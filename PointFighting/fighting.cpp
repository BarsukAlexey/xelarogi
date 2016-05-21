#include "fighting.h"


Fighting::Fighting(int durationOfRound, int durationOfBreak, int countOfRounds, int durationExtraRound) :

    durationOfDoctorOnRing(2 * 60 * 1000),
    durationOfRound(1000 * durationOfRound),
    durationOfBreak(1000 * durationOfBreak),
    countOfRounds(countOfRounds),
    durationOfExtraRound(1000 * durationExtraRound)
{

    statusName.clear();
    statusName << "NotStart" << "Fight" << "Break" << "PauseFight" << "DoctorOnRing" << "Tie" << "DisqualificationLeft" << "DisqualificationRight" <<
    "winnerByPointsLeft" << "winnerByPointsRight" <<
    "winnerByPointsLeft10" << "winnerByPointsRight10" <<
    "stoppedByJudge" << "forceLeftWinner" << "forceRightWinner" <<
    "PendingExtraRound" << "ExtraRound" << "PauseExtraRound";

    prevMomentTime = 0;
    spendTime = 0;

    currentRound = 1;
    spentTimeDoctor = 0;


    currentRound = 1;

    status = FightStatus::NotStart;

    countPointLeft = 0;
    countPointRight = 0;
    countOfMinusToLeft = 0;
    countOfMinusToRight = 0;
    countOfForestallingToLeft = 0;
    countOfForestallingToRight = 0;
    countOfExToLeft = 0;
    countOfExToRight = 0;
    wasExtraRound = false;

    timer = new QTimer();
    timer->setInterval(250);
    connect(timer, &QTimer::timeout, [this](){updateTime();});
}


void Fighting::dispose() {
    timer->stop();
}

void Fighting::setDialog(bool dialog) {
    if (dialog) {
        fightStatusBeforDialog = status;
        status = FightStatus::stoppedByJudge;
    } else {
        status = fightStatusBeforDialog;
    }
}

void Fighting::forceStopRound(Fighting::Player player, QString forceResult) {
    if (player == Player::Left) {
        status = FightStatus::forceLeftWinner;
        this->forceResult = forceResult;
    } else if (player == Player::Right) {
        status = FightStatus::forceRightWinner;
        this->forceResult = forceResult;
    }
}

bool Fighting::isDisqOrPoint10OrForceWinner() {
    return status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight ||
            status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner ||
            status == FightStatus::winnerByPointsLeft10 || status == FightStatus::winnerByPointsRight10 ||
            status == FightStatus::stoppedByJudge;
}

void Fighting::disqualify(Fighting::Player player){
    if (player == Player::Left) {
        statusBeforDisqualification = status;
        status = FightStatus::DisqualificationLeft;
    } else if (player == Player::Right) {
        statusBeforDisqualification = status;
        status = FightStatus::DisqualificationRight;
    }
}

void Fighting::addOnePointToLeftFighter() {
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight ||
        status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner ||
        status == FightStatus::stoppedByJudge)
        return;
    ++countPointLeft;
    updatePointStatus();
}

void Fighting::addOnePointToRightFighter() {
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight ||
        status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner ||
        status == FightStatus::stoppedByJudge)
        return;
    ++countPointRight;
    updatePointStatus();
}

void Fighting::cancelLeftPoint(){
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight ||
        status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner ||
        status == FightStatus::stoppedByJudge)
        return;

    if (0 < countPointLeft) {
        --countPointLeft;
        updatePointStatus();
    }
}

void Fighting::cancelRightPoint(){
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight ||
        status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner ||
        status == FightStatus::stoppedByJudge)
        return;

    if (0 < countPointRight) {
        --countPointRight;
        updatePointStatus();
    }
}

void Fighting::addForestallingToLeft() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    if (countOfForestallingToLeft == 0) {
        ++countOfForestallingToLeft;
        Item item(Penalty::FO, Player::Left);
        stackPenalty.push(item);
    }
}

void Fighting::addForestallingToRight() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    if (countOfForestallingToRight == 0) {
        ++countOfForestallingToRight;
        Item item(Penalty::FO, Player::Right);
        stackPenalty.push(item);
    }
}

