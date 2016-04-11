package net.pskov;

import com.google.gson.*;
import net.java.games.input.Component;
import net.pskov.controller.KeyboardController;
import net.pskov.controller.MouseController;
import net.pskov.some_enum.Player;
import net.pskov.some_enum.StatusFighting;
import net.pskov.utils.ImageUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;


class JFrameMainJudge extends JFrame {

    private final String pathSaveJson = "save.json";


    private JPanel jPanelStartPage; // панелька, на которой выбирается бой, настраиваются мышки, сохраняются результаты...
    private JPanel jPanelFighting;  // панелька, на которой находится табло боя и подсказки как управлять боем

    private JPanelScoreTable[] allJPanelScoreTable; // все табло, включая то, что у главного судьи (оно 0ое в массиве)
    private final JList<String> jList; // список дерущихся

    private volatile Fighting activeFighting;
    private volatile Vector<Fighting> allFighting;
    private volatile Vector<Boolean> canStartFighting;

    private final MouseController[] mouseController;
    private volatile KeyboardController keyboardController;

    JFrameMainJudge() {
        super();

        mouseController = new MouseController[3];
        keyboardController = new KeyboardController();

        jList = new JList<String>();
        initListOfPlayers(pathSaveJson);

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
        JFrame[] jFrameSpectator = new JFrame[originPoint.length - 1];
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

    private void initListOfPlayers(String path) {
        String JSON_DATA;
        try {
            JSON_DATA = new String(Files.readAllBytes(Paths.get(path)), StandardCharsets.UTF_8);
        } catch (IOException e1) {
            e1.printStackTrace();
            return;
        }

        final DefaultListModel<String> listModel = new DefaultListModel<>();

        allFighting = new Vector<>();
        canStartFighting = new Vector<>();
        for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
            JsonObject object = jsonElement.getAsJsonObject();

            Fighting f = new Fighting(
                    object.get("nameOfLeftFighter").getAsString(),
                    object.get("nameOfRightFighter").getAsString(),
                    object.get("fightId").getAsInt(),
                    object.get("categoryOfFighting").getAsString(),
//                    object.get("countOfRounds").getAsInt(),
//                    object.get("durationOfRound").getAsInt(),
//                    object.get("durationOfBreak").getAsInt(),
                    1,2,2,

                    ImageUtils.decodeToImage(object.get("leftFlag").getAsString()),
                    ImageUtils.decodeToImage(object.get("rightFlag").getAsString()),

                    object.get("countryOfLeftFighter").getAsString(),
                    object.get("countryOfRightFighter").getAsString(),
                    object.get("TOURNAMENT_CATEGORIES_FK").getAsLong(),
                    object.get("VERTEX").getAsInt()
            );
            allFighting.add(f);
            long winner = 0;
            if (object.get("orderUID") != null) winner = object.get("orderUID").getAsInt();
            long left = object.get("orderUID_left").getAsInt();
            long right = object.get("orderUID_right").getAsInt();
            String element = object.get("fightId").getAsInt() + "    /    " + object.get("nameOfLeftFighter").getAsString() + " (" + object.get("countryOfLeftFighter").getAsString() + ")    /    " +
                    object.get("nameOfRightFighter").getAsString() + " (" + object.get("countryOfRightFighter").getAsString() + ")   ";
            if (0 < winner) {
                element += "  / WINNER IS ";
                if (winner == left)
                    element += object.get("nameOfLeftFighter").getAsString();
                else if (winner == right)
                    element += object.get("countryOfRightFighter").getAsString();
                else
                    throw new RuntimeException();
                canStartFighting.add(false);
            }
            else{
                canStartFighting.add(true);
            }
            listModel.addElement(element);
        }
        jList.setModel(listModel);
    }

