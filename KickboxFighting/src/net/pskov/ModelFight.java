package net.pskov;

import net.pskov.some_enum.FightStatus;
import net.pskov.some_enum.Player;
import net.pskov.some_enum.PointPanelMode;
import net.pskov.some_enum.TypePenalty;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Stack;


public class ModelFight {

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
    private final PointPanelMode pointPanelMode;

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
    private FightStatus statusBeforeDisqualification;
    private FightStatus fightStatusBeforeDialog;

    private int countOfMinusToLeft;
    private int countOfMinusToRight;

    private int countOfForestallingToLeft; // количесво предупреждений, сделаных левому игроку
    private int countOfForestallingToRight; // количесво предупреждений, сделаных левому игроку

    private int countOfExToLeft; // количесво предупреждений, сделаных левому игроку
    private int countOfExToRight; // количесво предупреждений, сделаных левому игроку

    private int countOfKnockDownToLeft;
    private int countOfKnockDownToRight;

    private int[] countOfKickCountToLeft;
    private int[] countOfKickCountToRight;
    private int countOfKickCountToLeftInt;
    private int countOfKickCountToRightInt;

    private final long TOURNAMENT_CATEGORIES_FK;
    private final int VERTEX;
    private String forceResult;
    private boolean wasExtraRound;

    public PointPanelMode getPointPanelMode() {
        return pointPanelMode;
    }

    public int getCountOfKnockDownToLeft() {
        return countOfKnockDownToLeft;
    }

    public int getCountOfKnockDownToRight() {
        return countOfKnockDownToRight;
    }

    public int getCountOfKickCountToLeft() {
        return countOfKickCountToLeftInt;
    }

    public int getCountOfKickCountToRight() {
        return countOfKickCountToRightInt;
    }

    public int getCountOfKickCountToLeftForRound(int round) {
        return countOfKickCountToLeft[round];
    }

    public int getCountOfKickCountToRightForRound(int round) {
        return countOfKickCountToRight[round];
    }


    private static class Penalty {
        private TypePenalty typePenalty;
        private Player player;
        private int[] deltaLeft; //
        private int[] deltaRight; //
        private int round;


        Penalty(TypePenalty typePenalty, Player player) {
            this(typePenalty, player, -1);
        }

        Penalty(TypePenalty typePenalty, Player player, int round) {
            this.typePenalty = typePenalty;
            this.player = player;
            deltaLeft = new int[3];
            deltaRight = new int[3];
            this.round = round;
        }
    }

    private Stack<Penalty> stackPenalty;
    private Timer timer;

    void dispose() {
        timer.stop();
    }

