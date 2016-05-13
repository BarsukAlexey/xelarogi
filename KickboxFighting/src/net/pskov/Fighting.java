package net.pskov;

import net.pskov.some_enum.FightStatus;
import net.pskov.some_enum.Penalty;
import net.pskov.some_enum.Player;

import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Arrays;
import java.util.Stack;


class Fighting {

    private static final Sound soundGong = new Sound(new File("resources\\sounds\\gong.wav"));
    private static final Sound soundHumerBit = new Sound(new File("resources\\sounds\\stuk_molotka.wav"));


    // ФИО бойцов
    private final String nameOfLeftFighter;
    private final String nameOfRightFighter;

    private final int fightId;
    private final String categoryOfFighting;

    private final int countOfRounds; // количество раундов
    private final int durationOfRound; // длительности раунда в ms
    private final int durationOfBreak; // длительности раунда в ms
    private final int durationOfExtraRound; // длительности раунда в ms
    private final int inCaseOfTie; // длительности раунда в ms

    // флаги стран
    private final BufferedImage imageLeftConnerFlag;
    private final BufferedImage imageRightConnerFlag;

    // название стран
    private final String countryOfLeftFighter;
    private final String countryOfRightFighter;

    // сколько накликали судьи мышками [round][номер судьи]
    private final int[][] countOfPointsForTheLeftFighter;
    private final int[][] countOfPointsForTheRightFighter;

    private volatile long prevMomentTime;
    private volatile long spendTime;
    private volatile int currentRound; // номер текущего раунда

    private volatile FightStatus fightStatus;
    private volatile FightStatus statusFightingBeforeDisqualification;

    private volatile int countOfMinusToLeft;
    private volatile int countOfMinusToRight;

    private volatile int countOfForestallingToLeft; // количесво предупреждений, сделаных левому игроку
    private volatile int countOfForestallingToRight; // количесво предупреждений, сделаных левому игроку

    private volatile int countOfExToLeft; // количесво предупреждений, сделаных левому игроку
    private volatile int countOfExToRight; // количесво предупреждений, сделаных левому игроку


    final long TOURNAMENT_CATEGORIES_FK;
    final int VERTEX;
    private String forceResult;

    private static class Item {
        Penalty penalty;
        Player player;
        int[] deltaLeft; //
        int[] deltaRight; //

        Item(Penalty penalty, Player player) {
            this.penalty = penalty;
            this.player = player;
            deltaLeft = new int[3];
            deltaRight = new int[3];
        }
    }

    private Stack<Item> stackPenalty;

    Fighting(
            String nameOfLeftFighter,
            String nameOfRightFighter,

            int fightId,
            String categoryOfFighting,

            int countOfRounds,
            int durationOfRound,
            int durationOfBreak,
            int durationOfExtraRound,
            int inCaseOfTie,

            BufferedImage imageLeftConnerFlag,
            BufferedImage imageRightConnerFlag,
            String countryOfLeftFighter,
            String countryOfRightFighter,

            long TOURNAMENT_CATEGORIES_FK,
            int VERTEX
    ) {
        this.nameOfLeftFighter = nameOfLeftFighter;
        this.nameOfRightFighter = nameOfRightFighter;

        this.fightId = fightId;
        this.categoryOfFighting = categoryOfFighting;

        this.countOfRounds = countOfRounds;
        this.durationOfRound = durationOfRound;
        this.durationOfBreak = durationOfBreak;
        this.durationOfExtraRound = durationOfExtraRound;
        this.inCaseOfTie = inCaseOfTie;

        this.imageLeftConnerFlag = imageLeftConnerFlag;
        this.imageRightConnerFlag = imageRightConnerFlag;

        this.countryOfLeftFighter = countryOfLeftFighter;
        this.countryOfRightFighter = countryOfRightFighter;

        this.countOfPointsForTheLeftFighter = new int[this.countOfRounds + 1][3];
        this.countOfPointsForTheRightFighter = new int[this.countOfRounds + 1][3];

        init();


        this.TOURNAMENT_CATEGORIES_FK = TOURNAMENT_CATEGORIES_FK;
        this.VERTEX = VERTEX;

        stackPenalty = new Stack<>();
    }

    private synchronized void init() {

        for (int i = 0; i <= countOfRounds; i++) {
            Arrays.fill(countOfPointsForTheLeftFighter[i], 0);
            Arrays.fill(countOfPointsForTheRightFighter[i], 0);
        }

        spendTime = 0;
        currentRound = 1;

        fightStatus = FightStatus.NotStart;
        statusFightingBeforeDisqualification = null;

        countOfMinusToLeft = 0;
        countOfMinusToRight = 0;

        countOfForestallingToLeft = 0;
        countOfForestallingToRight = 0;

        countOfExToLeft = 0;
        countOfExToRight = 0;
    }