    private void initJPanelStartPage() {
        jList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane jScrollPane = new JScrollPane(jList);
        jScrollPane.setPreferredSize(new Dimension(90, 13));


        // создание кнопки начала боя
        JButton jStart = new JButton("Start fighting");
        jStart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!updateMice()) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "Connect mice and click \"init mice\"");
                    return;
                }
                if (jList.getSelectedIndex() < 0)
                    return;
                if (!canStartFighting.get(jList.getSelectedIndex())){
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "played");
                    return;
                }


                Fighting selectedValue = allFighting.get(jList.getSelectedIndex());
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
        JButton jButtonLoadData = new JButton("Select list of pairs...");
        jButtonLoadData.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
                if (chooser.showOpenDialog(jPanelStartPage) == JFileChooser.APPROVE_OPTION) {
                    String path = chooser.getSelectedFile().getAbsolutePath();
                    System.out.println("You chose to open this file: " + path); // TODO
                    try {
                        Files.copy(Paths.get(path), Paths.get(pathSaveJson), StandardCopyOption.REPLACE_EXISTING);
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    initListOfPlayers(path);
                }
            }
        });


        // выбор папки куда сохранять результаты
        JButton jButtonSaveFile = new JButton("Save results...");
        jButtonSaveFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setSelectedFile(new File("Results " + new SimpleDateFormat(" yyyy.MM.dd  HH'h'mm'm'").format(new Date()) + ".json"));
                if (chooser.showSaveDialog(jPanelStartPage) == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = chooser.getSelectedFile();
                    System.out.println("You chose to open this file: " + selectedFile.getAbsolutePath()); // TODO
                    try {
                        Files.copy(Paths.get(pathSaveJson), selectedFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
                    } catch (IOException e1) {
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
        jPanelStartPage.add(jButtonLoadData);
        jPanelStartPage.add(jButtonSaveFile);
        jPanelStartPage.add(jButtonInitMice);
    }

    private void initJPanelFighting() {
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
            //jLabel.setFont(new Font(font.getName(), Font.PLAIN, 20));
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
            } else if (activeFighting.getStatusFighting() == StatusFighting.fightingPause) {
                activeFighting.continueRound();
            } else if (activeFighting.getStatusFighting() == StatusFighting.finishPending ||
                    activeFighting.getStatusFighting() == StatusFighting.disqualification) {
                remove(jPanelFighting);
                add(jPanelStartPage);
                revalidate();
                repaint();
                for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                    panelScoreTable.setFighting(null);
                    panelScoreTable.revalidate();  // TODO?
                    panelScoreTable.repaint(); // TODO?
                }


                String JSON_DATA;
                try {
                    JSON_DATA = new String(Files.readAllBytes(Paths.get(pathSaveJson)), StandardCharsets.UTF_8);
                } catch (IOException e1) {
                    e1.printStackTrace();
                    return;
                }
                JsonArray jsonArray = new JsonArray();
                for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
                    JsonObject object = jsonElement.getAsJsonObject();
                    for (Fighting f : allFighting) {
                        if (f.TOURNAMENT_CATEGORIES_FK == object.get("TOURNAMENT_CATEGORIES_FK").getAsLong() &&
                                f.VERTEX == object.get("VERTEX").getAsLong() &&
                                (f.getStatusFighting() == StatusFighting.finishPending ||
                                        f.getStatusFighting() == StatusFighting.disqualification)) {
                            object.addProperty("orderUID", f.getLoser(true) == Player.left ? object.get("orderUID_right").getAsLong() : object.get("orderUID_left").getAsLong());
                            object.addProperty("result", f.getResult());
                        }
                    }
                    System.err.println(object.get("fightId"));
                    jsonArray.add(object);
                }
                System.err.println("-----------");
                try {
                    PrintStream out = new PrintStream(new FileOutputStream(pathSaveJson));
                    out.print(new Gson().toJson(jsonArray));
                    out.flush();
                    out.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                initListOfPlayers(pathSaveJson);
            }
        }
    }

    private class PollMiceAndKeyboard extends Thread {
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