void Fighting::addExToLeft() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfExToLeft;
    Item item(Penalty::Ex, Player::Left);
    if (2 <= countOfExToLeft) {
        int countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
        item.deltaLeft = -qMin(1, countOfPointsForTheLeftFighter);
        item.deltaRight = 1 + item.deltaLeft;
    }
    stackPenalty.push(item);

    if (4 == countOfExToLeft)
        disqualify(Player::Left);
    else
        updatePointStatus();
}

void Fighting::addExToRight() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfExToRight;
    Item item(Penalty::Ex, Player::Right);
    if (2 <= countOfExToRight) {
        int countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
        item.deltaRight = -qMin(1, countOfPointsForTheRightFighter);
        item.deltaLeft = 1 + item.deltaRight;
    }
    stackPenalty.push(item);

    if (4 == countOfExToRight)
        disqualify(Player::Right);
    else
        updatePointStatus();
}

void Fighting::addMinusToLeft() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfMinusToLeft;
    Item item(Penalty::Minus, Player::Left);
    int countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
    item.deltaLeft = -qMin(1, countOfPointsForTheLeftFighter);
    item.deltaRight = 1 + item.deltaLeft;
    stackPenalty.push(item);

    if (countOfMinusToLeft == 3)
        disqualify(Player::Left);
    else
        updatePointStatus();
}

void Fighting::addMinusToRight() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfMinusToRight;
    Item item(Penalty::Minus, Player::Right);
    int countOfPointsForRightFighter = getCountOfPointsForRightFighter();
    item.deltaRight = -qMin(1, countOfPointsForRightFighter);
    item.deltaLeft = 1 + item.deltaRight;
    stackPenalty.push(item);

    if (countOfMinusToRight == 3)
        disqualify(Player::Right);
    else
        updatePointStatus();
}

void Fighting::pressedKeySpace() {
    if (status == FightStatus::NotStart) {
        timer->start();
        status = FightStatus::Fight;
        soundGong->play();
    } else if (status == FightStatus::Fight)
        status = FightStatus::PauseFight;
    else if (status == FightStatus::PauseFight)
        status = FightStatus::Fight;
    else if (status == FightStatus::PendingExtraRound) {
        status = FightStatus::ExtraRound;
        soundGong->play();
    } else if (status == FightStatus::ExtraRound)
        status = FightStatus::PauseExtraRound;
    else if (status == FightStatus::PauseExtraRound)
        status = FightStatus::ExtraRound;
}

void Fighting::pressDoctor()
{
    if (status == FightStatus::Fight){
        spentTimeDoctor = 0;
        status = FightStatus::DoctorOnRing;
    }
    else if (status == FightStatus::DoctorOnRing){
        status = FightStatus::Fight;
    }
}

int Fighting::getCountOfPointsForLeftFighter() const{
    int count = countPointLeft;
    for (Item item : stackPenalty)
        count += item.deltaLeft;
    return count;
}

int Fighting::getCountOfPointsForRightFighter() const{
    int count = countPointRight;
    for (Item item : stackPenalty)
        count += item.deltaRight;
    return count;
}

