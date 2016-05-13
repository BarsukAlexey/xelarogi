package net.pskov;

import net.pskov.some_enum.Player;
import net.pskov.some_enum.FightStatus;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Rectangle2D;

class JFrameScoreTable extends JDialog {

    private boolean isThisForJudge;
    private Fighting f;

    JFrameScoreTable(boolean isThisForJudge, Rectangle bound, Fighting f) {
        super();
        this.isThisForJudge = isThisForJudge;
        this.f = f;


        setModal(true);
        setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        setUndecorated(true);
        pack();
        setBounds(bound);
        new Timer(250, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                repaint();
            }
        });
    }

    @Override
    public void paint(Graphics gg) {
        super.paint(gg);
//        System.err.println("JPanelScoreTable::paintComponent:: " + new Date());

        if (f == null) {
            gg.dispose();
            return;
        }

        final Graphics2D g = (Graphics2D) gg; // гарантируется что всегда будет корректное проебразование

        Dimension scrDim = new Dimension((int) g.getClipBounds().getWidth(), (int) g.getClipBounds().getHeight());
        if (scrDim.height <= 10 || scrDim.width <= 10) {
//            System.err.println("Слишком маленькое разрешение");
            g.dispose();
            return;
        }

        // высоты трёх секрций: верхнего колонтитула, нижнего колонтитула и серединки
        final double heightRoof = scrDim.height * 1.0 / 12.5;
        final double heightBottom = scrDim.height * 1.5 / 12.5;
        final double heightCenter = scrDim.height - heightRoof - heightBottom;

        final double wUnit = scrDim.width / (11.5 + 11.5);
        final double hUnit = heightCenter / (10.5);

//        // начало заполения заголовка ----------------------------------------------------------------------------------
//        {
//            g.setColor(Color.LIGHT_GRAY);
//            g.fill(new Rectangle.Double(0, 0, scrDim.width, heightRoof));
//
//            if (f.getFightStatus() == FightStatus.finish ||
//                    f.getFightStatus() == FightStatus.finishTie ||
//                    f.getFightStatus() == FightStatus.DisqualificationLeft
//                    ) {
//                GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.YELLOW, f.getRoofInfo(), 0, 0, scrDim.width, heightRoof);
//            } else {
//                int fontSize = Math.min(
//                        GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getRoofInfo(), (scrDim.width - 2 * wUnit) / 2, heightRoof),
//                        Math.min(
//                                GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getStringTime(), 2 * wUnit, heightRoof),
//                                GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "00:00", 2 * wUnit, heightRoof)
//                        )
//                ) - 3;
//
//                GraphicsUtilities.drawTextInTheLeftOfRectangle(
//                        g, Color.BLACK, f.getRoofInfo(), 0, 0, (int) heightRoof,
//                        fontSize
//                );
//
//                GraphicsUtilities.drawTextInCenterOfRectangle(
//                        g, Color.BLACK, f.getStringTime(), (scrDim.width - 2 * wUnit) / 2, 0, 2 * wUnit, heightRoof, fontSize
//                );
//
//                GraphicsUtilities.drawTextInTheRightOfRectangle(
//                        g, Color.BLACK, f.getRoofInfo(), (int) ((scrDim.width - 2 * wUnit) / 2 + 2 * wUnit), 0, (int) ((scrDim.width - 2 * wUnit) / 2), (int) heightRoof,
//                        fontSize
//                );
//            }
//        }
//        // конец заполения заголовка -----------------------------------------------------------------------------------
//
//        // начало заполения середины -----------------------------------------------------------------------------------
//        {
//            final int sizeOfFontForFightersAndCountries =
//                    Math.min(
//                            Math.min(
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getNameOfLeftFighter(isThisForJudge), (3.5 + 3.5 + 3.5) * wUnit, hUnit),
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getNameOfRightFighter(isThisForJudge), (3.5 + 3.5 + 3.5) * wUnit, hUnit)
//                            ),
//                            Math.min(
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getCountryOfLeftFighter(isThisForJudge), (3.5 + 3.5 + 3.5) * wUnit, hUnit),
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getCountryOfRightFighter(isThisForJudge), (3.5 + 3.5 + 3.5) * wUnit, hUnit)
//                            )
//                    ) - 2;
//            final int sizeOfFontForCenterBox =
//                    Math.min(
//                            Math.min(
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getLabelFightNo(), 2 * wUnit, 0.5 * hUnit),
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getFightId() + "", 2 * wUnit, 0.5 * hUnit)
//                            ),
//                            Math.min(
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getSeparator(), 2 * wUnit, 0.5 * hUnit),
//                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), f.getCategoryOfFighting() + "", 2 * wUnit, 0.5 * hUnit)
//                            )
//                    );
//
//            g.translate(0, heightRoof);
//
//            Color leftColor = isThisForJudge ? Color.RED : Color.BLUE;
//            Color rightColor = isThisForJudge ? Color.BLUE : Color.RED;
//            // красный фон для правого бойца
//            g.setColor(f.getLoser(isThisForJudge) == Player.left ? GraphicsUtilities.getGrayColor(leftColor) : leftColor);
//            g.fill(new Rectangle.Double(0, 0, scrDim.width / 2.0, heightCenter));
//
//            // голубой фон для правого бойца
//            g.setColor(f.getLoser(isThisForJudge) == Player.Right ? GraphicsUtilities.getGrayColor(rightColor) : rightColor);
////            g.setColor(GraphicsUtilities.getGrayColor(Color.RED));
//            g.fill(new Rectangle.Double(scrDim.width / 2.0, 0, scrDim.width / 2.0, heightCenter));
//
//            // заполняем номер раунда, категория бойцов (центральный квадратик)
//            g.setColor(Color.WHITE);
//            g.fill(new Rectangle2D.Double((11.5 - 1) * wUnit, 0.3 * hUnit, 2 * wUnit, 2 * hUnit));
//
//            g.setColor(Color.BLACK);
//            g.draw(new Rectangle2D.Double((11.5 - 1) * wUnit, 0.3 * hUnit, 2 * wUnit, 2 * hUnit));
//
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.BLACK,
//                    f.getLabelFightNo(),
//                    (11.5 - 1) * wUnit,
//                    0.3 * hUnit,
//                    2 * wUnit,
//                    0.5 * hUnit,
//                    sizeOfFontForCenterBox
//            );
//
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.BLACK,
//                    "" + f.getFightId(),
//                    (11.5 - 1) * wUnit,
//                    (0.3 + 0.5) * hUnit,
//                    2 * wUnit,
//                    0.5 * hUnit,
//                    sizeOfFontForCenterBox
//            );
//
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.BLACK,
//                    f.getSeparator(),
//                    (11.5 - 1) * wUnit,
//                    (0.3 + 0.5 + 0.5) * hUnit,
//                    2 * wUnit,
//                    0.5 * hUnit,
//                    sizeOfFontForCenterBox
//            );
//
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.BLACK,
//                    f.getCategoryOfFighting(),
//                    (11.5 - 1) * wUnit,
//                    (0.3 + 0.5 + 0.5 + 0.5) * hUnit,
//                    2 * wUnit,
//                    0.5 * hUnit,
//                    sizeOfFontForCenterBox
//            );
//
//            // ФИО левого
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.WHITE,
//                    f.getNameOfLeftFighter(isThisForJudge),
//                    0,
//                    0,
//                    (3.5 + 3.5 + 3.5) * wUnit,
//                    hUnit,
//                    sizeOfFontForFightersAndCountries
//            );
//
//
//            // флаг левого бойца
//            {
//                Dimension scaledDimension = GraphicsUtilities.getScaledDimension(f.getImageLeftConnerFlag(isThisForJudge).getWidth(), f.getImageLeftConnerFlag(isThisForJudge).getHeight(), (3.5 + 3.5 + 3.5) * wUnit, 2.5 * hUnit);
//                g.drawImage(
//                        f.getLoser(isThisForJudge) == Player.left ? GraphicsUtilities.getGrayImage(f.getImageLeftConnerFlag(isThisForJudge)) : f.getImageLeftConnerFlag(isThisForJudge),
//                        (int) ((10.5 * wUnit - scaledDimension.width) / 2),
//                        (int) hUnit,
//                        scaledDimension.width,
//                        scaledDimension.height,
//                        null
//                );
//
//                g.setColor(Color.WHITE);
//                g.drawRect(
//                        (int) ((10.5 * wUnit - scaledDimension.width) / 2),
//                        (int) hUnit,
//                        scaledDimension.width,
//                        scaledDimension.height
//                );
//            }
//
//            // название страны левого бойца
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.WHITE,
//                    f.getCountryOfLeftFighter(isThisForJudge),
//                    0,
//                    (1 + 2.5) * hUnit,
//                    (3.5 + 3.5 + 3.5) * wUnit,
//                    hUnit,
//                    sizeOfFontForFightersAndCountries
//            );
//
//
//            // ФИО правого
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.WHITE,
//                    f.getNameOfRightFighter(isThisForJudge),
//                    (11.5 + 1) * wUnit,
//                    0,
//                    (3.5 + 3.5 + 3.5) * wUnit,
//                    hUnit,
//                    sizeOfFontForFightersAndCountries
//            );
//
//
//            // флаг правого бойца
//            {
//                Dimension scaledDimension = GraphicsUtilities.getScaledDimension(f.getImageRightConnerFlag(isThisForJudge).getWidth(), f.getImageRightConnerFlag(isThisForJudge).getHeight(), (3.5 + 3.5 + 3.5) * wUnit, 2.5 * hUnit);
//                g.drawImage(
//                        f.getLoser(isThisForJudge) == Player.Right ? GraphicsUtilities.getGrayImage(f.getImageRightConnerFlag(isThisForJudge)) : f.getImageRightConnerFlag(isThisForJudge),
//                        (int) (scrDim.width / 2 + wUnit + (10.5 * wUnit - scaledDimension.width) / 2),
//                        (int) hUnit,
//                        scaledDimension.width,
//                        scaledDimension.height,
//                        null
//                );
//
//                g.setColor(Color.WHITE);
//                g.drawRect(
//                        (int) (scrDim.width / 2 + wUnit + (10.5 * wUnit - scaledDimension.width) / 2),
//                        (int) hUnit,
//                        scaledDimension.width,
//                        scaledDimension.height
//                );
//            }
//
//            // название страны правого бойца
//            GraphicsUtilities.drawTextInCenterOfRectangle(
//                    g,
//                    Color.WHITE,
//                    f.getCountryOfRightFighter(isThisForJudge),
//                    scrDim.width / 2 + wUnit,
//                    (1 + 2.5) * hUnit,
//                    (3.5 + 3.5 + 3.5) * wUnit,
//                    hUnit,
//                    sizeOfFontForFightersAndCountries
//            );
//
//
//            for (int judge = 0; judge < 3; judge++) {
//                int sideOfCube = (int) (0.3 * hUnit);
//                int widthSpaceBetweenCubes = (int) (0.2 * hUnit);
//                int heightSpaceBetweenCubes = (int) (0.4 * hUnit);
//                for (int cube = 0; cube < f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge] - f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge]; cube++) {
//                    g.setColor(Color.YELLOW);
//                    g.fillRect(
//                            (int) (scrDim.width / 2.0 - 10 - sideOfCube * (cube + 1) - widthSpaceBetweenCubes * cube),
//                            (int) (hUnit * 6.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
//                            sideOfCube, sideOfCube);
//                }
//                for (int cube = 0; cube < f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge] - f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge]; cube++) {
//                    g.setColor(Color.YELLOW);
//                    g.fillRect(
//                            (int) (scrDim.width / 2.0 + 10 + sideOfCube * (cube + 1) + widthSpaceBetweenCubes * cube),
//                            (int) (hUnit * 6.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
//                            sideOfCube, sideOfCube);
//                }
//
//                if (f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge] > f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge]) {
//                    int cube = f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge] - f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge];
//                    g.setColor(Color.WHITE);
//                    GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.WHITE,
//                            (f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge] - f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge]) + "",
//                            (int) (scrDim.width / 2.0 - 10 - sideOfCube * (cube + 1) - widthSpaceBetweenCubes * cube),
//                            (int) (hUnit * 6.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
//                            sideOfCube, sideOfCube
//                    );
//                }
//                if (f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge] < f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge]) {
//                    int cube = f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge] - f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge];
//                    g.setColor(Color.WHITE);
//                    GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.WHITE,
//                            (f.getCountOfPointsForTheRightFighter(isThisForJudge)[judge] - f.getCountOfPointsForTheLeftFighter(isThisForJudge)[judge]) + "",
//                            (int) (scrDim.width / 2.0 + 10 + sideOfCube * (cube + 1) + widthSpaceBetweenCubes * cube),
//                            (int) (hUnit * 6.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
//                            sideOfCube, sideOfCube
//                    );
//                }
//            }
//
//            // рисуем итоговый счёт
//            g.setColor(Color.WHITE);
//            g.fill(new Rectangle2D.Double(
//                    scrDim.width / 2 - 1 * wUnit,
//                    8.5 * hUnit,
//                    2 * wUnit,
//                    hUnit)
//            );
//            g.setColor(Color.BLACK);
//            g.draw(new Rectangle2D.Double(
//                    scrDim.width / 2 - 1 * wUnit,
//                    8.5 * hUnit,
//                    2 * wUnit,
//                    hUnit)
//            );
//            GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.BLACK, f.getCountJudgeForLeftFighter(isThisForJudge) + " : " + f.getCountJudgeForRightFighter(isThisForJudge),
//                    scrDim.width / 2 - 1 * wUnit, 8.5 * hUnit, 2 * wUnit, hUnit);
//
//
//            // рисуем Minus, Fo, Ex
//            {
//                double halfWidth = (scrDim.width / 2 - wUnit) / 2;
//                double sizeOfCube = Math.min(0.3 * hUnit, 0.3 * halfWidth / 2.2);
//                double widthSpaceBetweenCubes = Math.min(0.2 * hUnit, 0.2 * halfWidth / 2.2);
//                /** всего может быть 4 кубика и 5пробельчиков между ними
//                 * 4 * sizeOfCube + 5 * widthSpaceBetweenCubes = halfWidth  <=>
//                 * 4 * 0.3 * hUnit + 5 * 0.2 * hUnit = halfWidth   <=>
//                 * 1.2 * hUnit + 1 * hUnit = halfWidth   <=>
//                 * 2.2 * hUnit = halfWidth   <=> hUnit = halfWidth / 2.2
//                 */
//
//
//                int sizeOfFont = Math.min(
//                        Math.min(
//                                GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Minus: ", halfWidth, 0.5 * hUnit),
//                                GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Fo: ", halfWidth, 0.5 * hUnit)
//                        ), GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Ex: ", halfWidth, 0.5 * hUnit));
//
//                // рисуем Minus, Fo, Ex для левого бойца
//                {
//                    GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
//                            0, heightCenter + (-2) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
//                    GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Fo: ",
//                            0, heightCenter + (-2 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
//                    GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Ex: ",
//                            0, heightCenter + (-2 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
//                    g.setColor(Color.YELLOW);
//                    double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
//                    for (int i = 0; i < f.getCountOfMinusToLeft(isThisForJudge); i++) {
//                        g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
//                    }
//                    for (int i = 0; i < f.getCountOfForestallingToLeft(isThisForJudge); i++) {
//                        g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
//                    }
//                    for (int i = 0; i < f.getCountOfExToLeft(isThisForJudge); i++) {
//                        g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
//                    }
//                }
//
//                // рисуем Minus, Fo, Ex для правого бойца
//                {
//                    g.translate(scrDim.width / 2 + wUnit, 0);
//
//                    GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
//                            0, heightCenter + (-2) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
//                    GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Fo: ",
//                            0, heightCenter + (-2 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
//                    GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Ex: ",
//                            0, heightCenter + (-2 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
//                    g.setColor(Color.YELLOW);
//                    double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
//                    for (int i = 0; i < f.getCountOfMinusToRight(isThisForJudge); i++) {
//                        g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
//                    }
//                    for (int i = 0; i < f.getCountOfForestallingToRight(isThisForJudge); i++) {
//                        g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
//                    }
//                    for (int i = 0; i < f.getCountOfExToRight(isThisForJudge); i++) {
//                        g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
//                    }
//
//                    g.translate(-(scrDim.width / 2 + wUnit), 0);
//                }
//            }
//        }
//        // конец заполения середины ------------------------------------------------------------------------------------
//
//        // начало заполенения подвала
//        {
//            double hs = heightBottom * 2.5 / 15.0;
//            double heightRect = heightBottom * 5.0 / 15.0;
//            double widthRect = scrDim.width / (3 + 1 + 6.5 + 1 + 6.5 + 1 + 3);
//
//            g.translate(0, heightCenter);
//
//            g.setColor(Color.LIGHT_GRAY);
//            g.fill(new Rectangle.Double(0, 0, scrDim.width, heightBottom));
//
//            g.setColor(Color.WHITE);
//            g.fill(new Rectangle.Double((3) * widthRect, hs, widthRect, heightRect));
//            g.fill(new Rectangle.Double((3 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));
//            g.fill(new Rectangle.Double((3 + 1 + 6.5 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));
//
//            g.setColor(Color.BLACK);
//            g.draw(new Rectangle.Double((3) * widthRect, hs, widthRect, heightRect));
//            g.draw(new Rectangle.Double((3 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));
//            g.draw(new Rectangle.Double((3 + 1 + 6.5 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));
//
//            for (int i = 0; i < 3; i++) {
//                GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(
//                        g,
//                        Color.BLACK,
//                        f.getCountOfPointsForTheLeftFighter(isThisForJudge)[i] + " : " + f.getCountOfPointsForTheRightFighter(isThisForJudge)[i],
//                        (3 + (1 + 6.5) * i) * widthRect,
//                        hs,
//                        widthRect,
//                        heightRect
//                );
//
//                GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(
//                        g,
//                        Color.BLACK,
//                        "" + (i + 1),
//                        (3 + (1 + 6.5) * i) * widthRect,
//                        hs + heightRect,
//                        widthRect,
//                        heightRect
//                );
//            }
//        }
        //
        // конец заполенения подвала -----------------------------------------------------------------------------------
        g.dispose();
    }

}