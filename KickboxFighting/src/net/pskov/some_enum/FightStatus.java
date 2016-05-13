package net.pskov.some_enum;

public enum FightStatus {

    NotStart, Fighting, Break, PauseFight, Tie, Finish, DisqualificationLeft, DisqualificationRight,
    winnerByPointsLeft, winnerByPointsRight,
    stopedByJudge, forceLeftWinner, forceRightWinner,
    PendingExtraRound, ExtraRound, PauseExtraRound
}