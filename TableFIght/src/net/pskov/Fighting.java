package net.pskov;

import javafx.util.Pair;
import net.pskov.someEnum.Player;
import net.pskov.someEnum.StatusFighting;

import java.io.File;
import java.util.Arrays;
import java.util.Stack;

/**
 * Класс описывает бой: ФИО бойцов, их страна, и т.д.
 */
public class Fighting {
    // ФИО бойцов
    private final String nameOfLeftFighter;
    private final String nameOfRightFighter;

    private final int fightId;
    private final String categoryOfFighting;

    private final int countOfRounds; // количество раундов
    private final int durationOfRound; // длительности раунда в секундах
    private final int durationOfBreak; // длительности раунда в секундах

    // флаги стран
//    private final BufferedImage imageLeftConnerFlag;
//    private final BufferedImage imageRightConnerFlag;

    // название стран
    private final String countryOfLeftFighter;
    private final String countryOfRightFighter;

    // сколько накликали судьи мышками [round][номер судьи]
    private final int[][] countOfPointsForTheLeftFighter;
    private final int[][] countOfPointsForTheRightFighter;

    private volatile long startTime; // момент времени, когда текущий раунд(или break) начался
    private volatile long currentTime; // текущий момент времени
    private volatile long sumOfPause; // суммарное время, когда раунд был прерван
    private volatile int currentRound; // номер текущего раунда

    private volatile StatusFighting statusFighting;
    private volatile StatusFighting statusFightingBeforeDisqualification;

    private volatile Player disqualifiedPlayer;

    private Stack<Pair<Player, Integer>> stackOfMinus;
    private volatile int countOfMinusToLeft;
    private volatile int countOfMinusToRight;

    private Stack<Player> stackOfForestalling;
    private volatile int countOfForestallingToLeft; // количесво предупреждений, сделаных левому игроку
    private volatile int countOfForestallingToRight; // количесво предупреждений, сделаных левому игроку

    private Stack<Player> stackOfEx;
    private volatile int countOfExToLeft; // количесво предупреждений, сделаных левому игроку
    private volatile int countOfExToRight; // количесво предупреждений, сделаных левому игроку

    private final Sound soundGong; // звук гонга
    private final Sound soundHumerBit; // звук отбивки молоточков

    final long TOURNAMENT_CATEGORIES_FK;
    final int VERTEX;
    final long orderUID_left;
    final long orderUID_right;

    public Fighting(
            String nameOfLeftFighter,
            String nameOfRightFighter,

            int fightId,
            String categoryOfFighting,

            int countOfRounds,
            int durationOfRound,
            int durationOfBreak,

//            BufferedImage imageLeftConnerFlag,
//            BufferedImage imageRightConnerFlag,
            String countryOfLeftFighter,
            String countryOfRightFighter,

            long TOURNAMENT_CATEGORIES_FK,
            int VERTEX,
            long orderUID_left,
            long orderUID_right
    ) {
        this.nameOfLeftFighter = nameOfLeftFighter;
        this.nameOfRightFighter = nameOfRightFighter;

        this.fightId = fightId;
        this.categoryOfFighting = categoryOfFighting;

        this.countOfRounds = countOfRounds;
        this.durationOfRound = durationOfRound;
        this.durationOfBreak = durationOfBreak;

//        this.imageLeftConnerFlag = imageLeftConnerFlag;
//        this.imageRightConnerFlag = imageRightConnerFlag;

        this.countryOfLeftFighter = countryOfLeftFighter;
        this.countryOfRightFighter = countryOfRightFighter;

        this.countOfPointsForTheLeftFighter = new int[this.countOfRounds + 1][3];
        this.countOfPointsForTheRightFighter = new int[this.countOfRounds + 1][3];

        init();

        soundGong = new Sound(new File("resources\\sounds\\gong.wav"));
        soundHumerBit = new Sound(new File("resources\\sounds\\stuk_molotka.wav"));


        this.TOURNAMENT_CATEGORIES_FK = TOURNAMENT_CATEGORIES_FK;
        this.VERTEX = VERTEX;
        this.orderUID_left = orderUID_left;
        this.orderUID_right = orderUID_right;
    }

