package net.pskov.utils;


import net.pskov.ModelFight;
import net.pskov.some_enum.Player;
import net.pskov.some_enum.PointPanelMode;
import net.pskov.some_enum.TypePenalty;

public class ReportUtis {
    public static String getOpeningSystem(ModelFight f) {
        StringBuilder sb = new StringBuilder();
        sb.append("<html>\n" +
                "<body>\n");

        for (Player player : new Player[]{Player.Left, Player.Right}) {
            sb.append("<p>\n");
            sb.append("<table  cellspacing=\"0\" border=\"1\">\n");
            sb.append("    <caption>").append(player == Player.Left ? "Red conner: " + f.getNameOfLeftFighter() : "Blue conner: " + f.getNameOfRightFighter()).append("</caption>");
            sb.append("    <tr><td>&nbsp;</td><th>Judge #1</th><th>Judge #2</th><th>Judge #3</th></tr>\n");
            for (int round = 0; round < f.getCountOfRounds() + (f.getWasExtraRound() ? 1 : 0); round++) {
                sb.append("    <tr>");
                if (round < f.getCountOfRounds())
                    sb.append("<th>").append("Round #").append(round + 1).append("</th>");
                else
                    sb.append("<th>").append("Extra round").append("</th>");
                for (int judge = 0; judge < 3; judge++) {
                    sb.append("<td>").append(f.getCountOfClicksOfMouse(player, judge, round)).append("</td>");
                }
                sb.append("</tr>\n");
            }
            sb.append("</table>\n");
            sb.append("</p>\n");
            sb.append("\n");
        }


        sb.append("<p>\n");
        sb.append("<table  cellspacing=\"0\" border=\"1\">\n");
        sb.append("    <caption>").append("Penalty").append("</caption>");
        sb.append("    <tr><td>&nbsp;</td><th>Red conner</th><th>Blue conner</th></tr>\n");
        for (TypePenalty typePenalty : new TypePenalty[]{TypePenalty.Minus, TypePenalty.Warning, TypePenalty.Exit, TypePenalty.KnockDown}) {
            if (typePenalty == TypePenalty.Exit && f.getPointPanelMode() != PointPanelMode.LightContact ||
                    typePenalty == TypePenalty.KnockDown && f.getPointPanelMode() != PointPanelMode.K1 && f.getPointPanelMode() != PointPanelMode.FullContact)
                continue;
            String str = "";
            if (typePenalty == TypePenalty.Minus)
                str = "Minus";
            else if (typePenalty == TypePenalty.Warning)
                str = "Fo";
            else if (typePenalty == TypePenalty.Exit)
                str = "Exit";
            else if (typePenalty == TypePenalty.KnockDown)
                str = "Knock down";
            sb.append("    <tr><th>")
                    .append(str)
                    .append("</th><td>")
                    .append(f.getCountOfPenalty(Player.Left, typePenalty))
                    .append("</td><td>")
                    .append(f.getCountOfPenalty(Player.Right, typePenalty))
                    .append("</td></tr>\n");
        }
        sb.append("</table>\n");
        sb.append("</p>\n");
        sb.append("\n");

        if (f.getPointPanelMode() == PointPanelMode.FullContact) {
            sb.append("<p>\n");
            sb.append("<table cellspacing=\"0\" border=\"1\">\n");
            sb.append("    <caption>").append("Kick count").append("</caption>");
            sb.append("    <tr><td>&nbsp;</td><th>Red conner</th><th>Blue conner</th></tr>\n");
            for (int round = 0; round < f.getCountOfRounds() + (f.getWasExtraRound() ? 1 : 0); round++) {
                sb.append("    <tr><th>");
                if (round < f.getCountOfRounds())
                    sb.append("Round #").append(round + 1);
                else
                    sb.append("Extra round");
                sb.append("</th><td>")
                        .append(f.getCountOfKickCountToLeftForRound(round))
                        .append("</td><td>")
                        .append(f.getCountOfKickCountToRightForRound(round))
                        .append("</td></tr>\n");
            }
            sb.append("</table>\n");
            sb.append("</p>\n");
            sb.append("\n");
        }


        Player winner = f.getWinner();
        if (winner != Player.NoPlayer) {
            sb.append("<p>\n")
                    .append("Winner: ")
                    .append(winner == Player.Left ? f.getNameOfLeftFighter() : f.getNameOfRightFighter())
                    .append(" (").append(winner == Player.Left ? "red conner" : "blue conner").append(")")
                    .append("\n")
                    .append("</p>\n")
                    .append("<p>\n")
                    .append("Result: ").append(f.getResult())
                    .append("</p>\n");
        }

        sb.append("</body>\n" +
                "</html>\n");
        System.err.println(sb.toString());
        return sb.toString();
    }
}
