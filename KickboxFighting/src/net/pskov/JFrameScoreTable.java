package net.pskov;

import net.pskov.some_enum.Player;
import net.pskov.some_enum.FightStatus;
import net.pskov.some_enum.PointPanelMode;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;

class JFrameScoreTable extends JDialog {

    private boolean isThisForJudge;
    private final ModelFight modelFight;
    private Timer timer;

    JFrameScoreTable(boolean isThisForJudge, final Rectangle bound, final ModelFight f) {
        super();

        this.isThisForJudge = isThisForJudge;
        this.modelFight = f;

        add(new JPanel() {
            @Override
            public void paint(Graphics g) {
                JFrameScoreTable.this.myPaint(g);
            }
        });

//        if (isThisForJudge) {
//            addKeyListener(new KeyAdapter() {
//                @Override
//                public void keyPressed(KeyEvent e) {
//                    if (e.getKeyCode() == KeyEvent.VK_6) {
//                        f.setDialog(true);
//                        JDialogStopRound dialog = new JDialogStopRound(JFrameScoreTable.this);
//                        dialog.setVisible(true);
//                        f.setDialog(false);
//
//                        f.forceStopRound(dialog.getWinner(), dialog.getResult());
//                    }
//                }
//            });
//
//            //
//            addMouseMotionListener(new MouseMotionListener() {
//                @Override
//                public void mouseDragged(MouseEvent arg0) {
//                    mymove(arg0);
//                }
//
//                @Override
//                public void mouseMoved(MouseEvent arg0) {
//                    mymove(arg0);
//                }
//
//                private Robot robo;
//
//                {
//                    try {
//                        robo = new Robot();
//                    } catch (AWTException e) {
//                        e.printStackTrace();
//                    }
//                }
//
//                private final int fixX = bound.width / 2;
//                private final int fixY = bound.height / 2;
//
//                private void mymove(MouseEvent arg0) {
//                    if (robo == null) return;
//                    if (arg0.getX() == fixX && arg0.getY() == fixY) {
//                        // ignore mouse action
//                        return;
//                    }
//                    robo.mouseMove(fixX + JFrameScoreTable.this.getX(), fixY + JFrameScoreTable.this.getY());
//                }
//            });
//        }


        setModal(true);
        setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
//        setUndecorated(true);
        pack();
//        setBounds(bound);
        setBounds(new Rectangle(100, 100, 1700, 600));


        timer = new Timer(250, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                repaint();
//                System.err.println("JFrameScoreTable");
            }
        });
        timer.start();

    }

    @Override
    public void dispose() {
        super.dispose();
        timer.stop();
        modelFight.dispose();
    }

    public void myPaint(Graphics gg) {
//        System.err.println("paint: " + System.currentTimeMillis());
        //super.paint(gg);
//        System.err.println("JPanelScoreTable::paintComponent:: " + new Date());


        final Graphics2D g = (Graphics2D) gg; // гарантируется что всегда будет корректное проебразование

        g.setRenderingHint(
                RenderingHints.KEY_TEXT_ANTIALIASING,
                RenderingHints.VALUE_TEXT_ANTIALIAS_GASP);
        g.setFont(new Font(g.getFont().getFontName(), Font.BOLD, g.getFont().getSize()));

        g.setColor(Color.YELLOW);
        g.fillRect(0, 0, g.getClipBounds().width, g.getClipBounds().height);

        Dimension scrDim;
        if (isThisForJudge) {
            scrDim = new Dimension((int) (0.85 * g.getClipBounds().width), g.getClipBounds().height);
            g.translate(scrDim.width, 0);

            String[] msg = null;
            if (modelFight.getPointPanelMode() == PointPanelMode.LightContact)
                msg = new String[]{
                        "SPACE - start/pause",
                        "ESC - exit",

                        "Q - minus (red)",
                        "A - waring (red)",
                        "Z - exit (red)",

                        "O - minus (blue)",
                        "K - waring (blue)",
                        "M - exit (blue)",

                        "G - cancel last penalty",

                        "6 - STOP ROUND!"
                };

            else if (modelFight.getPointPanelMode() == PointPanelMode.K1)
                msg = new String[]{
                        "SPACE - start/pause",
                        "ESC - exit",

                        "Q - minus (red)",
                        "A - waring (red)",
                        "Z - knock down (red)",

                        "O - minus (blue)",
                        "K - waring (blue)",
                        "M - knock down (blue)",

                        "G - cancel last penalty",

                        "6 - STOP ROUND!"
                };
            else
                msg = new String[]{
                        "SPACE - start/pause",
                        "ESC - exit",

                        "Q - minus (red)",
                        "A - waring (red)",
                        "Z - knock down (red)",
                        "W - kick count (red)",

                        "O - minus (blue)",
                        "K - waring (blue)",
                        "M - knock down (blue)",
                        "I - kick count (blue)",

                        "G - cancel last penalty",

                        "6 - STOP ROUND!"
                };


            int height = scrDim.height / (msg.length);
            int sz = 100;
            for (String aMsg : msg) {
                sz = Math.min(sz, GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), aMsg, g.getClipBounds().width - scrDim.width, height));
            }
            for (int i = 0; i < msg.length; i++) {
                GraphicsUtilities.drawTextInTheLeftOfRectangle(g, Color.black, msg[i], 0, i * height, height, sz);
            }
            g.translate(-scrDim.width, 0);
        } else
            scrDim = new Dimension(g.getClipBounds().width, g.getClipBounds().height);

        if (scrDim.height <= 10 || scrDim.width <= 10) {
//            System.err.println("Слишком маленькое разрешение");
            g.dispose();
            return;
        }

        // высоты трёх секрций: верхнего колонтитула, нижнего колонтитула и серединки
        final double heightRoof = scrDim.height * 0.15;
        final double heightBottom = scrDim.height * 0.10;
        final double heightCenter = scrDim.height - heightRoof - heightBottom;

        final double wUnit = scrDim.width / (11.5 + 11.5);
        final double hUnit = heightCenter / (10.5);
        FightStatus status = modelFight.getStatus();

        Player greyPlayer = Player.NoPlayer;
        if (modelFight.getWinner() != Player.NoPlayer) {
            if (isThisForJudge && modelFight.getWinner() == Player.Left || !isThisForJudge && modelFight.getWinner() == Player.Right)
                greyPlayer = Player.Right;
            else
                greyPlayer = Player.Left;
        }
        final int[] countOfPointsForTheLeftFighter = isThisForJudge ? modelFight.getCountOfPointsForLeftFighter() : modelFight.getCountOfPointsForRightFighter();
        final int[] countOfPointsForTheRightFighter = isThisForJudge ? modelFight.getCountOfPointsForRightFighter() : modelFight.getCountOfPointsForLeftFighter();


