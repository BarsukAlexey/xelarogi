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
    private static final Sound soundHummerBit = new Sound(new File("resources\\sounds\\stuk_molotka.wav"));


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

    private FightStatus status;
    private FightStatus statusBeforDisqualification;
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

            status = FightStatus.NotStart;
            statusBeforDisqualification = null;

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
            fightStatusBeforDialog = status;
            status = FightStatus.stoppedByJudge;
        } else {
            status = fightStatusBeforDialog;
        }
    }

    public void forceStopRound(Player player, String forceResult) {
        if (player == Player.Left) {
            status = FightStatus.forceLeftWinner;
            this.forceResult = forceResult;
        } else if (player == Player.Right) {
            status = FightStatus.forceRightWinner;
            this.forceResult = forceResult;
        }
    }


    private boolean isDisqOrForceWinner() {
        return status == FightStatus.DisqualificationLeft || status == FightStatus.DisqualificationRight ||
                status == FightStatus.forceLeftWinner || status == FightStatus.forceRightWinner ||
                status == FightStatus.stoppedByJudge;
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
        if (status == FightStatus.NotStart) {
            timer.start();
            status = FightStatus.Fight;
            soundGong.play();
        } else if (status == FightStatus.Fight)
            status = FightStatus.PauseFight;
        else if (status == FightStatus.PauseFight)
            status = FightStatus.Fight;
        else if (status == FightStatus.PendingExtraRound) {
            status = FightStatus.ExtraRound;
            soundGong.play();
        } else if (status == FightStatus.ExtraRound)
            status = FightStatus.PauseExtraRound;
        else if (status == FightStatus.PauseExtraRound)
            status = FightStatus.ExtraRound;
    }

    private void updateTime() {
        long momentTime = System.currentTimeMillis();
        if (prevMomentTime == 0) prevMomentTime = momentTime;
        long quantum = momentTime - prevMomentTime;
//        System.err.printf("%d %d %s\n", prevMomentTime, momentTime, status);
        prevMomentTime = momentTime;


        if (status == FightStatus.Fight) {
            spendTime += quantum;
            if (durationOfRound <= spendTime) {
                spendTime -= durationOfRound; // spendTime = 0;

                if (currentRound == countOfRounds) {
                    int l = getCountJudgeForLeftFighter();
                    int r = getCountJudgeForRightFighter();
                    if (l > r)
                        status = FightStatus.winnerByPointsLeft;
                    else if (l < r)
                        status = FightStatus.winnerByPointsRight;
                    else {
                        if (inCaseOfTie == 0) {
                            status = FightStatus.Tie;
                        } else if (inCaseOfTie == 1) {
                            Player winner = findWinnerInCaseOfTieByEuropeanRules();
                            if (winner == Player.NoPlayer)
                                status = FightStatus.Tie;
                            else
                                status = winner == Player.Left ? FightStatus.winnerByPointsLeft : FightStatus.winnerByPointsRight;
                        } else
                            status = FightStatus.PendingExtraRound;
                    }
                } else {
                    status = FightStatus.Break;
                }
                soundGong.play();
            }
        } else if (status == FightStatus.Break) {
            spendTime += quantum;
            if (durationOfBreak - spendTime <= 10 * 1000 && !soundHummerBit.isPlaying()) {
                soundHummerBit.play();
            }
            if (durationOfBreak <= spendTime) {
                spendTime -= durationOfBreak; // spendTime = 0;

                status = FightStatus.Fight;
                ++currentRound;

                soundHummerBit.stop();
                soundGong.play();
            }
        } else if (status == FightStatus.Tie) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r)
                status = FightStatus.winnerByPointsLeft;
            else if (l < r)
                status = FightStatus.winnerByPointsRight;
        } else if (status == FightStatus.PendingExtraRound) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r)
                status = FightStatus.winnerByPointsLeft;
            else if (l < r)
                status = FightStatus.winnerByPointsRight;
        } else if (status == FightStatus.ExtraRound) {
            spendTime += quantum;
            wasExtraRound = true;
            if (durationOfExtraRound <= spendTime) {
                int l = getCountJudgeForLeftFighter();
                int r = getCountJudgeForRightFighter();
                if (l > r) {
                    status = FightStatus.winnerByPointsLeft;
                    soundGong.play();
                } else if (l < r) {
                    status = FightStatus.winnerByPointsRight;
                    soundGong.play();
                }
            }
        } else if (status == FightStatus.winnerByPointsLeft) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r) {
                status = FightStatus.winnerByPointsLeft;
            } else if (l < r) {
                status = FightStatus.winnerByPointsRight;
            } else {
                if (inCaseOfTie == 2 && !wasExtraRound)
                    status = FightStatus.PendingExtraRound;
                else
                    status = FightStatus.Tie;
            }
        } else if (status == FightStatus.winnerByPointsRight) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r) {
                status = FightStatus.winnerByPointsLeft;
            } else if (l < r) {
                status = FightStatus.winnerByPointsRight;
            } else {
                if (inCaseOfTie == 2 && !wasExtraRound)
                    status = FightStatus.PendingExtraRound;
                else
                    status = FightStatus.Tie;
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
        return Player.NoPlayer;
    }

    private void disqualify(Player player) {
        if (player == Player.Left) {
            statusBeforDisqualification = status;
            status = FightStatus.DisqualificationLeft;
        } else if (player == Player.Right) {
            statusBeforDisqualification = status;
            status = FightStatus.DisqualificationRight;
        }
    }

    void addMinusToLeft() {
        if (isDisqOrForceWinner())
            return;

        ++countOfMinusToLeft;
        Item item = new Item(Penalty.Minus, Player.Left);
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
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
        int[] countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
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
            int[] countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
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
            int[] countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
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


    int[] getCountOfPointsForLeftFighter() {
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

    int[] getCountOfPointsForRightFighter() {
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
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
        int[] countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
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
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
        int[] countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
        for (int i = 0; i < 3; i++) {
            if (countOfPointsForTheLeftFighter[i] < countOfPointsForTheRightFighter[i])
                ++countJudgeForRightFighter;
        }
        return countJudgeForRightFighter;
    }

    String getStringTime() {
        if (status == FightStatus.NotStart) {
            return String.format("%02d:%02d", durationOfRound / 1000 / 60, durationOfRound / 1000 % 60);
        }
        if (status == FightStatus.Fight || status == FightStatus.PauseFight) {
            long remainTime = Math.max(0, durationOfRound - spendTime);
            return String.format("%02d:%02d", remainTime / 1000 / 60, remainTime / 1000 % 60);
        }
        if (status == FightStatus.Break) {
            long remainTime = Math.max(0, durationOfBreak - spendTime);
            return String.format("%02d:%02d", remainTime / 1000 / 60, remainTime / 1000 % 60);
        }
        if (status == FightStatus.PendingExtraRound) {
            return String.format("%02d:%02d", durationOfExtraRound / 1000 / 60, durationOfExtraRound / 1000 % 60);
        }
        if (status == FightStatus.ExtraRound || status == FightStatus.PauseExtraRound) {
            long remainTime = Math.max(0, durationOfExtraRound - spendTime);
            return String.format("%02d:%02d", remainTime / 1000 / 60, remainTime / 1000 % 60);
        }
        return "";
    }

    FightStatus getStatus() {
        return status;
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
        if (status == FightStatus.DisqualificationLeft || status == FightStatus.DisqualificationRight)
            return "DISQ";
        if (status == FightStatus.forceLeftWinner || status == FightStatus.forceRightWinner)
            return forceResult;

        return countPointLeft + " : " + countPointRight;
    }

    Player getWinner() {
        if (status == FightStatus.forceLeftWinner || status == FightStatus.winnerByPointsLeft || status == FightStatus.DisqualificationRight)
            return Player.Left;
        if (status == FightStatus.forceRightWinner || status == FightStatus.winnerByPointsRight || status == FightStatus.DisqualificationLeft)
            return Player.Right;
        return Player.NoPlayer;
    }

    void cancelLastAction() {
        if (stackPenalty.isEmpty() || status == FightStatus.stoppedByJudge)
            return;

        Item item = stackPenalty.pop();

        if (item.penalty == Penalty.Minus) {
            if (item.player == Player.Left) {
                --countOfMinusToLeft;
                if (countOfMinusToLeft == 2 && status == FightStatus.DisqualificationLeft) {
                    status = statusBeforDisqualification;
                    statusBeforDisqualification = null;
                }
            }
            if (item.player == Player.Right) {
                --countOfMinusToRight;
                if (countOfMinusToRight == 2 && status == FightStatus.DisqualificationRight) {
                    status = statusBeforDisqualification;
                    statusBeforDisqualification = null;
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
                if (countOfExToLeft == 3 && status == FightStatus.DisqualificationLeft) {
                    status = statusBeforDisqualification;
                    statusBeforDisqualification = null;
                }
            }
            if (item.player == Player.Right) {
                --countOfExToRight;
                if (countOfExToRight == 3 && status == FightStatus.DisqualificationRight) {
                    status = statusBeforDisqualification;
                    statusBeforDisqualification = null;
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