    private synchronized void init() {

        for (int i = 0; i <= countOfRounds; i++) {
            Arrays.fill(countOfPointsForTheLeftFighter[i], 0);
            Arrays.fill(countOfPointsForTheRightFighter[i], 0);
        }

        startTime = currentTime = sumOfPause = 0;
        currentRound = 1;

        statusFighting = StatusFighting.notBegin;
        statusFightingBeforeDisqualification = null;

        disqualifiedPlayer = Player.unknown;

        stackOfMinus = new Stack<>();
        countOfMinusToLeft = 0;
        countOfMinusToRight = 0;

        stackOfForestalling = new Stack<>();
        countOfForestallingToLeft = 0;
        countOfForestallingToRight = 0;

        stackOfEx = new Stack<>();
        countOfExToLeft = 0;
        countOfExToRight = 0;
    }

    /**
     * Одно очко идет левому бойцу
     */
    public synchronized void addOnePointToLeftFighter(int fromJudge) {
        if (!(statusFighting == StatusFighting.fighting || statusFighting == StatusFighting.finishTie))
            return;
        ++countOfPointsForTheLeftFighter[currentRound][fromJudge];
    }

    /**
     * * Одно очко идет правому бойцу
     */
    public synchronized void addOnePointToRightFighter(int fromJudge) {
        if (!(statusFighting == StatusFighting.fighting || statusFighting == StatusFighting.finishTie))
            return;
        ++countOfPointsForTheRightFighter[currentRound][fromJudge];
    }

    /**
     * Начать раунд
     */
    public synchronized void startRound() {
        init();
        startTime = currentTime = System.currentTimeMillis();
        statusFighting = StatusFighting.fighting;

        soundGong.play();
    }

    /**
     * Поставить раунд на паузу
     */
    public synchronized void pauseRound() {
        if (statusFighting == StatusFighting.fighting)
            statusFighting = StatusFighting.fightingPause;
        else
            throw new IllegalStateException();

        currentTime = System.currentTimeMillis();
    }

    /**
     * Продолжить раунд
     */
    public synchronized void continueRound() {
        if (statusFighting == StatusFighting.fightingPause)
            statusFighting = StatusFighting.fighting;
        else
            throw new RuntimeException();

        long time = System.currentTimeMillis();
        sumOfPause += time - currentTime;
        currentTime = time;
    }

    /**
     * Обновляем состояние раунда, смотря на время
     */
    public synchronized void updateTime() {
        if (statusFighting == StatusFighting.fighting || statusFighting == StatusFighting._break) {
            currentTime = System.currentTimeMillis();
            long now = ((currentTime - startTime) - sumOfPause) / 1000;

            if (statusFighting == StatusFighting.fighting) {
                if (durationOfRound <= now) {
                    startTime = currentTime;
                    sumOfPause = 0;

                    if (currentRound == countOfRounds) {
                        if (findWinner() != Player.unknown)
                            statusFighting = StatusFighting.finishPending;
                        else
                            statusFighting = StatusFighting.finishTie;
                    } else {
                        statusFighting = StatusFighting._break;
                    }
                    soundGong.play();
                    //return true;
                }
            } else {  //if (statusFighting == StatusFighting._break) {
                if (durationOfBreak - now <= 10 && !soundHumerBit.isPlaying()) {
                    soundHumerBit.play();
                }
                if (durationOfBreak <= now) {
                    startTime = currentTime;
                    sumOfPause = 0;

                    statusFighting = StatusFighting.fighting;
                    ++currentRound;

                    soundHumerBit.stop();
                    soundHumerBit.stop();
                    soundGong.play();
                    //return true;
                }
            }
        } else if (statusFighting == StatusFighting.finishTie) {
            int l = getCountJudgeForLeftFighter(true);
            int r = getCountJudgeForRightFighter(true);
            if (l < r) {
                statusFighting = StatusFighting.finishPending;
            } else if (l > r) {
                statusFighting = StatusFighting.finishPending;
            }
        }
    }

    private Player findWinner() {
        statusFighting = StatusFighting.finishTie;
        int l = getCountJudgeForLeftFighter(true);
        int r = getCountJudgeForRightFighter(true);
        if (l < r) {
            statusFighting = StatusFighting.finishPending;
            return Player.right;
        } else if (l > r) {
            statusFighting = StatusFighting.finishPending;
            return Player.left;
        } else {
            return findWinnerInCaseOfTieByEuropeanRules();
        }
    }

