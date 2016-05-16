package net.pskov;

import net.pskov.some_enum.FightStatus;
import net.pskov.some_enum.Penalty;
import net.pskov.some_enum.Player;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
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

    private long prevMomentTime;
    private long spendTime;
    private int currentRound; // номер текущего раунда

    private FightStatus fightStatus;
    private FightStatus statusFightingBeforeDisqualification;
    private FightStatus fightStatusBeforDialog;

    private int countOfMinusToLeft;
    private int countOfMinusToRight;

    private int countOfForestallingToLeft; // количесво предупреждений, сделаных левому игроку
    private int countOfForestallingToRight; // количесво предупреждений, сделаных левому игроку

    private int countOfExToLeft; // количесво предупреждений, сделаных левому игроку
    private int countOfExToRight; // количесво предупреждений, сделаных левому игроку


    private final long TOURNAMENT_CATEGORIES_FK;
    private final int VERTEX;
    private String forceResult;
    private boolean wasExtraRound;


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
    private Timer timer;

    void dispose() {
        timer.stop();
    }

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

//        this.countOfRounds = 1;
//        this.durationOfRound = 1 * 1000;
//        this.durationOfBreak = 4 * 1000;
//        this.durationOfExtraRound = 3 * 1000;
//        this.inCaseOfTie = 0;

        this.imageLeftConnerFlag = imageLeftConnerFlag;
        this.imageRightConnerFlag = imageRightConnerFlag;

        this.countryOfLeftFighter = countryOfLeftFighter;
        this.countryOfRightFighter = countryOfRightFighter;

        this.countOfPointsForTheLeftFighter = new int[this.countOfRounds + 1][3];
        this.countOfPointsForTheRightFighter = new int[this.countOfRounds + 1][3];

        {
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


        this.TOURNAMENT_CATEGORIES_FK = TOURNAMENT_CATEGORIES_FK;
        this.VERTEX = VERTEX;

        stackPenalty = new Stack<>();

        timer = new Timer(200, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateTime();
            }
        });
    }

    public void setDialog(boolean dialog) {
        if (dialog) {
            fightStatusBeforDialog = fightStatus;
            fightStatus = FightStatus.stoppedByJudge;
        } else {
            fightStatus = fightStatusBeforDialog;
        }
    }

    public void forceStopRound(Player player, String forceResult) {
        if (player == Player.Left) {
            fightStatus = FightStatus.forceLeftWinner;
            this.forceResult = forceResult;
        } else if (player == Player.Right) {
            fightStatus = FightStatus.forceRightWinner;
            this.forceResult = forceResult;
        }
    }


    private boolean isDisqOrForceWinner() {
        return fightStatus == FightStatus.DisqualificationLeft || fightStatus == FightStatus.DisqualificationRight ||
                fightStatus == FightStatus.forceLeftWinner || fightStatus == FightStatus.forceRightWinner ||
                fightStatus == FightStatus.stoppedByJudge;
    }

    void addOnePointToLeftFighter(int fromJudge) {
        if (isDisqOrForceWinner())
            return;
        ++countOfPointsForTheLeftFighter[currentRound][fromJudge];
    }

    void addOnePointToRightFighter(int fromJudge) {
        if (isDisqOrForceWinner())
            return;
        ++countOfPointsForTheRightFighter[currentRound][fromJudge];
    }

    void pressedKeySpace() {
        if (fightStatus == FightStatus.NotStart) {
            timer.start();
            fightStatus = FightStatus.Fighting;
            soundGong.play();
        } else if (fightStatus == FightStatus.Fighting)
            fightStatus = FightStatus.PauseFight;
        else if (fightStatus == FightStatus.PauseFight)
            fightStatus = FightStatus.Fighting;
        else if (fightStatus == FightStatus.PendingExtraRound) {
            fightStatus = FightStatus.ExtraRound;
            soundGong.play();
        } else if (fightStatus == FightStatus.ExtraRound)
            fightStatus = FightStatus.PauseExtraRound;
        else if (fightStatus == FightStatus.PauseExtraRound)
            fightStatus = FightStatus.ExtraRound;
    }

    private void updateTime() {
        long momentTime = System.currentTimeMillis();
        if (prevMomentTime == 0) prevMomentTime = momentTime;
        long quantum = momentTime - prevMomentTime;
//        System.err.printf("%d %d %s\n", prevMomentTime, momentTime, fightStatus);
        prevMomentTime = momentTime;


        if (fightStatus == FightStatus.Fighting) {
            spendTime += quantum;
            if (durationOfRound <= spendTime) {
                spendTime -= durationOfRound; // spendTime = 0;

                if (currentRound == countOfRounds) {
                    int l = getCountJudgeForLeftFighter();
                    int r = getCountJudgeForRightFighter();
                    if (l > r)
                        fightStatus = FightStatus.winnerByPointsLeft;
                    else if (l < r)
                        fightStatus = FightStatus.winnerByPointsRight;
                    else {
                        if (inCaseOfTie == 0) {
                            fightStatus = FightStatus.Tie;
                        } else if (inCaseOfTie == 1) {
                            Player winner = findWinnerInCaseOfTieByEuropeanRules();
                            if (winner == Player.Unknown)
                                fightStatus = FightStatus.Tie;
                            else
                                fightStatus = winner == Player.Left ? FightStatus.winnerByPointsLeft : FightStatus.winnerByPointsRight;
                        } else
                            fightStatus = FightStatus.PendingExtraRound;
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
            if (l > r)
                fightStatus = FightStatus.winnerByPointsLeft;
            else if (l < r)
                fightStatus = FightStatus.winnerByPointsRight;
        } else if (fightStatus == FightStatus.PendingExtraRound) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r)
                fightStatus = FightStatus.winnerByPointsLeft;
            else if (l < r)
                fightStatus = FightStatus.winnerByPointsRight;
        } else if (fightStatus == FightStatus.ExtraRound) {
            spendTime += quantum;
            wasExtraRound = true;
            if (durationOfExtraRound <= spendTime) {
                int l = getCountJudgeForLeftFighter();
                int r = getCountJudgeForRightFighter();
                if (l > r) {
                    fightStatus = FightStatus.winnerByPointsLeft;
                    soundGong.play();
                } else if (l < r) {
                    fightStatus = FightStatus.winnerByPointsRight;
                    soundGong.play();
                }
            }
        } else if (fightStatus == FightStatus.winnerByPointsLeft) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r) {
                fightStatus = FightStatus.winnerByPointsLeft;
            } else if (l < r) {
                fightStatus = FightStatus.winnerByPointsRight;
            } else {
                if (inCaseOfTie == 2 && !wasExtraRound)
                    fightStatus = FightStatus.PendingExtraRound;
                else
                    fightStatus = FightStatus.Tie;
            }
        } else if (fightStatus == FightStatus.winnerByPointsRight) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r) {
                fightStatus = FightStatus.winnerByPointsLeft;
            } else if (l < r) {
                fightStatus = FightStatus.winnerByPointsRight;
            } else {
                if (inCaseOfTie == 2 && !wasExtraRound)
                    fightStatus = FightStatus.PendingExtraRound;
                else
                    fightStatus = FightStatus.Tie;
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
                    return Player.Left;
                }
            }
        }
        return Player.Unknown;
    }

    private void disqualify(Player player) {
        if (player == Player.Left) {
            statusFightingBeforeDisqualification = fightStatus;
            fightStatus = FightStatus.DisqualificationLeft;
        } else if (player == Player.Right) {
            statusFightingBeforeDisqualification = fightStatus;
            fightStatus = FightStatus.DisqualificationRight;
        }
    }

    void addMinusToLeft() {
        if (isDisqOrForceWinner())
            return;

        ++countOfMinusToLeft;
        Item item = new Item(Penalty.Minus, Player.Left);
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
        for (int i = 0; i < 3; i++) {
            item.deltaLeft[i] = -Math.min(3, countOfPointsForTheLeftFighter[i]);
            item.deltaRight[i] = 3 + item.deltaLeft[i];
        }
        stackPenalty.add(item);

        if (countOfMinusToLeft == 3) {
            disqualify(Player.Left);
        }
    }

    /**
     * Минус бал правому бойцу. 3 очка левому бойцу от каждого судьи.
     */
    void addMinusToRight() {
        if (isDisqOrForceWinner())
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
    void addForestallingToLeft() {
        if (isDisqOrForceWinner())
            return;

        if (countOfForestallingToLeft == 0) {
            ++countOfForestallingToLeft;
            Item item = new Item(Penalty.FO, Player.Left);
            stackPenalty.push(item);
        }
    }

    /**
     * Одно предупреждение идет правому бойцу. Если их больше 1ого, до дисквалификация
     */
    void addForestallingToRight() {
        if (isDisqOrForceWinner())
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
    void addExToLeft() {
        if (isDisqOrForceWinner())
            return;

        ++countOfExToLeft;
        Item item = new Item(Penalty.Ex, Player.Left);
        if (2 <= countOfExToLeft) {
            int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
            for (int i = 0; i < 3; i++) {
                item.deltaLeft[i] = -Math.min(3, countOfPointsForTheLeftFighter[i]);
                item.deltaRight[i] = 3 + item.deltaLeft[i];
            }
        }
        stackPenalty.add(item);

        if (4 == countOfExToLeft) {
            disqualify(Player.Left);
        }
    }

    /**
     * Правый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    void addExToRight() {
        if (isDisqOrForceWinner())
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


    int[] getCountOfPointsForTheLeftFighter() {
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

    int[] getCountOfPointsForTheRightFighter() {
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
    int getCountJudgeForLeftFighter() {
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
    int getCountJudgeForRightFighter() {
        int countJudgeForRightFighter = 0;
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForTheLeftFighter();
        int[] countOfPointsForTheRightFighter = getCountOfPointsForTheRightFighter();
        for (int i = 0; i < 3; i++) {
            if (countOfPointsForTheLeftFighter[i] < countOfPointsForTheRightFighter[i])
                ++countJudgeForRightFighter;
        }
        return countJudgeForRightFighter;
    }

    String getStringTime() {
        if (fightStatus == FightStatus.NotStart) {
            return String.format("%02d:%02d", durationOfRound / 1000 / 60, durationOfRound / 1000 % 60);
        }
        if (fightStatus == FightStatus.Fighting || fightStatus == FightStatus.PauseFight) {
            long remainTime = Math.max(0, durationOfRound - spendTime);
            return String.format("%02d:%02d", remainTime / 1000 / 60, remainTime / 1000 % 60);
        }
        if (fightStatus == FightStatus.Break) {
            long remainTime = Math.max(0, durationOfBreak - spendTime);
            return String.format("%02d:%02d", remainTime / 1000 / 60, remainTime / 1000 % 60);
        }
        if (fightStatus == FightStatus.PendingExtraRound) {
            return String.format("%02d:%02d", durationOfExtraRound / 1000 / 60, durationOfExtraRound / 1000 % 60);
        }
        if (fightStatus == FightStatus.ExtraRound || fightStatus == FightStatus.PauseExtraRound) {
            long remainTime = Math.max(0, durationOfExtraRound - spendTime);
            return String.format("%02d:%02d", remainTime / 1000 / 60, remainTime / 1000 % 60);
        }
        return "";
    }

    FightStatus getFightStatus() {
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

    String getResult() {
        int countPointLeft = getCountJudgeForLeftFighter();
        int countPointRight = getCountJudgeForRightFighter();
        if (fightStatus == FightStatus.DisqualificationLeft || fightStatus == FightStatus.DisqualificationRight)
            return "DISQ";
        if (fightStatus == FightStatus.forceLeftWinner || fightStatus == FightStatus.forceRightWinner)
            return forceResult;

        return countPointLeft + " : " + countPointRight;
    }

    Player getWinner() {
        if (fightStatus == FightStatus.forceLeftWinner || fightStatus == FightStatus.winnerByPointsLeft || fightStatus == FightStatus.DisqualificationRight)
            return Player.Left;
        if (fightStatus == FightStatus.forceRightWinner || fightStatus == FightStatus.winnerByPointsRight || fightStatus == FightStatus.DisqualificationLeft)
            return Player.Right;
        return Player.Unknown;
    }

    void cancelLastAction() {
        if (stackPenalty.isEmpty() || fightStatus == FightStatus.stoppedByJudge)
            return;

        Item item = stackPenalty.pop();

        if (item.penalty == Penalty.Minus) {
            if (item.player == Player.Left) {
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
            if (item.player == Player.Left)
                --countOfForestallingToLeft;
            if (item.player == Player.Right)
                --countOfForestallingToRight;
        }

        if (item.penalty == Penalty.Ex) {
            if (item.player == Player.Left) {
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


    public int getCountOfExToLeft() {
        return countOfExToLeft;
    }

    public String getCategoryOfFighting() {
        return categoryOfFighting;
    }

    public int getCountOfExToRight() {
        return countOfExToRight;
    }

    public int getCountOfForestallingToLeft() {
        return countOfForestallingToLeft;
    }

    public int getCountOfForestallingToRight() {
        return countOfForestallingToRight;
    }

    public int getCountOfMinusToLeft() {
        return countOfMinusToLeft;
    }

    public int getCountOfMinusToRight() {
        return countOfMinusToRight;
    }

    public int getCountOfRounds() {
        return countOfRounds;
    }

    public String getCountryOfLeftFighter() {
        return countryOfLeftFighter;
    }

    public String getCountryOfRightFighter() {
        return countryOfRightFighter;
    }

    public int getCurrentRound() {
        return currentRound;
    }

    public int getFightId() {
        return fightId;
    }

    public BufferedImage getImageLeftConnerFlag() {
        return imageLeftConnerFlag;
    }

    public BufferedImage getImageRightConnerFlag() {
        return imageRightConnerFlag;
    }

    public String getNameOfLeftFighter() {
        return nameOfLeftFighter;
    }

    public String getNameOfRightFighter() {
        return nameOfRightFighter;
    }

    public long getTOURNAMENT_CATEGORIES_FK() {
        return TOURNAMENT_CATEGORIES_FK;
    }

    public int getVERTEX() {
        return VERTEX;
    }
}