    synchronized void addOnePointToLeftFighter(int fromJudge) {
        if (getWinner() == Player.unknown)
            return;
        ++countOfPointsForTheLeftFighter[currentRound][fromJudge];
    }

    synchronized void addOnePointToRightFighter(int fromJudge) {
        if (getWinner() == Player.unknown)
            return;
        ++countOfPointsForTheRightFighter[currentRound][fromJudge];
    }

    synchronized void pressedKeySpace() {
        if (fightStatus == FightStatus.NotStart) {
            init();
            fightStatus = FightStatus.Fighting;
            soundGong.play();
        } else if (fightStatus == FightStatus.Fighting) {
            fightStatus = FightStatus.PauseFight;
        } else if (fightStatus == FightStatus.PauseFight) {
            fightStatus = FightStatus.Fighting;
        } else if (fightStatus == FightStatus.ExtraRound) {
            fightStatus = FightStatus.PauseExtraRound;
        } else if (fightStatus == FightStatus.PauseExtraRound) {
            fightStatus = FightStatus.ExtraRound;
        }
    }

    synchronized void updateTime() {
        long momentTime = System.currentTimeMillis();
        long quantum = momentTime - prevMomentTime;
        prevMomentTime = momentTime;


        if (fightStatus == FightStatus.Fighting) {
            spendTime += quantum;
            if (durationOfRound <= spendTime) {
                spendTime -= durationOfRound; // spendTime = 0;

                if (currentRound == countOfRounds) {
                    if (getWinner() != Player.unknown) {
                        if (inCaseOfTie == 0) {
                            fightStatus = FightStatus.Tie;
                        } else if (inCaseOfTie == 1) {
                            Player winner = findWinnerInCaseOfTieByEuropeanRules();
                            if (winner == Player.unknown)
                                fightStatus = FightStatus.Tie;
                            else
                                fightStatus = winner == Player.left ? FightStatus.winnerByPointsLeft : FightStatus.winnerByPointsRight;
                        } else {
                            fightStatus = FightStatus.PendingExtraRound;
                        }
                    } else {
                        int l = getCountJudgeForLeftFighter();
                        int r = getCountJudgeForRightFighter();
                        if (l > r)
                            fightStatus = FightStatus.winnerByPointsLeft;
                        else if (l < r)
                            fightStatus = FightStatus.winnerByPointsRight;
                    }
                } else {
                    fightStatus = FightStatus.Break;
                }
                soundGong.play();
            }
        } else if (fightStatus == FightStatus.Break) {
            spendTime += quantum;
            if (durationOfBreak - spendTime <= 10 && !soundHumerBit.isPlaying()) {
                soundHumerBit.play();
            }
            if (durationOfBreak <= spendTime) {
                spendTime -= durationOfBreak; // spendTime = 0;

                fightStatus = FightStatus.Fighting;
                ++currentRound;

                soundHumerBit.stop();
                soundGong.play();
            }
        } else if (fightStatus == FightStatus.Tie) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r) {
                fightStatus = FightStatus.winnerByPointsLeft;
            } else if (l < r) {
                fightStatus = FightStatus.winnerByPointsRight;
            }
        } else if (fightStatus == FightStatus.ExtraRound) {
            spendTime += quantum;
            if (durationOfExtraRound <= spendTime) {
                int l = getCountJudgeForLeftFighter();
                int r = getCountJudgeForRightFighter();
                if (l > r) {
                    fightStatus = FightStatus.winnerByPointsLeft;
                } else if (l < r) {
                    fightStatus = FightStatus.winnerByPointsRight;
                }
            }
        }
    }


    private Player findWinnerInCaseOfTieByEuropeanRules() {
        for (int idJudge = 0; idJudge < 3; idJudge++) {
            int countPointLeft = 0;
            int countPointRight = 0;
            for (int round = 1; round <= countOfRounds; round++) {
                countPointLeft += countOfPointsForTheLeftFighter[round][idJudge];
                countPointRight += countOfPointsForTheRightFighter[round][idJudge];
            }
            if (countPointLeft != countPointRight)
                continue;
            for (int round = countOfRounds - 1; round >= 1; round--) {
                if (countOfPointsForTheLeftFighter[round][idJudge] < countOfPointsForTheRightFighter[round][idJudge]) {
                    return Player.Right;
                } else if (countOfPointsForTheLeftFighter[round][idJudge] > countOfPointsForTheRightFighter[round][idJudge]) {
                    return Player.left;
                }
            }
        }
        return Player.unknown;
    }

    private synchronized void disqualify(Player player) {
        if (player == Player.left) {
            statusFightingBeforeDisqualification = fightStatus;
            fightStatus = FightStatus.DisqualificationLeft;
        } else if (player == Player.Right) {
            statusFightingBeforeDisqualification = fightStatus;
            fightStatus = FightStatus.DisqualificationRight;
        }
    }

    synchronized void addMinusToLeft() {
        if (getWinner() != Player.unknown)
            return;

        ++countOfMinusToLeft;
        Item item = new Item(Penalty.Minus, Player.Right);
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
        for (int i = 0; i < 3; i++) {
            item.deltaLeft[i] = -Math.min(3, countOfPointsForTheLeftFighter[i]);
            item.deltaRight[i] = 3 + item.deltaLeft[i];
        }
        stackPenalty.add(item);

        if (countOfMinusToLeft == 3) {
            disqualify(Player.left);
        }
    }

    /**
     * Минус бал правому бойцу. 3 очка левому бойцу от каждого судьи.
     */
    synchronized void addMinusToRight() {
        if (getWinner() != Player.unknown)
            return;

        ++countOfMinusToRight;
        Item item = new Item(Penalty.Minus, Player.Right);
        int[] countOfPointsForTheRightFighter = getCountOfPointsForTheRightFighter();
        for (int i = 0; i < 3; i++) {
            item.deltaRight[i] = -Math.min(3, countOfPointsForTheRightFighter[i]);
            item.deltaLeft[i] = 3 + item.deltaRight[i];
        }
        stackPenalty.add(item);

        if (countOfMinusToRight == 3)
            disqualify(Player.Right);
    }

    /**
     * Одно предупреждение идет левому бойцу. Если их больше 1ого, до дисквалификация
     */
    synchronized void addForestallingToLeft() {
        if (getWinner() != Player.unknown)
            return;

        if (countOfForestallingToLeft == 0) {
            ++countOfForestallingToLeft;
            Item item = new Item(Penalty.FO, Player.left);
            stackPenalty.push(item);
        }
    }

    /**
     * Одно предупреждение идет правому бойцу. Если их больше 1ого, до дисквалификация
     */
    synchronized void addForestallingToRight() {
        if (getWinner() != Player.unknown)
            return;

        if (countOfForestallingToRight == 0) {
            ++countOfForestallingToRight;
            Item item = new Item(Penalty.FO, Player.Right);
            stackPenalty.push(item);
        }
    }

    /**
     * Левый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    synchronized void addExToLeft() {
        if (getWinner() != Player.unknown)
            return;

        ++countOfExToLeft;
        Item item = new Item(Penalty.Ex, Player.left);
        if (2 <= countOfExToLeft) {
            int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
            for (int i = 0; i < 3; i++) {
                item.deltaLeft[i] = -Math.min(3, countOfPointsForTheLeftFighter[i]);
                item.deltaRight[i] = 3 + item.deltaLeft[i];
            }
        }
        stackPenalty.add(item);

        if (4 == countOfExToLeft) {
            disqualify(Player.left);
        }
    }

    /**
     * Правый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    synchronized void addExToRight() {
        if (getWinner() != Player.unknown)
            return;

        ++countOfExToRight;
        Item item = new Item(Penalty.Ex, Player.Right);
        if (2 <= countOfExToRight) {
            int[] countOfPointsForTheRightFighter = getCountOfPointsForTheRightFighter();
            for (int i = 0; i < 3; i++) {
                item.deltaRight[i] = -Math.min(3, countOfPointsForTheRightFighter[i]);
                item.deltaLeft[i] = 3 + item.deltaRight[i];
            }
        }
        stackPenalty.add(item);

        if (4 == countOfExToRight) {
            disqualify(Player.Right);
        }
    }


    synchronized int[] getCountOfPointsForTheLeftFighter() {
        int[] count = new int[3];
        for (int round = 1; round <= currentRound; round++) {
            for (int judge = 0; judge < 3; judge++) {
                count[judge] += countOfPointsForTheLeftFighter[round][judge];
            }
        }
        for (Item item : stackPenalty) {
            for (int i = 0; i < 3; i++) {
                count[i] += item.deltaLeft[i];
            }
        }
        return count;
    }

    synchronized int[] getCountOfPointsForTheRightFighter() {
        int[] count = new int[3];
        for (int round = 1; round <= currentRound; round++) {
            for (int judge = 0; judge < 3; judge++) {
                count[judge] += countOfPointsForTheRightFighter[round][judge];
            }
        }
        for (Item item : stackPenalty) {
            for (int i = 0; i < 3; i++) {
                count[i] += item.deltaRight[i];
            }
        }
        return count;
    }

    /**
     * @return колическо судей за левого бойца
     */
    synchronized int getCountJudgeForLeftFighter() {
        int countJudgeForLeftFighter = 0;
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
        int[] countOfPointsForTheRightFighter = getCountOfPointsForTheRightFighter();
        for (int i = 0; i < 3; i++) {
            if (countOfPointsForTheLeftFighter[i] > countOfPointsForTheRightFighter[i])
                ++countJudgeForLeftFighter;
        }
        return countJudgeForLeftFighter;
    }

    /**
     * @return колическо судей за правого бойца
     */
    synchronized int getCountJudgeForRightFighter() {
        int countJudgeForRightFighter = 0;
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
        int[] countOfPointsForTheRightFighter = getCountOfPointsForTheRightFighter();
        for (int i = 0; i < 3; i++) {
            if (countOfPointsForTheLeftFighter[i] < countOfPointsForTheRightFighter[i])
                ++countJudgeForRightFighter;
        }
        return countJudgeForRightFighter;
    }

    synchronized String getStringTime() {
        if (fightStatus == FightStatus.NotStart) {
            return String.format("%02d:%02d", durationOfRound / 60, durationOfRound % 60);
        }
        if (fightStatus == FightStatus.Fighting || fightStatus == FightStatus.PauseFight) {
            long remainTime = durationOfRound - spendTime;
            return String.format("%02d:%02d", remainTime / 60, remainTime % 60);
        }
        if (fightStatus == FightStatus.Break) {
            long remainTime = durationOfBreak - spendTime;
            return String.format("%02d:%02d", remainTime / 60, remainTime % 60);
        }
        if (fightStatus == FightStatus.PendingExtraRound) {
            return String.format("%02d:%02d", durationOfExtraRound / 60, durationOfExtraRound % 60);
        }
        if (fightStatus == FightStatus.ExtraRound || fightStatus == FightStatus.PauseExtraRound) {
            return String.format("%02d:%02d", durationOfExtraRound / 60, durationOfExtraRound % 60);
        }
        return "";
    }

    synchronized FightStatus getFightStatus() {
        return fightStatus;
    }

    @Override
    public String toString() {
        String separator = " / ";
        return fightId + separator +
                nameOfLeftFighter + " " + countryOfLeftFighter + " " + separator +
                nameOfRightFighter + " " + countryOfRightFighter + " " + separator;
    }

    //------------------------------------------------------------------------------------------------------------------

    synchronized String getResult() {
        int countPointLeft = getCountJudgeForLeftFighter();
        int countPointRight = getCountJudgeForRightFighter();
        if (fightStatus == FightStatus.DisqualificationLeft || fightStatus == FightStatus.DisqualificationRight)
            return "DISQ";
        if (fightStatus == FightStatus.forceLeftWinner || fightStatus == FightStatus.forceRightWinner)
            return forceResult;

        return countPointLeft + " : " + countPointRight;
    }

    synchronized Player getWinner() {
        int countPointLeft = getCountJudgeForLeftFighter();
        int countPointRight = getCountJudgeForRightFighter();
        if (fightStatus == FightStatus.forceLeftWinner || fightStatus == FightStatus.winnerByPointsLeft || fightStatus == FightStatus.DisqualificationRight || fightStatus == FightStatus.Finish && countPointLeft > countPointRight)
            return Player.left;
        if (fightStatus == FightStatus.forceRightWinner || fightStatus == FightStatus.winnerByPointsRight || fightStatus == FightStatus.DisqualificationLeft || fightStatus == FightStatus.Finish && countPointLeft < countPointRight)
            return Player.Right;
        return Player.unknown;
    }

    synchronized void cancelLastAction() {
        if (stackPenalty.isEmpty())
            return;

        Item item = stackPenalty.pop();

        if (item.penalty == Penalty.Minus) {
            if (item.player == Player.left) {
                --countOfMinusToLeft;
                if (countOfMinusToLeft == 2 && fightStatus == FightStatus.DisqualificationLeft) {
                    fightStatus = statusFightingBeforeDisqualification;
                    statusFightingBeforeDisqualification = null;
                }
            }
            if (item.player == Player.Right) {
                --countOfMinusToRight;
                if (countOfMinusToRight == 2 && fightStatus == FightStatus.DisqualificationRight) {
                    fightStatus = statusFightingBeforeDisqualification;
                    statusFightingBeforeDisqualification = null;
                }
            }
        }

        if (item.penalty == Penalty.FO) {
            if (item.player == Player.left)
                --countOfForestallingToLeft;
            if (item.player == Player.Right)
                --countOfForestallingToRight;
        }

        if (item.penalty == Penalty.Ex) {
            if (item.player == Player.left) {
                --countOfExToLeft;
                if (countOfExToLeft == 3 && fightStatus == FightStatus.DisqualificationLeft) {
                    fightStatus = statusFightingBeforeDisqualification;
                    statusFightingBeforeDisqualification = null;
                }
            }
            if (item.player == Player.Right) {
                --countOfExToRight;
                if (countOfExToRight == 3 && fightStatus == FightStatus.DisqualificationRight) {
                    fightStatus = statusFightingBeforeDisqualification;
                    statusFightingBeforeDisqualification = null;
                }
            }
        }
    }
}