//        // начало заполения заголовка ----------------------------------------------------------------------------------
        {
            g.setColor(Color.LIGHT_GRAY);
            g.fill(new Rectangle.Double(0, 0, scrDim.width, heightRoof));

//            NotStart, Fight, Break, PauseFight, Tie, Finish, DisqualificationLeft, DisqualificationRight,
//            winnerByPointsLeft, winnerByPointsRight,
//            stoppedByJudge, forceLeftWinner, forceRightWinner,
//            PendingExtraRound, ExtraRound, PauseExtraRound
            if (modelFight.getWinner() != Player.NoPlayer) {
                GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.YELLOW, "Winner is " + (modelFight.getWinner() == Player.Left ? modelFight.getNameOfLeftFighter() : modelFight.getNameOfRightFighter()), 0, 0, scrDim.width, heightRoof);
            } else {
                String roofInfo = "";
                if (status == FightStatus.NotStart)
                    roofInfo = String.format("Round %d/%d - Pending", modelFight.getCurrentRound(), modelFight.getCountOfRounds());
                else if (status == FightStatus.Fight)
                    roofInfo = String.format("Round %d/%d - Fight!", modelFight.getCurrentRound(), modelFight.getCountOfRounds());
                else if (status == FightStatus.Break)
                    roofInfo = String.format("Round %d/%d - Break", modelFight.getCurrentRound(), modelFight.getCountOfRounds());
                else if (status == FightStatus.PauseFight)
                    roofInfo = String.format("Round %d/%d - Pause", modelFight.getCurrentRound(), modelFight.getCountOfRounds());
                else if (status == FightStatus.Tie)
                    roofInfo = "Tie...";
                else if (status == FightStatus.PendingExtraRound)
                    roofInfo = "Extra round - Pending";
                else if (status == FightStatus.ExtraRound)
                    roofInfo = "Extra round - Fight!";
                else if (status == FightStatus.PauseExtraRound)
                    roofInfo = "Extra round - Pause";

                final double widthTime = scrDim.width * 0.2;
                int fontSizeOfRoofInfo = GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), roofInfo, 0.90 * (scrDim.width - widthTime) / 2, heightRoof);

                int fontSizeOfTime = GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getStringTime(), widthTime, heightRoof);
                for (int i = 0; i < 10; i++) {
                    fontSizeOfTime = Math.min(fontSizeOfTime,
                            GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), String.format("%d%d:%d%d", i, i, i, i), widthTime, heightRoof));
                }


                GraphicsUtilities.drawTextInTheLeftOfRectangle(g, Color.BLACK, roofInfo, 0, 0, (int) heightRoof, fontSizeOfRoofInfo);
                GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.BLACK, roofInfo, (int) ((scrDim.width - widthTime) / 2 + widthTime), 0, (int) ((scrDim.width - widthTime) / 2), (int) heightRoof, fontSizeOfRoofInfo);
                GraphicsUtilities.drawTextInCenterOfRectangle(g, Color.BLACK, modelFight.getStringTime(), (scrDim.width - widthTime) / 2, 0, widthTime, heightRoof, fontSizeOfTime);


            }
        }