    private Player findWinnerInCaseOfTieByEuropeanRules() {
        int idJudge = -1;
        for (int i = 0; i < 3; i++) {
            int countPointLeft = 0;
            int countPointRight = 0;
            for (int round = 1; round <= countOfRounds; round++) {
                countPointLeft += countOfPointsForTheLeftFighter[round][i];
                countPointRight += countOfPointsForTheRightFighter[round][i];
            }
            if (countPointLeft == countPointRight) {
                idJudge = i;
                break;
            }
        }
        if (idJudge == -1) return Player.unknown;
        for (int round = countOfRounds - 1; round >= 1; round--) {
            if (countOfPointsForTheLeftFighter[round][idJudge] < countOfPointsForTheRightFighter[round][idJudge]) {
                statusFighting = StatusFighting.finishPending;
                return Player.right;
            } else if (countOfPointsForTheLeftFighter[round][idJudge] > countOfPointsForTheRightFighter[round][idJudge]) {
                statusFighting = StatusFighting.finishPending;
                return Player.left;
            }
        }
        return Player.unknown;
    }

    /**
     * Дисквалификация конкретного бойца
     *
     * @param player - этого бойца мы дисквалифицируем
     */
    void disqualify(Player player) {
        statusFightingBeforeDisqualification = statusFighting;
        statusFighting = StatusFighting.disqualification;

        disqualifiedPlayer = player;
    }

    /**
     * Отменить дисквалификацию и продолжить раунд
     */
    void rollBackDisqualification() {
        statusFighting = statusFightingBeforeDisqualification;
        statusFightingBeforeDisqualification = null;

        disqualifiedPlayer = null;

        long time = System.currentTimeMillis();
        sumOfPause += time - currentTime;
        currentTime = time;
    }

    /**
     * Минус бал левом бойцу. 3 очка правому бойцу от каждого судьи.
     */
    public synchronized void addMinusToLeft() {
        if (statusFighting == StatusFighting.notBegin ||
                statusFighting == StatusFighting.disqualification) {
            return;
        }

        ++countOfMinusToLeft;
        for (int i = 0; i < 3; i++) {
            countOfPointsForTheRightFighter[currentRound][i] += 3;
        }
        stackOfMinus.add(new Pair<>(Player.left, currentRound));

        if (countOfMinusToLeft == 3) {
            disqualify(Player.left);
        }
    }

    /**
     * Минус бал правому бойцу. 3 очка левому бойцу от каждого судьи.
     */
    public synchronized void addMinusToRight() {
        if (statusFighting == StatusFighting.notBegin ||
                statusFighting == StatusFighting.disqualification) {
            return;
        }

        ++countOfMinusToRight;
        for (int i = 0; i < 3; i++) {
            countOfPointsForTheLeftFighter[currentRound][i] += 3;
        }
        stackOfMinus.add(new Pair<>(Player.right, currentRound));

        if (countOfMinusToRight == 3) {
            disqualify(Player.right);
        }
    }

    /**
     * Откатываем последний minus
     */
    public synchronized void cancelLastMinus() {
        if (stackOfMinus.isEmpty())
            return;

        Player player = stackOfMinus.peek().getKey();
        int idRound = stackOfMinus.peek().getValue();
        stackOfMinus.pop();
        if (player == Player.left) {
            --countOfMinusToLeft;
            for (int i = 0; i < 3; i++) {
                countOfPointsForTheRightFighter[idRound][i] -= 3;
            }
        } else {
            --countOfMinusToRight;
            for (int i = 0; i < 3; i++) {
                countOfPointsForTheLeftFighter[idRound][i] -= 3;
            }
        }
        if (statusFighting == StatusFighting.disqualification && countOfMinusToLeft <= 2 && countOfMinusToRight <= 2) {
            rollBackDisqualification();
        }
    }

    /**
     * Одно предупреждение идет левому бойцу. Если их больше 1ого, до дисквалификация
     */
    public synchronized void addForestallingToLeft() {
        if (statusFighting == StatusFighting.notBegin ||
                statusFighting == StatusFighting.disqualification) {
            return;
        }

        if (countOfForestallingToLeft == 0) {
            ++countOfForestallingToLeft;
            stackOfForestalling.add(Player.left);
        }
    }

