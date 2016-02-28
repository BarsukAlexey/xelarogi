package net.pskov;

import com.google.gson.*;
import com.google.gson.internal.bind.JsonTreeWriter;
import net.java.games.input.Component;
import net.pskov.controller.KeyboardController;
import net.pskov.controller.MouseController;
import net.pskov.someEnum.Player;
import net.pskov.someEnum.StatusFighting;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Date;
import java.util.HashSet;

//import java.nio.charset.StandardCharsets;

public class JFrameMainJudge extends JFrame {

    private JPanel jPanelStartPage; // панелька, на которой выбирается бой, настраиваются мышки, сохраняются результаты...
    private JPanel jPanelFighting;  // панелька, на которой находится табло боя и подсказки как управлять боем

    private JFrame[] jFrameSpectator; // Окна, которые отображаются на мониторах для зрителей. На каждом мониторе по одному окну

    private JPanelScoreTable[] allJPanelScoreTable; // все табло, включая то, что у главного судьи (оно 0ое в массиве)

    final JList<Fighting> jList; // список дерущихся

    private volatile Fighting activeFighting;

    private final MouseController[] mouseController;
    private volatile KeyboardController keyboardController;

    public JFrameMainJudge() {
        super();

        mouseController = new MouseController[3];
        keyboardController = new KeyboardController();

        jList = new JList<Fighting>();

        // получаем координаты левого верхнего всех мониторов
        GraphicsDevice[] screenDevices = GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
        Point[] originPoint = new Point[screenDevices.length];
        for (int i = 0; i < originPoint.length; i++) {
            originPoint[i] = screenDevices[i].getDefaultConfiguration().getBounds().getLocation();
        }

        // делаем так, чтобы в originPoint[0] хранилали лавая верхняя координата дефолтного монитора (это монитор главного судьи)
        for (int i = 0; i < originPoint.length; i++) {
            if (originPoint[i].equals(GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDefaultConfiguration().getBounds().getLocation())) {
                Point point = originPoint[i];
                originPoint[i] = originPoint[0];
                originPoint[0] = point;
                break;
            }
        }

        setLocation(originPoint[0]);

        allJPanelScoreTable = new JPanelScoreTable[originPoint.length];
        allJPanelScoreTable[0] = new JPanelScoreTable(true);
        jFrameSpectator = new JFrame[originPoint.length - 1];
        for (int i = 0; i < jFrameSpectator.length; i++) {
            jFrameSpectator[i] = createFrameAtLocation(originPoint[i + 1], allJPanelScoreTable[i + 1] = new JPanelScoreTable(false));
        }

        initJPanelStartPage();
        initJPanelFighting();

        add(jPanelStartPage);

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLocation(originPoint[0]);
        setUndecorated(true);
        setExtendedState(Frame.MAXIMIZED_BOTH);
//        setAlwaysOnTop(true);
        requestFocus();
        addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                System.err.println("focusGained");
            }

            @Override
            public void focusLost(FocusEvent e) {
                System.err.println("FocusEvent");
                JFrameMainJudge.this.requestFocus();
            }
        });
        pack();
        setVisible(true);