//        // конец заполения заголовка -----------------------------------------------------------------------------------
//
//        // начало заполения середины -----------------------------------------------------------------------------------
        {
            final int sizeOfFontForFightersAndCountries =
                    Math.min(
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getNameOfLeftFighter(), (3.5 + 3.5 + 3.5) * wUnit, hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getNameOfRightFighter(), (3.5 + 3.5 + 3.5) * wUnit, hUnit)
                            ),
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getCountryOfLeftFighter(), (3.5 + 3.5 + 3.5) * wUnit, hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getCountryOfRightFighter(), (3.5 + 3.5 + 3.5) * wUnit, hUnit)
                            )
                    ) - 2;
            final String fightNo = "Fight no.";
            final int sizeOfFontForCenterBox =
                    Math.min(
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), fightNo, 2 * wUnit, 0.5 * hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getFightId() + "", 2 * wUnit, 0.5 * hUnit)
                            ),
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "---", 2 * wUnit, 0.5 * hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getCategoryOfFighting() + "", 2 * wUnit, 0.5 * hUnit)
                            )
                    );

            g.translate(0, heightRoof);

            Color leftColor = isThisForJudge ? Color.RED : Color.BLUE;
            Color rightColor = isThisForJudge ? Color.BLUE : Color.RED;

            if (greyPlayer == Player.Left)
                leftColor = GraphicsUtilities.getGrayColor(leftColor);
            else if (greyPlayer == Player.Right)
                rightColor = GraphicsUtilities.getGrayColor(rightColor);

            g.setColor(leftColor);
            g.fill(new Rectangle.Double(0, 0, scrDim.width / 2.0, heightCenter));
            g.setColor(rightColor);
            g.fill(new Rectangle.Double(scrDim.width / 2.0, 0, scrDim.width / 2.0, heightCenter));