void Fighting::updateTime() {
    long momentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();;
    if (prevMomentTime == 0) prevMomentTime = momentTime;
    long quantum = momentTime - prevMomentTime;
    prevMomentTime = momentTime;
//    qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss zzz") << statusName[status] << spendTime;


    if (status == FightStatus::Fight) {
        spendTime += quantum;
        if (durationOfRound <= spendTime) {
            spendTime -= durationOfRound; // spendTime = 0;

            if (currentRound == countOfRounds) {
                int l = getCountOfPointsForLeftFighter();
                int r = getCountOfPointsForRightFighter();
                if (l > r) {
                    status = FightStatus::winnerByPointsLeft;
                } else if (l < r) {
                    status = FightStatus::winnerByPointsRight;
                } else {
                    if (0 < durationOfExtraRound && !wasExtraRound)
                        status = FightStatus::PendingExtraRound;
                    else
                        status = FightStatus::Tie;
                }
            } else {
                status = FightStatus::Break;
            }
            soundGong->play();
        }
    } else if (status == FightStatus::Break) {
        spendTime += quantum;
        if (durationOfBreak - spendTime <= 10 * 1000 && soundHummerBit->isFinished()) {
            soundGong->stop();
            soundHummerBit->play();

        }
        if (durationOfBreak <= spendTime) {
            spendTime -= durationOfBreak; // spendTime = 0;

            status = FightStatus::Fight;
            ++currentRound;

            soundHummerBit->stop();
            soundGong->play();
        }
    } else if (status == FightStatus::DoctorOnRing) {
        spentTimeDoctor += quantum;
        if (durationOfDoctorOnRing <= spentTimeDoctor) {
            status = FightStatus::Fight;
        }
    } else if (status == FightStatus::Tie) {
    } else if (status == FightStatus::PendingExtraRound) {
    } else if (status == FightStatus::ExtraRound) {
        spendTime += quantum;
        wasExtraRound = true;
        if (durationOfExtraRound <= spendTime) {
            int l = getCountOfPointsForLeftFighter();
            int r = getCountOfPointsForRightFighter();
            if (l > r) {
                status = FightStatus::winnerByPointsLeft;
                soundGong->play();
            } else if (l < r) {
                status = FightStatus::winnerByPointsRight;
                soundGong->play();
            }
        }
    } else if (status == FightStatus::winnerByPointsLeft) {
    } else if (status == FightStatus::winnerByPointsRight) {
    }

    emit statusOrPointsChanged();
}

void Fighting::updatePointStatus()
{
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight)
        return;

    if (status != FightStatus::winnerByPointsLeft10 && 10 <= getCountOfPointsForLeftFighter() - getCountOfPointsForRightFighter()) {
         statusBeforDisqualification = status;
         status = FightStatus::winnerByPointsLeft10;
    } else if (status != FightStatus::winnerByPointsRight10 && 10 <= getCountOfPointsForRightFighter() - getCountOfPointsForLeftFighter()) {
        statusBeforDisqualification = status;
        status = FightStatus::winnerByPointsRight10;
    }

    if (status == FightStatus::winnerByPointsLeft10  && getCountOfPointsForLeftFighter()  - getCountOfPointsForRightFighter() < 10){
        status = statusBeforDisqualification;
    } else if (status == FightStatus::winnerByPointsRight10 && getCountOfPointsForRightFighter() - getCountOfPointsForLeftFighter() < 10){
        status = statusBeforDisqualification;
    }

    if (status == winnerByPointsRight || status == winnerByPointsLeft || status == Tie ||
        status == PendingExtraRound){
        int l = getCountOfPointsForLeftFighter();
        int r = getCountOfPointsForRightFighter();
        if (l > r) {
            status = FightStatus::winnerByPointsLeft;
        } else if (l < r) {
            status = FightStatus::winnerByPointsRight;
        } else {
            if (0 < durationOfExtraRound && !wasExtraRound)
                status = FightStatus::PendingExtraRound;
            else
                status = FightStatus::Tie;
        }
    }
}

QString Fighting::getTimeMMSS(long long timeMS)
{
    timeMS /= 1000;
    return QString("%1").arg(timeMS/60, 2, 10, QChar('0')) + ":" + QString("%1").arg(timeMS%60, 2, 10, QChar('0'));
}

QString Fighting::getStringTime() const {
    if (status == FightStatus::NotStart) {
        return getTimeMMSS(durationOfRound);
    }
    if (status == FightStatus::Fight || status == FightStatus::PauseFight || status == FightStatus::DoctorOnRing) {
        long remainTime = qMax(0LL, durationOfRound - spendTime);
        return getTimeMMSS(remainTime);
    }
    if (status == FightStatus::Break) {
        long remainTime = qMax(0LL, durationOfBreak - spendTime);
        return getTimeMMSS(remainTime);
    }
    if (status == FightStatus::PendingExtraRound) {
        return getTimeMMSS(durationOfExtraRound);
    }
    if (status == FightStatus::ExtraRound || status == FightStatus::PauseExtraRound) {
        long remainTime = qMax(0LL, durationOfExtraRound - spendTime);
        return getTimeMMSS(remainTime);
    }
    return "";
}

