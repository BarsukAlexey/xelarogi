#include "fighting.h"

Fighting::Fighting(int durationOfRound, int durationOfBreak, int countOfRounds, int durationExtraRound) :

    durationOfDoctorOnRing(2 * 60 * 1000),
    durationOfRound(durationOfRound),
    durationOfBreak(durationOfBreak),
    countOfRounds(countOfRounds),
    durationOfExtraRound(durationExtraRound)
{
    currentRound = 1;
    status = FightStatus::NotStart;

    timer = new QTimer();
    timer->setInterval(250);
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
    if (isDisqOrPoint10OrForceWinner())
        return;
    ++countPointLeft;
    if (getCountOfPointsForLeftFighter() - getCountOfPointsForRightFighter() == 10) {
        statusBeforDisqualification = status;
        statusBeforDisqualification = FightStatus::winnerByPointsLeft10;
    }

}

void Fighting::addOnePointToRightFighter() {
    if (isDisqOrPoint10OrForceWinner())
        return;
    ++countPointRight;
    if (getCountOfPointsForRightFighter() - getCountOfPointsForLeftFighter() == 10) {
        statusBeforDisqualification = status;
        statusBeforDisqualification = FightStatus::winnerByPointsLeft10;
    }
}

void Fighting::cancelLeftPoint(){
    if (0 < countPointLeft)
        --countPointLeft;
}

void Fighting::cancelRightPoint(){
    if (0 < countPointRight)
        --countPointRight;
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
        item.deltaLeft = -qMin(3, countOfPointsForTheLeftFighter);
        item.deltaRight = 3 + item.deltaLeft;
    }
    stackPenalty.push(item);

    if (4 == countOfExToLeft) {
        disqualify(Player::Left);
    }
}

void Fighting::addExToRight() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfExToRight;
    Item item(Penalty::Ex, Player::Right);
    if (2 <= countOfExToRight) {
        int countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
        item.deltaRight = -qMin(3, countOfPointsForTheRightFighter);
        item.deltaLeft = 3 + item.deltaRight;
    }
    stackPenalty.push(item);

    if (4 == countOfExToRight) {
        disqualify(Player::Right);
    }
}

void Fighting::addMinusToLeft() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfMinusToLeft;
    Item item(Penalty::Minus, Player::Left);
    int countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
    item.deltaLeft = -qMin(3, countOfPointsForTheLeftFighter);
    item.deltaRight = 3 + item.deltaLeft;
    stackPenalty.push(item);

    if (countOfMinusToLeft == 3) {
        disqualify(Player::Left);
    }
}

void Fighting::addMinusToRight() {
    if (isDisqOrPoint10OrForceWinner())
        return;

    ++countOfMinusToRight;
    Item item(Penalty::Minus, Player::Right);
    int countOfPointsForRightFighter = getCountOfPointsForRightFighter();
    item.deltaRight = -qMin(3, countOfPointsForRightFighter);
    item.deltaLeft = 3 + item.deltaRight;
    stackPenalty.push(item);

    if (countOfMinusToRight == 3)
        disqualify(Player::Right);
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

int Fighting::getCountOfPointsForLeftFighter(){
    int count = countPointLeft;
    for (Item item : stackPenalty)
        count += item.deltaLeft;
    return count;
}

int Fighting::getCountOfPointsForRightFighter(){
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


    if (status == FightStatus::Fight) {
        spendTime += quantum;
        if (durationOfRound <= spendTime) {
            spendTime -= durationOfRound; // spendTime = 0;

            if (currentRound == countOfRounds) {
                int l = getCountOfPointsForLeftFighter();
                int r = getCountOfPointsForRightFighter();
                if (l > r)
                    status = FightStatus::winnerByPointsLeft;
                else if (l < r)
                    status = FightStatus::winnerByPointsRight;
                else {
                    if (durationOfExtraRound == 0)
                        status = FightStatus::Tie;
                    else
                        status = FightStatus::PendingExtraRound;
                }
            } else {
                status = FightStatus::Break;
            }
            soundGong->play();
        }
    } else if (status == FightStatus::Break) {
        spendTime += quantum;
        if (durationOfBreak - spendTime <= 10 && soundHummerBit->isFinished()) {
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
        int l = getCountOfPointsForLeftFighter();
        int r = getCountOfPointsForRightFighter();
        if (l > r)
            status = FightStatus::winnerByPointsLeft;
        else if (l < r)
            status = FightStatus::winnerByPointsRight;
    } else if (status == FightStatus::PendingExtraRound) {
        int l = getCountOfPointsForLeftFighter();
        int r = getCountOfPointsForRightFighter();
        if (l > r)
            status = FightStatus::winnerByPointsLeft;
        else if (l < r)
            status = FightStatus::winnerByPointsRight;
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
    } else if (status == FightStatus::winnerByPointsRight) {
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

QString Fighting::getStringTime() {
    if (status == FightStatus::NotStart) {
        return getTimeMMSS(durationOfRound);
    }
    if (status == FightStatus::Fight || status == FightStatus::PauseFight) {
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

QString Fighting::getStringTimeDoctor()
{
    return getTimeMMSS(spentTimeDoctor);
}

QString Fighting::getResult() {
    int countPointLeft = getCountOfPointsForLeftFighter();
    int countPointRight = getCountOfPointsForRightFighter();
    if (status == FightStatus::DisqualificationLeft || status == FightStatus::DisqualificationRight)
        return "DISQ";
    if (status == FightStatus::forceLeftWinner || status == FightStatus::forceRightWinner)
        return forceResult;

    return countPointLeft + " : " + countPointRight;
}

Fighting::Player Fighting::getWinner() {
    if (status == FightStatus::forceLeftWinner || status == FightStatus::winnerByPointsLeft || status == FightStatus::DisqualificationRight)
        return Player::Left;
    if (status == FightStatus::forceRightWinner || status == FightStatus::winnerByPointsRight || status == FightStatus::DisqualificationLeft)
        return Player::Right;
    return Player::NoPlayer;
}

void Fighting::cancelLastAction() {
    if (stackPenalty.isEmpty() || status == FightStatus::stoppedByJudge)
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