//            {
//                int widthTime = scrDim.width;
//                int heightTime = (int) ((6.4 - 1 - 2.5 - 1) * hUnit);
//                int fontSizeOfTime = GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), modelFight.getStringTime(), widthTime, heightTime);
//                for (int i = 0; i < 10; i++) {
//                    fontSizeOfTime = Math.min(fontSizeOfTime,
//                            GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), String.format("%d%d:%d%d", i, i, i, i), widthTime, heightTime));
//                }
//                GraphicsUtilities.drawTextInCenterOfRectangle(g, Color.WHITE, modelFight.getStringTime(), 0, (1 + 2.5 + 1) * hUnit, widthTime, heightTime, fontSizeOfTime);
//
//            }

//
//            // заполняем номер раунда, категория бойцов (центральный квадратик)
            g.setColor(Color.WHITE);
            g.fill(new Rectangle2D.Double((11.5 - 1) * wUnit, 0.3 * hUnit, 2 * wUnit, 2 * hUnit));

            g.setColor(Color.BLACK);
            g.draw(new Rectangle2D.Double((11.5 - 1) * wUnit, 0.3 * hUnit, 2 * wUnit, 2 * hUnit));

            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.BLACK,
                    fightNo,
                    (11.5 - 1) * wUnit,
                    0.3 * hUnit,
                    2 * wUnit,
                    0.5 * hUnit,
                    sizeOfFontForCenterBox
            );

            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.BLACK,
                    "" + modelFight.getFightId(),
                    (11.5 - 1) * wUnit,
                    (0.3 + 0.5) * hUnit,
                    2 * wUnit,
                    0.5 * hUnit,
                    sizeOfFontForCenterBox
            );

            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.BLACK,
                    "---",
                    (11.5 - 1) * wUnit,
                    (0.3 + 0.5 + 0.5) * hUnit,
                    2 * wUnit,
                    0.5 * hUnit,
                    sizeOfFontForCenterBox
            );

            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.BLACK,
                    modelFight.getCategoryOfFighting(),
                    (11.5 - 1) * wUnit,
                    (0.3 + 0.5 + 0.5 + 0.5) * hUnit,
                    2 * wUnit,
                    0.5 * hUnit,
                    sizeOfFontForCenterBox
            );

//            // ФИО левого
            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.WHITE,
                    isThisForJudge ? modelFight.getNameOfLeftFighter() : modelFight.getNameOfRightFighter(),
                    0,
                    0,
                    (3.5 + 3.5 + 3.5) * wUnit,
                    hUnit,
                    sizeOfFontForFightersAndCountries
            );