    /**
     * Одно предупреждение идет правому бойцу. Если их больше 1ого, до дисквалификация
     */
    public synchronized void addForestallingToRight() {
        if (statusFighting == StatusFighting.notBegin ||
                statusFighting == StatusFighting.disqualification) {
            return;
        }

        if (countOfForestallingToRight == 0) {
            ++countOfForestallingToRight;
            stackOfForestalling.add(Player.right);
        }
    }

    /**
     * Откатываем последнее предупреждение
     */
    public synchronized void cancelLastForestalling() {
        if (stackOfForestalling.isEmpty())
            return;

        Player player = stackOfForestalling.pop();
        if (player == Player.left) {
            --countOfForestallingToLeft;
        } else {
            --countOfForestallingToRight;
        }
    }


    /**
     * Левый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    public synchronized void addExToLeft() {
        if (statusFighting == StatusFighting.notBegin ||
                statusFighting == StatusFighting.disqualification) {
            return;
        }


        ++countOfExToLeft;
        stackOfEx.add(Player.left);
        if (4 <= countOfExToLeft) {
            disqualify(Player.left);
        }
    }

    /**
     * Правый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    public synchronized void addExToRight() {
        if (statusFighting == StatusFighting.notBegin ||
                statusFighting == StatusFighting.disqualification) {
            return;
        }

        ++countOfExToRight;
        stackOfEx.add(Player.right);
        if (4 <= countOfExToRight) {
            disqualify(Player.right);
        }
    }

    /**
     * Откатываем последний Ex (выход бойца за ринг)
     */
    public synchronized void cancelLastEx() {
        if (stackOfEx.isEmpty())
            return;

        Player player = stackOfEx.pop();
        if (player == Player.left)
            --countOfExToLeft;
        else
            --countOfExToRight;
        if (statusFighting == StatusFighting.disqualification && countOfExToLeft <= 3 && countOfExToRight <= 3) {
            rollBackDisqualification();
        }
    }

    // ----------------- Далее идут геттеры ---------------------------

    public synchronized String getNameOfLeftFighter(boolean isForJudge) {
        return isForJudge ? nameOfLeftFighter : nameOfRightFighter;
    }

    public synchronized String getNameOfRightFighter(boolean isForJudge) {
        return isForJudge ? nameOfRightFighter : nameOfLeftFighter;
    }

    public synchronized String getLabelFightNo() {
        return "Fight no.";
    }

    public synchronized int getFightId() {
        return fightId;
    }

    public synchronized String getSeparator() {
        return "---";
    }

    public synchronized String getCategoryOfFighting() {
        return categoryOfFighting;
    }

//    public synchronized BufferedImage getImageLeftConnerFlag(boolean isForJudge) {
//        return isForJudge ? imageLeftConnerFlag : imageRightConnerFlag;
//    }

//    public synchronized BufferedImage getImageRightConnerFlag(boolean isForJudge) {
//        return isForJudge ? imageRightConnerFlag : imageLeftConnerFlag;
//    }

    public synchronized String getCountryOfLeftFighter(boolean isForJudge) {
        return isForJudge ? countryOfLeftFighter : countryOfRightFighter;
    }

    public synchronized String getCountryOfRightFighter(boolean isForJudge) {
        return isForJudge ? countryOfRightFighter : countryOfLeftFighter;
    }

    public synchronized int[] getCountOfPointsForTheLeftFighter(boolean isForJudge) {
        if (isForJudge) {
            int[] count = new int[3];
            for (int round = 0; round <= currentRound; round++) {
                for (int judge = 0; judge < 3; judge++) {
                    count[judge] += countOfPointsForTheLeftFighter[round][judge];
                }
            }
            return count;
        } else {
            return getCountOfPointsForTheRightFighter(true);
        }
    }

    public synchronized int[] getCountOfPointsForTheRightFighter(boolean isForJudge) {
        if (isForJudge) {
            int[] count = new int[3];
            for (int round = 0; round <= currentRound; round++) {
                for (int judge = 0; judge < 3; judge++) {
                    count[judge] += countOfPointsForTheRightFighter[round][judge];
                }
            }
            return count;
        } else {
            return getCountOfPointsForTheLeftFighter(true);
        }
    }