//        setSize(1200, 800);

        new PollMiceAndKeyboard().start();
    }

    private void initJPanelStartPage() {
        // создания списка боёв
//        final JList<Fighting> jList;
//        Fighting[] fightings;
//        try {
//            fightings = new Fighting[]{
//                    new Fighting("Быстрий Иван", "Быстрый Егор", 4, "FC M-2", 1, 3, 2, ImageIO.read(new File("resources\\images\\rus.png")), ImageIO.read(new File("resources\\images\\Switzerland.png")), "Rus", "Switzerland"),
//                    new Fighting("Иван  Иванович", "Василий Васильевич", 1, "FC f-52", 2, 30, 20, ImageIO.read(new File("resources\\images\\Canada.png")), ImageIO.read(new File("resources\\images\\Qatar.png")), "Canada", "Qatar"),
//                    new Fighting("Петров Петрович", "Максим Максимыч", 2, "FC f-2", 3, 20, 13, ImageIO.read(new File("resources\\images\\rus.png")), ImageIO.read(new File("resources\\images\\Switzerland.png")), "Rus", "Switzerland"),
//                    new Fighting("Петрова Ирина", "Шаманова Виктория", 3, "FC f-2", 3, 20, 13, ImageIO.read(new File("resources\\images\\rus.png")), ImageIO.read(new File("resources\\images\\Switzerland.png")), "Rus", "Switzerland"),
//            };
//
//        } catch (IOException e) {
//            e.printStackTrace();
//            fightings = new Fighting[0];
//        }
//        jList = new JList<>(fightings);
//        jList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
//        JScrollPane jScrollPane = new JScrollPane(jList);
//        jScrollPane.setPreferredSize(new Dimension(90, 13));
//        if (0 < jList.getModel().getSize())
//            jList.setSelectedIndex(0);


        //jList = new JList<>();
        jList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane jScrollPane = new JScrollPane(jList);
        jScrollPane.setPreferredSize(new Dimension(90, 13));
        if (0 < jList.getModel().getSize())
            jList.setSelectedIndex(0);


        // создание кнопки начала боя
        JButton jStart = new JButton("Start fighting");
        jStart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!updateMice()) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "Connect mice and click \"init mice\"");
                    return;
                }

                Fighting selectedValue = jList.getSelectedValue();
                if (selectedValue == null) return;
                System.err.println("Fight: " + selectedValue); // TODO

                // Инифиализируем текущий бой
                activeFighting = selectedValue;
                for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                    panelScoreTable.setFighting(activeFighting);
                    panelScoreTable.revalidate();  // TODO?
                    panelScoreTable.repaint(); // TODO?
                }

                // в окне главного судьи убираем панельку jPanelStartPage, заменяем её на панельку, в которой смотрим за результатами боя
                remove(jPanelStartPage);
                add(jPanelFighting);
                revalidate();
                repaint();
            }
        });


        // выбор файла с боями
        JButton jButtonSelectFile = new JButton("Select file");
        jButtonSelectFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
                int returnVal = chooser.showOpenDialog(jPanelStartPage);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    String path = chooser.getSelectedFile().getAbsolutePath();
                    System.out.println("You chose to open this file: " + path); // TODO
                    String JSON_DATA;
                    try {
                        JSON_DATA = new String(Files.readAllBytes(Paths.get(path)), StandardCharsets.UTF_8);
//                        JSON_DATA = new String(Files.readAllBytes(Paths.get(path)));
                    } catch (IOException e1) {
                        e1.printStackTrace();
                        return;
                    }

                    final DefaultListModel<Fighting> listModel = new DefaultListModel<Fighting>();

                    for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
                        Fighting f = new Fighting(
                                jsonElement.getAsJsonObject().get("nameOfLeftFighter").getAsString(),
                                jsonElement.getAsJsonObject().get("nameOfRightFighter").getAsString(),
                                jsonElement.getAsJsonObject().get("fightId").getAsInt(),
                                jsonElement.getAsJsonObject().get("categoryOfFighting").getAsString(),
                                jsonElement.getAsJsonObject().get("countOfRounds").getAsInt(),
                                jsonElement.getAsJsonObject().get("durationOfRound").getAsInt(),
                                jsonElement.getAsJsonObject().get("durationOfBreak").getAsInt(),
                                jsonElement.getAsJsonObject().get("countryOfLeftFighter").getAsString(),
                                jsonElement.getAsJsonObject().get("countryOfRightFighter").getAsString(),
                                jsonElement.getAsJsonObject().get("TOURNAMENT_CATEGORIES_FK").getAsLong(),
                                jsonElement.getAsJsonObject().get("VERTEX").getAsInt(),
                                jsonElement.getAsJsonObject().get("orderUID_left").getAsLong(),
                                jsonElement.getAsJsonObject().get("orderUID_right").getAsLong()
                        );
                        listModel.addElement(f);
                        com.google.gson.stream.JsonWriter s = new JsonTreeWriter();

                    }
                    jList.setModel(listModel);
                }
            }
        });


        // выбор папки куда сохранять результаты
        JButton jButtonSaveFile = new JButton("Save results");
        jButtonSaveFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                int returnVal = chooser.showOpenDialog(jPanelStartPage);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    String choosedPath = chooser.getSelectedFile().getAbsolutePath();
                    System.out.println("You chose to open this file: " + choosedPath); // TODO
                    File file = new File(choosedPath, "result" + new Date().getTime() + ".json");

                    JsonArray jsonArray = new JsonArray();
                    for (int i = 0; i < jList.getModel().getSize(); ++i) {
                        Fighting f = jList.getModel().getElementAt(i);
                        if (f.getStatusFighting() == StatusFighting.finishPending || f.getStatusFighting() == StatusFighting.disqualification) {
                            JsonObject jsonObject = new JsonObject();
                            jsonObject.addProperty("TOURNAMENT_CATEGORIES_FK", f.TOURNAMENT_CATEGORIES_FK);
                            jsonObject.addProperty("VERTEX", f.VERTEX);
                            jsonObject.addProperty("orderUID", f.getLoser(true) == Player.left ? f.orderUID_right : f.orderUID_left);
                            jsonObject.addProperty("result", f.getResult());
                            jsonArray.add(jsonObject);
                        }
                    }

                    try {
                        PrintStream out = new PrintStream(file);
                        out.print(new Gson().toJson(jsonArray));
                        out.flush();
                        out.close();
                    } catch (FileNotFoundException e1) {
                        e1.printStackTrace();
                    }

                }
            }
        });

        JButton jButtonInitMice = new JButton("Init mice...");
        jButtonInitMice.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new JDialogInitMice(JFrameMainJudge.this, JFrameMainJudge.this.mouseController);
            }
        });

        // добавление всех компонентов на панель
        jPanelStartPage = new JPanel();
        jPanelStartPage.setLayout(new BoxLayout(jPanelStartPage, BoxLayout.Y_AXIS));
        jPanelStartPage.add(jScrollPane);
        jPanelStartPage.add(jStart);
        jPanelStartPage.add(jButtonSelectFile);
        jPanelStartPage.add(jButtonSaveFile);
        jPanelStartPage.add(jButtonInitMice);
    }

    void initJPanelFighting() {
        jPanelFighting = new JPanel();
        jPanelFighting.setLayout(new GridBagLayout());


        JPanel jPanelRight = new JPanel();
        jPanelRight.setLayout(new BoxLayout(jPanelRight, BoxLayout.Y_AXIS));
        JLabel[] jLabels = new JLabel[]{
                new JLabel("Q - minus кр. углу"),
                new JLabel("O - minus син. углу"),
                new JLabel("T - отмена последнего minus"),
                new JLabel(" "),
                new JLabel("A - fo. кр. углу"),
                new JLabel("K - fo. син. углу"),
                new JLabel("G - отмена последнего fo."),
                new JLabel(" "),
                new JLabel("Z - ex. кр. углу"),
                new JLabel("M - ex. син. углу"),
                new JLabel("V - отмена последнего ex."),
                new JLabel(" "),
                new JLabel("W - нокаут кр. угла"),
                new JLabel("I - нокаут син. угла"),
                new JLabel(" "),
                new JLabel("S - отказ от боя кр. угла"),
                new JLabel("J - отказ от боя син. угла"),
                new JLabel(" "),
                new JLabel("X - дисквалификация кр. угла"),
                new JLabel("N - дисквалификация син. угла"),
                new JLabel(" "),
                new JLabel("E - остановка боя рефери кр. угла"),
                new JLabel("U - остановка боя рефери син. угла"),
                new JLabel(" "),
                new JLabel("D - технический нокаут кр. угла"),
                new JLabel("H - технический нокаут син. угла"),
                new JLabel(" "),
                new JLabel("C - невозможность продолжать бой кр. угла"),
                new JLabel("B - невозможность продолжать бой син. угла"),
                new JLabel(" "),
                new JLabel("R - отказ секунданта кр. угла"),
                new JLabel("Y - отказ секунданта син. угла"),
                new JLabel(" "),
                new JLabel("SPACE - начать бой/пауза/выход"),
        };
        for (JLabel jLabel : jLabels) {
            Font font = jLabel.getFont();
            jLabel.setFont(new Font(font.getName(), Font.PLAIN, 20));
            jPanelRight.add(jLabel);
        }

        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 0.8;
        c.weighty = 1;
        c.gridx = 0;
        c.gridy = 0;
        jPanelFighting.add(allJPanelScoreTable[0], c);
//        allJPanelScoreTable[0].setFighting(f()); // TODO

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 0.2;
        c.weighty = 1;
        c.gridx = 1;
        c.gridy = 0;
        jPanelFighting.add(jPanelRight, c);
    }


    /**
     * @return true, если мышки покллючены и они не отвалились, иначе false
     */
    private boolean updateMice() {
        synchronized (mouseController) {
            boolean ok = true;
            for (int i = 0; i < 3; i++) {
                MouseController mouse = mouseController[i];
                if (mouse == null || !mouse.update()) {
                    ok = false;
                    continue;
                }
//                System.err.println("JFrameMainJudge::updateMice::" + new Date());
                if (mouse.wasLeftClick()) {
                    if (activeFighting != null) {
                        activeFighting.addOnePointToLeftFighter(i);
                    }
                }
                if (mouse.wasRightClick()) {
                    if (activeFighting != null) {
                        activeFighting.addOnePointToRightFighter(i);
                    }
                }
            }
            return ok;
        }
    }

    private void updateKeyboard() {
        HashSet<Component.Identifier> pressedKeys = keyboardController.capture();
        if (!pressedKeys.isEmpty())
            System.err.println(pressedKeys);

        if (activeFighting == null) return;

        // Если минус балл кому-то
        if (pressedKeys.contains(Component.Identifier.Key.Q)) {
            activeFighting.addMinusToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.T)) {
            activeFighting.cancelLastMinus();
        }
        if (pressedKeys.contains(Component.Identifier.Key.O)) {
            activeFighting.addMinusToRight();
        }

        // Если предупреждение кому-то
        if (pressedKeys.contains(Component.Identifier.Key.A)) {
            activeFighting.addForestallingToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.G)) {
            activeFighting.cancelLastForestalling();
        }
        if (pressedKeys.contains(Component.Identifier.Key.K)) {
            activeFighting.addForestallingToRight();
        }


        //  Если выход за ринг у кого-то
        if (pressedKeys.contains(Component.Identifier.Key.Z)) {
            activeFighting.addExToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.V)) {
            activeFighting.cancelLastEx();
        }
        if (pressedKeys.contains(Component.Identifier.Key.M)) {
            activeFighting.addExToRight();
        }

        if (pressedKeys.contains(Component.Identifier.Key.W)) activeFighting.stopFightingBlyatSuka(Player.left, "КО");
        if (pressedKeys.contains(Component.Identifier.Key.I)) activeFighting.stopFightingBlyatSuka(Player.right, "КО");

        if (pressedKeys.contains(Component.Identifier.Key.S)) activeFighting.stopFightingBlyatSuka(Player.left, "L");
        if (pressedKeys.contains(Component.Identifier.Key.J)) activeFighting.stopFightingBlyatSuka(Player.right, "L");

        if (pressedKeys.contains(Component.Identifier.Key.X)) activeFighting.stopFightingBlyatSuka(Player.left, "DISQ");
        if (pressedKeys.contains(Component.Identifier.Key.N))
            activeFighting.stopFightingBlyatSuka(Player.right, "DISQ");

        if (pressedKeys.contains(Component.Identifier.Key.E)) activeFighting.stopFightingBlyatSuka(Player.left, "RSC");
        if (pressedKeys.contains(Component.Identifier.Key.U)) activeFighting.stopFightingBlyatSuka(Player.right, "RSC");

        if (pressedKeys.contains(Component.Identifier.Key.D)) activeFighting.stopFightingBlyatSuka(Player.left, "RSCH");
        if (pressedKeys.contains(Component.Identifier.Key.H))
            activeFighting.stopFightingBlyatSuka(Player.right, "RSCH");

        if (pressedKeys.contains(Component.Identifier.Key.C)) activeFighting.stopFightingBlyatSuka(Player.left, "AB");
        if (pressedKeys.contains(Component.Identifier.Key.B)) activeFighting.stopFightingBlyatSuka(Player.right, "AB");

        if (pressedKeys.contains(Component.Identifier.Key.R)) activeFighting.stopFightingBlyatSuka(Player.left, "WO");
        if (pressedKeys.contains(Component.Identifier.Key.Y)) activeFighting.stopFightingBlyatSuka(Player.right, "WO");


        if (pressedKeys.contains(Component.Identifier.Key.SPACE)) {
            if (activeFighting.getStatusFighting() == StatusFighting.notBegin) {
                activeFighting.startRound();
            } else if (activeFighting.getStatusFighting() == StatusFighting.fighting) {
                activeFighting.pauseRound();
            } else if (activeFighting.getStatusFighting() == StatusFighting._break) {
                // ничего не надо делать
            } else if (activeFighting.getStatusFighting() == StatusFighting.fightingPause) {
                activeFighting.continueRound();
//            } else if (activeFighting.getStatusFighting() == StatusFighting.finishPending ||
//                    activeFighting.getStatusFighting() == StatusFighting.disqualification) {
            } else {
                remove(jPanelFighting);
                add(jPanelStartPage);
                revalidate();
                repaint();
                for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                    panelScoreTable.setFighting(null);
                    panelScoreTable.revalidate();  // TODO?
                    panelScoreTable.repaint(); // TODO?
                }

                JsonArray jsonArray = new JsonArray();
                for (int i = 0; i < jList.getModel().getSize(); ++i) {
                    Fighting f = jList.getModel().getElementAt(i);
                    if (f.getStatusFighting() == StatusFighting.finishPending || f.getStatusFighting() == StatusFighting.disqualification) {
                        JsonObject jsonObject = new JsonObject();
                        jsonObject.addProperty("TOURNAMENT_CATEGORIES_FK", f.TOURNAMENT_CATEGORIES_FK);
                        jsonObject.addProperty("VERTEX", f.VERTEX);
                        jsonObject.addProperty("orderUID", f.getLoser(true) == Player.left ? f.orderUID_right : f.orderUID_left);
                        jsonObject.addProperty("result", f.getResult());
                        jsonArray.add(jsonObject);
                    }
                }

                try {
                    PrintStream out = new PrintStream(new FileOutputStream("результаты боя.json"));
                    out.print(new Gson().toJson(jsonArray));
                    out.flush();
                    out.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class PollMiceAndKeyboard extends Thread {
        @Override
        public void run() {
            while (true) {
                long startTime = System.currentTimeMillis();
                updateMice();
                updateKeyboard();
                long duration = System.currentTimeMillis() - startTime;
//                    System.err.println(duration);
                int DELAY = 50;
                if (duration < DELAY) {
                    try {
                        Thread.sleep(DELAY - duration);  // wait until DELAY time has passed
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                } else {
                    System.err.println("Не успел: " + (duration - DELAY));
                }
            }
        }
    }

    {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) { // на весь этот цикл даётся 200 мс
                    long beginTime = System.currentTimeMillis();
                    if (activeFighting != null) {
                        activeFighting.updateTime();
                        for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                            panelScoreTable.repaint();
                        }
                    }
                    long delay = 200 - (System.currentTimeMillis() - beginTime);
                    if (0 < delay) {
                        try {
                            Thread.sleep(delay);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }).start();
    }


    private JFrame createFrameAtLocation(Point p, JPanel jPanel) {
        final JFrame frame = new JFrame();
        frame.add(jPanel);
        frame.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        frame.setLocation(p);
        frame.setAlwaysOnTop(true);
        frame.setUndecorated(true);
        hideCursor(frame);
        frame.pack();
        frame.setExtendedState(Frame.MAXIMIZED_BOTH);
        frame.setVisible(true);
        frame.addWindowFocusListener(new WindowAdapter() {
            @Override
            public void windowLostFocus(WindowEvent e) {
                frame.setExtendedState(Frame.MAXIMIZED_BOTH);
                frame.requestFocus();
                System.err.println(e); // TODO
            }
        });
        return frame;
    }

    private void hideCursor(Container c) {
        // create a transparent 16 x 16 pixel cursor image
        BufferedImage cursorIm = new BufferedImage(16, 16, BufferedImage.TYPE_INT_ARGB);
        // create a new blank cursor
        Cursor blankCursor = Toolkit.getDefaultToolkit().createCustomCursor(cursorIm, new Point(0, 0), "blank cursor");
        // assign the blank cursor to the JFrame
        c.setCursor(blankCursor);
    }

}