//            // флаг левого бойца
            {
                BufferedImage flag = isThisForJudge ? modelFight.getImageLeftConnerFlag() : modelFight.getImageRightConnerFlag();
                if (flag != null) {
                    Dimension scaledDimension = GraphicsUtilities.getScaledDimension(flag.getWidth(), flag.getHeight(), (3.5 + 3.5 + 3.5) * wUnit, 2.5 * hUnit);
                    g.drawImage(
                            greyPlayer == Player.Left ? GraphicsUtilities.getGrayImage(flag) : flag,
                            (int) ((10.5 * wUnit - scaledDimension.width) / 2),
                            (int) hUnit,
                            scaledDimension.width,
                            scaledDimension.height,
                            null
                    );

                    g.setColor(Color.WHITE);
                    g.drawRect(
                            (int) ((10.5 * wUnit - scaledDimension.width) / 2),
                            (int) hUnit,
                            scaledDimension.width,
                            scaledDimension.height
                    );
                }
            }

            // название страны левого бойца
            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.WHITE,
                    isThisForJudge ? modelFight.getCountryOfLeftFighter() : modelFight.getCountryOfRightFighter(),
                    0,
                    (1 + 2.5) * hUnit,
                    (3.5 + 3.5 + 3.5) * wUnit,
                    hUnit,
                    sizeOfFontForFightersAndCountries
            );


            // ФИО правого
            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.WHITE,
                    isThisForJudge ? modelFight.getNameOfRightFighter() : modelFight.getNameOfLeftFighter(),
                    (11.5 + 1) * wUnit,
                    0,
                    (3.5 + 3.5 + 3.5) * wUnit,
                    hUnit,
                    sizeOfFontForFightersAndCountries
            );


            // флаг правого бойца
            {
                BufferedImage flag = isThisForJudge ? modelFight.getImageRightConnerFlag() : modelFight.getImageLeftConnerFlag();
                if (flag != null) {
                    Dimension scaledDimension = GraphicsUtilities.getScaledDimension(flag.getWidth(), flag.getHeight(), (3.5 + 3.5 + 3.5) * wUnit, 2.5 * hUnit);
                    g.drawImage(
                            greyPlayer == Player.Right ? GraphicsUtilities.getGrayImage(flag) : flag,
                            (int) (scrDim.width / 2 + wUnit + (10.5 * wUnit - scaledDimension.width) / 2),
                            (int) hUnit,
                            scaledDimension.width,
                            scaledDimension.height,
                            null
                    );

                    g.setColor(Color.WHITE);
                    g.drawRect(
                            (int) (scrDim.width / 2 + wUnit + (10.5 * wUnit - scaledDimension.width) / 2),
                            (int) hUnit,
                            scaledDimension.width,
                            scaledDimension.height
                    );
                }
            }

            // название страны правого бойца
            GraphicsUtilities.drawTextInCenterOfRectangle(
                    g,
                    Color.WHITE,
                    isThisForJudge ? modelFight.getCountryOfRightFighter() : modelFight.getCountryOfLeftFighter(),
                    scrDim.width / 2 + wUnit,
                    (1 + 2.5) * hUnit,
                    (3.5 + 3.5 + 3.5) * wUnit,
                    hUnit,
                    sizeOfFontForFightersAndCountries
            );


            for (int judge = 0; judge < 3; judge++) {
                int sideOfCube = (int) (0.3 * hUnit);
                int widthSpaceBetweenCubes = (int) (0.2 * hUnit);
                int heightSpaceBetweenCubes = (int) (0.4 * hUnit);

                for (int cube = 0; cube < countOfPointsForTheLeftFighter[judge] - countOfPointsForTheRightFighter[judge]; cube++) {
                    g.setColor(Color.YELLOW);
                    g.fillRect(
                            (int) (scrDim.width / 2.0 - 10 - sideOfCube * (cube + 1) - widthSpaceBetweenCubes * cube),
                            (int) (hUnit * 5.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
                            sideOfCube, sideOfCube);
                }
                for (int cube = 0; cube < countOfPointsForTheRightFighter[judge] - countOfPointsForTheLeftFighter[judge]; cube++) {
                    g.setColor(Color.YELLOW);
                    g.fillRect(
                            (int) (scrDim.width / 2.0 + 10 + sideOfCube * (cube + 1) + widthSpaceBetweenCubes * cube),
                            (int) (hUnit * 5.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
                            sideOfCube, sideOfCube);
                }

                if (countOfPointsForTheLeftFighter[judge] > countOfPointsForTheRightFighter[judge]) {
                    int cube = countOfPointsForTheLeftFighter[judge] - countOfPointsForTheRightFighter[judge];
                    g.setColor(Color.WHITE);
                    GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.WHITE,
                            (countOfPointsForTheLeftFighter[judge] - countOfPointsForTheRightFighter[judge]) + "",
                            (int) (scrDim.width / 2.0 - 10 - sideOfCube * (cube + 1) - widthSpaceBetweenCubes * cube),
                            (int) (hUnit * 5.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
                            sideOfCube, sideOfCube
                    );
                }
                if (countOfPointsForTheLeftFighter[judge] < countOfPointsForTheRightFighter[judge]) {
                    int cube = countOfPointsForTheRightFighter[judge] - countOfPointsForTheLeftFighter[judge];
                    g.setColor(Color.WHITE);
                    GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.WHITE,
                            (countOfPointsForTheRightFighter[judge] - countOfPointsForTheLeftFighter[judge]) + "",
                            (int) (scrDim.width / 2.0 + 10 + sideOfCube * (cube + 1) + widthSpaceBetweenCubes * cube),
                            (int) (hUnit * 5.4 + (sideOfCube + heightSpaceBetweenCubes) * judge),
                            sideOfCube, sideOfCube
                    );
                }
            }

            // рисуем итоговый счёт
            g.setColor(Color.WHITE);
            g.fill(new Rectangle2D.Double(
                    scrDim.width / 2 - 1 * wUnit,
                    8.5 * hUnit,
                    2 * wUnit,
                    hUnit)
            );
            g.setColor(Color.BLACK);
            g.draw(new Rectangle2D.Double(
                    scrDim.width / 2 - 1 * wUnit,
                    8.5 * hUnit,
                    2 * wUnit,
                    hUnit)
            );

            int countJudgeForLeftFighter = isThisForJudge ? modelFight.getCountJudgeForLeftFighter() : modelFight.getCountJudgeForRightFighter();
            int countJudgeForRightFighter = isThisForJudge ? modelFight.getCountJudgeForRightFighter() : modelFight.getCountJudgeForLeftFighter();
            GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(g, Color.BLACK, countJudgeForLeftFighter + " : " + countJudgeForRightFighter,
                    scrDim.width / 2 - 1 * wUnit, 8.5 * hUnit, 2 * wUnit, hUnit);


            // рисуем Minus, Fo, Exit
            {
                double halfWidth = (scrDim.width / 2 - wUnit) / 2;
                double sizeOfCube = Math.min(0.3 * hUnit, 0.3 * halfWidth / 2.2);
                double widthSpaceBetweenCubes = Math.min(0.2 * hUnit, 0.2 * halfWidth / 2.2);
                /** всего может быть 4 кубика и 5пробельчиков между ними
                 * 4 * sizeOfCube + 5 * widthSpaceBetweenCubes = halfWidth  <=>
                 * 4 * 0.3 * hUnit + 5 * 0.2 * hUnit = halfWidth   <=>
                 * 1.2 * hUnit + 1 * hUnit = halfWidth   <=>
                 * 2.2 * hUnit = halfWidth   <=> hUnit = halfWidth / 2.2
                 */


                int sizeOfFont;
                if (modelFight.getPointPanelMode() == PointPanelMode.LightContact)
                    sizeOfFont = Math.min(
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Minus: ", halfWidth, 0.5 * hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Warning: ", halfWidth, 0.5 * hUnit)
                            ), GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Exit: ", halfWidth, 0.5 * hUnit));
                else if (modelFight.getPointPanelMode() == PointPanelMode.K1)
                    sizeOfFont = Math.min(
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Minus: ", halfWidth, 0.5 * hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Warning: ", halfWidth, 0.5 * hUnit)
                            ), GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Knock down: ", halfWidth, 0.5 * hUnit));
                else
                    sizeOfFont = Math.min(
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Minus: ", halfWidth, 0.5 * hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Warning: ", halfWidth, 0.5 * hUnit)
                            ),
                            Math.min(
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Knock down: ", halfWidth, 0.5 * hUnit),
                                    GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), "Kick count: ", halfWidth, 0.5 * hUnit)
                            ));

                // рисуем Minus, Fo, Exit для левого бойца
                {
                    if (modelFight.getPointPanelMode() == PointPanelMode.LightContact) {
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
                                0, heightCenter + (-2) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Warning: ",
                                0, heightCenter + (-2 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Exit: ",
                                0, heightCenter + (-2 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        g.setColor(Color.YELLOW);
                        double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
                        int countOfMinusToLeft = isThisForJudge ? modelFight.getCountOfMinusToLeft() : modelFight.getCountOfMinusToRight();
                        int countOfForestallingToLeft = isThisForJudge ? modelFight.getCountOfForestallingToLeft() : modelFight.getCountOfForestallingToRight();
                        int countOfExToLeft = isThisForJudge ? modelFight.getCountOfExToLeft() : modelFight.getCountOfExToRight();
                        for (int i = 0; i < countOfMinusToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfForestallingToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfExToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                    } else if (modelFight.getPointPanelMode() == PointPanelMode.K1) {
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
                                0, heightCenter + (-2) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Warning: ",
                                0, heightCenter + (-2 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Knock down: ",
                                0, heightCenter + (-2 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        g.setColor(Color.YELLOW);
                        double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
                        int countOfMinusToLeft = isThisForJudge ? modelFight.getCountOfMinusToLeft() : modelFight.getCountOfMinusToRight();
                        int countOfForestallingToLeft = isThisForJudge ? modelFight.getCountOfForestallingToLeft() : modelFight.getCountOfForestallingToRight();
                        int countOfKnockDown = isThisForJudge ? modelFight.getCountOfKnockDownToLeft() : modelFight.getCountOfKnockDownToRight();
                        for (int i = 0; i < countOfMinusToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfForestallingToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfKnockDown; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                    } else if (modelFight.getPointPanelMode() == PointPanelMode.FullContact) {
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
                                0, heightCenter + (-2.5) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Warning: ",
                                0, heightCenter + (-2.5 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Knock down: ",
                                0, heightCenter + (-2.5 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Kick count: ",
                                0, heightCenter + (-2.5 + 0.6 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        g.setColor(Color.YELLOW);
                        double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
                        int countOfMinusToLeft = isThisForJudge ? modelFight.getCountOfMinusToLeft() : modelFight.getCountOfMinusToRight();
                        int countOfForestallingToLeft = isThisForJudge ? modelFight.getCountOfForestallingToLeft() : modelFight.getCountOfForestallingToRight();
                        int countOfKnockDown = isThisForJudge ? modelFight.getCountOfKnockDownToLeft() : modelFight.getCountOfKnockDownToRight();
                        int countOfKickCount = isThisForJudge ? modelFight.getCountOfKickCountToLeft() : modelFight.getCountOfKickCountToRight();
                        for (int i = 0; i < countOfMinusToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfForestallingToLeft; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfKnockDown; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfKickCount; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5 + 0.6 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                    }
                }

                // рисуем Minus, Fo, Exit для правого бойца
                {
                    g.translate(scrDim.width / 2 + wUnit, 0);

                    if (modelFight.getPointPanelMode() == PointPanelMode.LightContact) {
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
                                0, heightCenter + (-2) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Warning: ",
                                0, heightCenter + (-2 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Exit: ",
                                0, heightCenter + (-2 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        g.setColor(Color.YELLOW);
                        double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
                        int countOfMinus = isThisForJudge ? modelFight.getCountOfMinusToRight() : modelFight.getCountOfMinusToLeft();
                        int countOfForestalling = isThisForJudge ? modelFight.getCountOfForestallingToRight() : modelFight.getCountOfForestallingToLeft();
                        int countOfEx = isThisForJudge ? modelFight.getCountOfExToRight() : modelFight.getCountOfExToLeft();
                        for (int i = 0; i < countOfMinus; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfForestalling; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfEx; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                    } else if (modelFight.getPointPanelMode() == PointPanelMode.K1) {
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
                                0, heightCenter + (-2) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Warning: ",
                                0, heightCenter + (-2 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Knock down: ",
                                0, heightCenter + (-2 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        g.setColor(Color.YELLOW);
                        double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
                        int countOfMinus = isThisForJudge ? modelFight.getCountOfMinusToRight() : modelFight.getCountOfMinusToLeft();
                        int countOfForestalling = isThisForJudge ? modelFight.getCountOfForestallingToRight() : modelFight.getCountOfForestallingToLeft();
                        int countOfKnockDown = isThisForJudge ? modelFight.getCountOfKnockDownToRight() : modelFight.getCountOfKnockDownToLeft();
                        for (int i = 0; i < countOfMinus; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfForestalling; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfKnockDown; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                    } else {
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Minus: ",
                                0, heightCenter + (-2.5) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Warning: ",
                                0, heightCenter + (-2.5 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Knock down: ",
                                0, heightCenter + (-2.5 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        GraphicsUtilities.drawTextInTheRightOfRectangle(g, Color.WHITE, "Kick count: ",
                                0, heightCenter + (-2.5 + 0.6 + 0.6 + 0.6) * hUnit, (scrDim.width / 2 - wUnit) / 2, 0.5 * hUnit, sizeOfFont);
                        g.setColor(Color.YELLOW);
                        double BUBEN = (0.5 * hUnit - sizeOfCube) / 2; // чтобы красиво было
                        int countOfMinus = isThisForJudge ? modelFight.getCountOfMinusToRight() : modelFight.getCountOfMinusToLeft();
                        int countOfForestalling = isThisForJudge ? modelFight.getCountOfForestallingToRight() : modelFight.getCountOfForestallingToLeft();
                        int countOfKnockDown = isThisForJudge ? modelFight.getCountOfKnockDownToRight() : modelFight.getCountOfKnockDownToLeft();
                        int countOfKickCount = isThisForJudge ? modelFight.getCountOfKickCountToRight() : modelFight.getCountOfKickCountToLeft();
                        for (int i = 0; i < countOfMinus; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfForestalling; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfKnockDown; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                        for (int i = 0; i < countOfKickCount; i++) {
                            g.fill(new Rectangle.Double((halfWidth + (i + 1) * widthSpaceBetweenCubes + i * sizeOfCube), heightCenter + (-2.5 + 0.6 + 0.6 + 0.6) * hUnit + BUBEN, sizeOfCube, sizeOfCube));
                        }
                    }

                    g.translate(-(scrDim.width / 2 + wUnit), 0);
                }
            }
        }
        // конец заполения середины ------------------------------------------------------------------------------------

        // начало заполенения подвала
        {
            double hs = heightBottom * 2.5 / 15.0;
            double heightRect = heightBottom * 5.0 / 15.0;
            double widthRect = scrDim.width / (3 + 1 + 6.5 + 1 + 6.5 + 1 + 3);

            g.translate(0, heightCenter);

            g.setColor(Color.LIGHT_GRAY);
            g.fill(new Rectangle.Double(0, 0, scrDim.width, heightBottom));

            g.setColor(Color.WHITE);
            g.fill(new Rectangle.Double((3) * widthRect, hs, widthRect, heightRect));
            g.fill(new Rectangle.Double((3 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));
            g.fill(new Rectangle.Double((3 + 1 + 6.5 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));

            g.setColor(Color.BLACK);
            g.draw(new Rectangle.Double((3) * widthRect, hs, widthRect, heightRect));
            g.draw(new Rectangle.Double((3 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));
            g.draw(new Rectangle.Double((3 + 1 + 6.5 + 1 + 6.5) * widthRect, hs, widthRect, heightRect));

            for (int i = 0; i < 3; i++) {
                GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(
                        g,
                        Color.BLACK,
                        countOfPointsForTheLeftFighter[i] + " : " + countOfPointsForTheRightFighter[i],
                        (3 + (1 + 6.5) * i) * widthRect,
                        hs,
                        widthRect,
                        heightRect
                );

                GraphicsUtilities.fitAndDrawTextInCenterOfRectangle(
                        g,
                        Color.BLACK,
                        "" + (i + 1),
                        (3 + (1 + 6.5) * i) * widthRect,
                        hs + heightRect,
                        widthRect,
                        heightRect
                );
            }
        }
        // конец заполенения подвала -----------------------------------------------------------------------------------
        g.dispose();
    }

}