    /**
     * @return колическо судей за левого бойца
     */
    public synchronized int getCountJudgeForLeftFighter(boolean fromJudge) {
        int countJudgeForLeftFighter = 0;
        for (int i = 0; i < 3; i++) {
            if (getCountOfPointsForTheLeftFighter(fromJudge)[i] > getCountOfPointsForTheRightFighter(fromJudge)[i])
                ++countJudgeForLeftFighter;
        }
        return countJudgeForLeftFighter;
    }

    /**
     * @return колическо судей за правого бойца
     */
    public synchronized int getCountJudgeForRightFighter(boolean fromJudge) {
        int countJudgeForRightFighter = 0;
        for (int i = 0; i < 3; i++) {
            if (getCountOfPointsForTheLeftFighter(fromJudge)[i] < getCountOfPointsForTheRightFighter(fromJudge)[i])
                ++countJudgeForRightFighter;
        }
        return countJudgeForRightFighter;
    }

    public synchronized Player getLoser(boolean isForJudge) {
        if (isForJudge) {
            if (statusFighting == StatusFighting.disqualification)
                return disqualifiedPlayer;
            if (statusFighting == StatusFighting.finishPending || statusFighting == StatusFighting.finishTie) {
                Player winner = findWinner();
                if (winner == Player.left)
                    return Player.right;
                if (winner == Player.right)
                    return Player.left;
                return Player.unknown;
            }
            return Player.unknown;
        } else {
            Player loser = getLoser(false);
            if (loser == Player.left)
                return Player.right;
            if (loser == Player.right)
                return Player.left;
            return Player.unknown;
        }
    }

    public synchronized int getCountOfMinusToLeft(boolean isForJudge) {
        return isForJudge ? countOfMinusToLeft : countOfMinusToRight;
    }

    public synchronized int getCountOfMinusToRight(boolean isForJudge) {
        return isForJudge ? countOfMinusToRight : countOfMinusToLeft;
    }

    public synchronized int getCountOfForestallingToLeft(boolean isForJudge) {
        return isForJudge ? countOfForestallingToLeft : countOfForestallingToRight;
    }

    public synchronized int getCountOfForestallingToRight(boolean isForJudge) {
        return isForJudge ? countOfForestallingToRight : countOfForestallingToLeft;
    }

    public synchronized int getCountOfExToLeft(boolean isForJudge) {
        return isForJudge ? countOfExToLeft : countOfExToRight;
    }

    public synchronized int getCountOfExToRight(boolean isForJudge) {
        return isForJudge ? countOfExToRight : countOfExToLeft;
    }

    public synchronized String getStringTime() {
        long now = ((currentTime - startTime) - sumOfPause) / 1000;

        if (statusFighting == StatusFighting.notBegin) {
            return String.format("%02d:%02d", durationOfRound / 60, durationOfRound % 60);
        }
        if (statusFighting == StatusFighting.fighting || statusFighting == StatusFighting.fightingPause) {
            long remainTime = durationOfRound - now;
            return String.format("%02d:%02d", remainTime / 60, remainTime % 60);
        }
        if (statusFighting == StatusFighting._break) {
            long remainTime = durationOfBreak - now;
            return String.format("%02d:%02d", remainTime / 60, remainTime % 60);
        }
        return "";
    }


    /**
     * @return то, что находится в заголовке в таблице со счётом
     */
    public synchronized String getRoofInfo() {
        if (statusFighting == StatusFighting.finishPending) {
            if (getLoser(true) == Player.left)
                return "Winner is " + nameOfRightFighter;
            else if (getLoser(true) == Player.right)
                return "Winner is " + nameOfLeftFighter;
            else
                return "Winner is ";
        } else if (statusFighting == StatusFighting.finishTie) {
            return statusFighting.toString();
        } else if (statusFighting == StatusFighting.disqualification) {
            return statusFighting.toString();
        }
        return String.format("Round %d/%d %s", currentRound, countOfRounds, statusFighting);
    }


    public synchronized StatusFighting getStatusFighting() {
        return statusFighting;
    }

    @Override
    public String toString() {
        String separator = " / ";
        return fightId + separator +
                nameOfLeftFighter + " " + countryOfLeftFighter + " " + separator +
                nameOfRightFighter + " " + countryOfRightFighter + " " + separator;
    }
}