    ModelFight(
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
            int VERTEX,

            PointPanelMode pointPanelMode
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
        this.pointPanelMode = pointPanelMode;


        /*/
//        this.countOfRounds = 1;
//        this.durationOfRound = 1 * 1000;
//        this.durationOfBreak = 2 * 1000;
//        this.durationOfExtraRound = 3 * 1000;
//        this.inCaseOfTie = 2;
        /**/


        this.imageLeftConnerFlag = imageLeftConnerFlag;
        this.imageRightConnerFlag = imageRightConnerFlag;

        this.countryOfLeftFighter = countryOfLeftFighter;
        this.countryOfRightFighter = countryOfRightFighter;

        this.countOfPointsForTheLeftFighter = new int[this.countOfRounds + 1][3]; //  + 1 чтобы хранить экстрараунд
        this.countOfPointsForTheRightFighter = new int[this.countOfRounds + 1][3];

        this.countOfKickCountToLeft = new int[this.countOfRounds + 1];
        this.countOfKickCountToRight = new int[this.countOfRounds + 1];

        {
            spendTime = 0;
            currentRound = 0;

            status = FightStatus.NotStart;
            statusBeforeDisqualification = null;

            countOfMinusToLeft = 0;
            countOfMinusToRight = 0;

            countOfForestallingToLeft = 0;
            countOfForestallingToRight = 0;

            countOfExToLeft = 0;
            countOfExToRight = 0;

            countOfKnockDownToLeft = 0;
            countOfKnockDownToRight = 0;

            this.countOfKickCountToLeftInt = 6;
            this.countOfKickCountToRightInt = 6;
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
            fightStatusBeforeDialog = status;
            status = FightStatus.stoppedByJudge;
        } else {
            status = fightStatusBeforeDialog;
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
        if (isDisqOrForceWinner() || status == FightStatus.Break)
            return;
        ++countOfPointsForTheLeftFighter[currentRound][fromJudge];
    }

    void addOnePointToRightFighter(int fromJudge) {
        if (isDisqOrForceWinner() || status == FightStatus.Break)
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
            if (pointPanelMode == PointPanelMode.FullContact) {
                countOfKickCountToLeftInt += 6;
                countOfKickCountToRightInt += 6;
            }
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

                if (currentRound + 1 == countOfRounds) {
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

                countOfKickCountToLeftInt += 6;
                countOfKickCountToRightInt += 6;

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
            currentRound = countOfRounds;
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
        } else if (status == FightStatus.winnerByPointsLeft || status == FightStatus.winnerByPointsRight) {
            int l = getCountJudgeForLeftFighter();
            int r = getCountJudgeForRightFighter();
            if (l > r) {
                status = FightStatus.winnerByPointsLeft;
            } else if (l < r) {
                status = FightStatus.winnerByPointsRight;
            } else {
                if (inCaseOfTie == 2 && !wasExtraRound)
                    status = FightStatus.PendingExtraRound;
                else if (inCaseOfTie == 1) {
                    Player winner = findWinnerInCaseOfTieByEuropeanRules();
                    if (winner == Player.NoPlayer) {
                        status = FightStatus.Tie;
                    } else {
                        status = winner == Player.Left ? FightStatus.winnerByPointsLeft : FightStatus.winnerByPointsRight;
                    }
                } else {
                    status = FightStatus.Tie;
                }
            }
        }
    }


    private Player findWinnerInCaseOfTieByEuropeanRules() {
        int countJudgeForLeft = 0;
        int countJudgeForRight = 0;
        for (int idJudge = 0; idJudge < 3; idJudge++) {
            int countPointLeftOverAllRounds = 0;
            int countPointRightOverAllRounds = 0;
            for (int round = 0; round < countOfRounds; round++) {
                countPointLeftOverAllRounds += countOfPointsForTheLeftFighter[round][idJudge];
                countPointRightOverAllRounds += countOfPointsForTheRightFighter[round][idJudge];
            }
            if (countPointLeftOverAllRounds == countPointRightOverAllRounds) {
                int l = countOfPointsForTheLeftFighter[countOfRounds - 1][idJudge];
                int r = countOfPointsForTheRightFighter[countOfRounds - 1][idJudge];
                if (l < r) {
                    ++countJudgeForRight;
                } else if (l > r) {
                    ++countJudgeForLeft;
                }
            }
        }
        if (countJudgeForLeft < countJudgeForRight)
            return Player.Right;
        if (countJudgeForLeft > countJudgeForRight)
            return Player.Left;
        return Player.NoPlayer;
    }

    private void disqualify(Player player) {
        if (player == Player.Left) {
            statusBeforeDisqualification = status;
            status = FightStatus.DisqualificationLeft;
        } else if (player == Player.Right) {
            statusBeforeDisqualification = status;
            status = FightStatus.DisqualificationRight;
        }
    }

    void addMinusToLeft() {
        if (isDisqOrForceWinner())
            return;

        ++countOfMinusToLeft;
        Penalty penalty = new Penalty(TypePenalty.Minus, Player.Left);
        int[] countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
        for (int i = 0; i < 3; i++) {
            penalty.deltaLeft[i] = -Math.min(3, countOfPointsForTheLeftFighter[i]);
            penalty.deltaRight[i] = 3 + penalty.deltaLeft[i];
        }
        stackPenalty.add(penalty);

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
        Penalty penalty = new Penalty(TypePenalty.Minus, Player.Right);
        int[] countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
        for (int i = 0; i < 3; i++) {
            penalty.deltaRight[i] = -Math.min(3, countOfPointsForTheRightFighter[i]);
            penalty.deltaLeft[i] = 3 + penalty.deltaRight[i];
        }
        stackPenalty.add(penalty);

        if (countOfMinusToRight == 3)
            disqualify(Player.Right);
    }

    /**
     * Одно предупреждение идет левому бойцу
     */
    void addForestallingToLeft() {
        if (countOfForestallingToLeft <= 3) {
            ++countOfForestallingToLeft;
            Penalty penalty = new Penalty(TypePenalty.Warning, Player.Left);
            stackPenalty.push(penalty);
        }
    }

    /**
     * Одно предупреждение идет правому бойцу
     */
    void addForestallingToRight() {
        if (countOfForestallingToRight <= 3) {
            ++countOfForestallingToRight;
            Penalty penalty = new Penalty(TypePenalty.Warning, Player.Right);
            stackPenalty.push(penalty);
        }
    }

    /**
     * Левый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    void addExToLeft() {
        if (pointPanelMode != PointPanelMode.LightContact)
            return;
//        if (isDisqOrForceWinner())
//            return;
        if (countOfExToLeft <= 3) {
            ++countOfExToLeft;
            Penalty penalty = new Penalty(TypePenalty.Exit, Player.Left);
// Не удалять закомментированный код, ибо правила постоянно меняются
//        if (2 <= countOfExToLeft) {
//            int[] countOfPointsForTheLeftFighter = getCountOfPointsForLeftFighter();
//            for (int i = 0; i < 3; i++) {
//                penalty.deltaLeft[i] = -Math.min(3, countOfPointsForTheLeftFighter[i]);
//                penalty.deltaRight[i] = 3 + penalty.deltaLeft[i];
//            }
//        }

            stackPenalty.add(penalty);
        }

//        if (4 == countOfExToLeft) {
//            disqualify(Player.Left);
//        }
    }

    /**
     * Правый боец вышел за ринг. Если 4 выхода, то дисквалификация
     */
    void addExToRight() {
        if (pointPanelMode != PointPanelMode.LightContact)
            return;
//        if (isDisqOrForceWinner())
//            return;

        if (countOfExToRight <= 3) {
            ++countOfExToRight;
            Penalty penalty = new Penalty(TypePenalty.Exit, Player.Right);
// Не удалять закомментированный код, ибо правила постоянно меняются
//        if (2 <= countOfExToRight) {
//            int[] countOfPointsForTheRightFighter = getCountOfPointsForRightFighter();
//            for (int i = 0; i < 3; i++) {
//                penalty.deltaRight[i] = -Math.min(3, countOfPointsForTheRightFighter[i]);
//                penalty.deltaLeft[i] = 3 + penalty.deltaRight[i];
//            }
//        }

            stackPenalty.add(penalty);
        }

//        if (4 == countOfExToRight) {
//            disqualify(Player.Right);
//        }
    }

    public void addKnockDownToLeft() {
        if (!(pointPanelMode == PointPanelMode.K1 || pointPanelMode == PointPanelMode.FullContact))
            return;
        if (countOfKnockDownToLeft <= 3) {
            countOfKnockDownToLeft++;
            stackPenalty.add(new Penalty(TypePenalty.KnockDown, Player.Left));
        }
    }

    public void addKnockDownToRight() {
        if (!(pointPanelMode == PointPanelMode.K1 || pointPanelMode == PointPanelMode.FullContact))
            return;
        if (countOfKnockDownToRight <= 3) {
            countOfKnockDownToRight++;
            stackPenalty.add(new Penalty(TypePenalty.KnockDown, Player.Right));
        }
    }

    public void addKickCountToLeft() {
        if (pointPanelMode != PointPanelMode.FullContact)
            return;
        if (0 < countOfKickCountToLeftInt) {
            --countOfKickCountToLeftInt;
            ++countOfKickCountToLeft[currentRound];
            stackPenalty.add(new Penalty(TypePenalty.KickCount, Player.Left, currentRound));
        }
    }

    public void addKickCountToRight() {
        if (pointPanelMode != PointPanelMode.FullContact)
            return;
        if (0 < countOfKickCountToRightInt) {
            --countOfKickCountToRightInt;
            ++countOfKickCountToRight[currentRound];
            stackPenalty.add(new Penalty(TypePenalty.KickCount, Player.Right, currentRound));
        }
    }


    public int[] getCountOfPointsForLeftFighter() {
        int[] count = new int[3];
        for (int round = 0; round <= currentRound; round++) {
            for (int judge = 0; judge < 3; judge++) {
                count[judge] += countOfPointsForTheLeftFighter[round][judge];
            }
        }
        for (Penalty penalty : stackPenalty) {
            for (int i = 0; i < 3; i++) {
                count[i] += penalty.deltaLeft[i];
            }
        }
        return count;
    }

    public int[] getCountOfPointsForRightFighter() {
        int[] count = new int[3];
        for (int round = 0; round <= currentRound; round++) {
            for (int judge = 0; judge < 3; judge++) {
                count[judge] += countOfPointsForTheRightFighter[round][judge];
            }
        }
        for (Penalty penalty : stackPenalty) {
            for (int i = 0; i < 3; i++) {
                count[i] += penalty.deltaRight[i];
            }
        }
        return count;
    }

    public int getCountOfClicksOfMouse(Player player, int judge, int round) {
        if (player == Player.Left)
            return countOfPointsForTheLeftFighter[round][judge];
        else if (player == Player.Right)
            return countOfPointsForTheRightFighter[round][judge];
        return -1;
    }

    public int getCountOfPenalty(Player player, TypePenalty typePenalty) {
        int count = 0;
        for (Penalty penalty : stackPenalty) {
            if (penalty.typePenalty == typePenalty && penalty.player == player) {
                ++count;
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

    public String getResult() {
        int countPointLeft = getCountJudgeForLeftFighter();
        int countPointRight = getCountJudgeForRightFighter();
        if (status == FightStatus.DisqualificationLeft || status == FightStatus.DisqualificationRight)
            return "DISQ";
        if (status == FightStatus.forceLeftWinner || status == FightStatus.forceRightWinner)
            return forceResult;

        return countPointLeft + " : " + countPointRight;
    }

    public Player getWinner() {
        if (status == FightStatus.forceLeftWinner || status == FightStatus.winnerByPointsLeft || status == FightStatus.DisqualificationRight)
            return Player.Left;
        if (status == FightStatus.forceRightWinner || status == FightStatus.winnerByPointsRight || status == FightStatus.DisqualificationLeft)
            return Player.Right;
        return Player.NoPlayer;
    }

    void cancelLastAction() {
        if (stackPenalty.isEmpty() || status == FightStatus.stoppedByJudge)
            return;

        Penalty penalty = stackPenalty.pop();

        if (penalty.typePenalty == TypePenalty.Minus) {
            if (penalty.player == Player.Left) {
                --countOfMinusToLeft;
                if (countOfMinusToLeft == 2 && status == FightStatus.DisqualificationLeft) {
                    status = statusBeforeDisqualification;
                    statusBeforeDisqualification = null;
                }
            }
            if (penalty.player == Player.Right) {
                --countOfMinusToRight;
                if (countOfMinusToRight == 2 && status == FightStatus.DisqualificationRight) {
                    status = statusBeforeDisqualification;
                    statusBeforeDisqualification = null;
                }
            }
        }

        if (penalty.typePenalty == TypePenalty.Warning) {
            if (penalty.player == Player.Left)
                --countOfForestallingToLeft;
            if (penalty.player == Player.Right)
                --countOfForestallingToRight;
        }

        if (penalty.typePenalty == TypePenalty.Exit) {
            if (penalty.player == Player.Left) {
                --countOfExToLeft;
                if (countOfExToLeft == 3 && status == FightStatus.DisqualificationLeft) {
                    status = statusBeforeDisqualification;
                    statusBeforeDisqualification = null;
                }
            }
            if (penalty.player == Player.Right) {
                --countOfExToRight;
                if (countOfExToRight == 3 && status == FightStatus.DisqualificationRight) {
                    status = statusBeforeDisqualification;
                    statusBeforeDisqualification = null;
                }
            }
        }

        if (penalty.typePenalty == TypePenalty.KnockDown) {
            if (penalty.player == Player.Left) {
                --countOfKnockDownToLeft;
            }
            if (penalty.player == Player.Right) {
                --countOfKnockDownToRight;
            }
        }

        if (penalty.typePenalty == TypePenalty.KickCount) {
            if (penalty.player == Player.Left) {
                --countOfKickCountToLeft[penalty.round];
                ++countOfKickCountToLeftInt;
            }
            if (penalty.player == Player.Right) {
                --countOfKickCountToRight[penalty.round];
                ++countOfKickCountToRightInt;
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
        return currentRound + 1;
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

    public boolean getWasExtraRound() {
        return wasExtraRound;
    }
}