long long Fighting::getTimeMS() const {
    if (status == FightStatus::NotStart) {
        return durationOfRound;
    }
    if (status == FightStatus::Fight || status == FightStatus::PauseFight) {
        long remainTime = qMax(0LL, durationOfRound - spendTime);
        return remainTime;
    }
    if (status == FightStatus::Break) {
        long remainTime = qMax(0LL, durationOfBreak - spendTime);
        return remainTime;
    }
    if (status == FightStatus::PendingExtraRound) {
        return durationOfExtraRound;
    }
    if (status == FightStatus::ExtraRound || status == FightStatus::PauseExtraRound) {
        long remainTime = qMax(0LL, durationOfExtraRound - spendTime);
        return remainTime;
    }
    return 0;
}

QString Fighting::getStringTimeDoctor() const
{
    return getTimeMMSS(qMax(0LL, durationOfDoctorOnRing - spentTimeDoctor));
}

QString Fighting::getResult() {
    int countPointLeft = getCountOfPointsForLeftFighter();
    int countPointRight = getCountOfPointsForRightFighter();
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight)
        return "DISQ";
    if (status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner)
        return forceResult;

    return QString::number(countPointLeft) + " : " + QString::number(countPointRight);
}

Fighting::Player Fighting::getWinner() {
    if (status == FightStatus::forceLeftWinner  || status == FightStatus::winnerByPointsLeft  || status == FightStatus::winnerByPointsLeft10  || status == FightStatus::DisqualificationRight)
        return Player::Left;
    if (status == FightStatus::forceRightWinner || status == FightStatus::winnerByPointsRight || status == FightStatus::winnerByPointsRight10 || status == FightStatus::DisqualificationLeft )
        return Player::Right;
    return Player::NoPlayer;
}

void Fighting::cancelLastAction() {
    if (stackPenalty.isEmpty() || status == FightStatus::stoppedByJudge || status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner)
        return;


    Item item = stackPenalty.pop();

    if (item.penalty == Penalty::Minus) {
        if (item.player == Player::Left) {
            --countOfMinusToLeft;
            if (countOfMinusToLeft == 2 && status == FightStatus::DisqualificationLeft) {
                status = statusBeforDisqualification;
            }
        }
        if (item.player == Player::Right) {
            --countOfMinusToRight;
            if (countOfMinusToRight == 2 && status == FightStatus::DisqualificationRight) {
                status = statusBeforDisqualification;
            }
        }
    }

    if (item.penalty == Penalty::FO) {
        if (item.player == Player::Left)
            --countOfForestallingToLeft;
        if (item.player == Player::Right)
            --countOfForestallingToRight;
    }

    if (item.penalty == Penalty::Ex) {
        if (item.player == Player::Left) {
            --countOfExToLeft;
            if (countOfExToLeft == 3 && status == FightStatus::DisqualificationLeft) {
                status = statusBeforDisqualification;
            }
        }
        if (item.player == Player::Right) {
            --countOfExToRight;
            if (countOfExToRight == 3 && status == FightStatus::DisqualificationRight) {
                status = statusBeforDisqualification;
            }
        }
    }


}

Fighting::FightStatus Fighting::getStatus() const {
    return status;
}

int Fighting::getDurationOfRound() const{
    return durationOfRound;
}

int Fighting::getCountOfRounds() const
{
    return countOfRounds;
}

int Fighting::getCurrentRound() const
{
    return currentRound;
}

int Fighting::getCountOfMinusToLeft() const{
    return countOfMinusToLeft;
}

int Fighting::getCountOfMinusToRight() const{
    return countOfMinusToRight;
}

int Fighting::getCountOfForestallingToLeft() const{
    return countOfForestallingToLeft;
}

int Fighting::getCountOfForestallingToRight() const{
    return countOfForestallingToRight;
}

int Fighting::getCountOfExToLeft() const{
    return countOfExToLeft;
}

int Fighting::getCountOfExToRight() const{
    return countOfExToRight;
}

