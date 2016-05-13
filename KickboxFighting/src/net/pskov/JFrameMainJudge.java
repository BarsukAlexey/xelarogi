package net.pskov;

import com.google.gson.*;
import net.java.games.input.Component;
import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;
import net.java.games.input.Mouse;
import net.pskov.controller.KeyboardController;
import net.pskov.controller.MouseController;
import net.pskov.some_enum.FightStatus;
import net.pskov.some_enum.Player;
import net.pskov.utils.ImageUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashSet;
import java.util.Vector;

class JFrameMainJudge extends JFrame {

    private final String pathSaveJson = "save.json";
    private final String pathAdvJson = "adv.json";


    private final JTable table; // список дерущихся

    private volatile Fighting activeFighting;
    private volatile Vector<Fighting> allFighting;
    private volatile Vector<Boolean> canStartFighting;

    private final MouseController[] mouseController;
    private volatile KeyboardController keyboardController;

    private int intervalAdv;
    ArrayList<JFrameScoreTable> scoreTable;


    private final ArrayList<JFrameAdvertising> jFrameAdvertisings;

    JFrameMainJudge() {
        super("Judge");

        intervalAdv = 15;
        scoreTable = new ArrayList<>();

        mouseController = new MouseController[3];
        keyboardController = new KeyboardController();


        table = new JTable() {
            @Override
            public java.awt.Component prepareRenderer(TableCellRenderer renderer, int row, int column) {
                TableColumn tableColumn = getColumnModel().getColumn(column);
                TableCellRenderer headerRenderer = tableColumn.getHeaderRenderer();
                if (headerRenderer == null) {
                    headerRenderer = table.getTableHeader().getDefaultRenderer();
                }
                java.awt.Component comp = headerRenderer.getTableCellRendererComponent(this, tableColumn.getHeaderValue(), false, false, 0, 0);

                java.awt.Component component = super.prepareRenderer(renderer, row, column);


                int width = comp.getPreferredSize().width ;
                width = Math.max(width, component.getPreferredSize().width + getIntercellSpacing().width);
                width = Math.max(width, tableColumn.getPreferredWidth());
                tableColumn.setPreferredWidth(width);
                return component;
            }
        };



        try {
            String JSON_DATA = new String(Files.readAllBytes(Paths.get(pathAdvJson)), StandardCharsets.UTF_8);
            intervalAdv = new JsonParser().parse(JSON_DATA).getAsJsonObject().get("intervalAdv").getAsInt();
        } catch (IOException e1) {
            e1.printStackTrace();
            intervalAdv = 0;
        }

        ArrayList<BufferedImage> avd;
        {
            avd = new ArrayList<>();
            File[] advertisings = new File("Advertising").listFiles();
            if (advertisings != null) {
                for (final File file : advertisings) {
                    if (!file.isDirectory()) {
                        try {
                            BufferedImage image = ImageIO.read(file);
                            if (image != null && 0 < image.getWidth() && 0 < image.getHeight())
                                avd.add(image);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }


        jFrameAdvertisings = new ArrayList<>();
        Rectangle defaultBounds = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDefaultConfiguration().getBounds();
        GraphicsDevice[] screenDevices = GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
        for (int i = 0, id = 0; i < screenDevices.length; i++) {
            Rectangle bounds = screenDevices[i].getDefaultConfiguration().getBounds();
            if (bounds.equals(defaultBounds))
                continue;
            jFrameAdvertisings.add(new JFrameAdvertising("Spectator" + id++, bounds, avd, intervalAdv));
        }

        setContentPane(initUI());
        initListOfPlayers(pathSaveJson);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
//        setUndecorated(true);
        pack();
        setBounds(defaultBounds);
//        setExtendedState(Frame.MAXIMIZED_BOTH);
        setVisible(true);
        setSize(1280, 800);

        new Timer(50, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateMice();
                updateKeyboard();
            }
        }).start();
    }

    private JPanel initUI() {
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane jScrollPane = new JScrollPane(table);
        table.setFillsViewportHeight(true);
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

        JButton jStart = new JButton("Start Fighting");
        jStart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                forceMouseInit();
                //
                if (!updateMice()) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "Connect mice and click \"init mice\"");
                    return;
                }
                if (table.getSelectedRow() < 0) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "Select fight #");
                    return;
                }
                if (!canStartFighting.get(table.getSelectedRow())) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "played");
                    return;
                }
                activeFighting = allFighting.get(table.getSelectedRow());

                Rectangle defaultBounds = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDefaultConfiguration().getBounds();
                GraphicsDevice[] screenDevices = GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
                final Rectangle bounds[] = new Rectangle[screenDevices.length];
                for (int i = 0; i < screenDevices.length; i++) {
                    bounds[i] = screenDevices[i].getDefaultConfiguration().getBounds();
                    if (bounds[i].equals(defaultBounds)) {
                        Rectangle t = bounds[0];
                        bounds[0] = bounds[i];
                        bounds[i] = t;
                    }
                }
                final Fighting finalFighting = activeFighting;
                scoreTable = new ArrayList<>();
                for (int i = 0; i < screenDevices.length; i++) {
                    scoreTable.add(new JFrameScoreTable(i == 0, bounds[i], finalFighting));
                }
                for (int i = 0; i < screenDevices.length; i++) {
                    final JFrameScoreTable jFrameScoreTable = scoreTable.get(i);
                    SwingUtilities.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            jFrameScoreTable.setVisible(true);
                        }
                    });
                }
                /**/
            }
        });


        // выбор файла с боями
        JButton jButtonLoadData = new JButton("Select list of pairs...");
        jButtonLoadData.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
                if (chooser.showOpenDialog(JFrameMainJudge.this) == JFileChooser.APPROVE_OPTION) {
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
                if (chooser.showSaveDialog(JFrameMainJudge.this) == JFileChooser.APPROVE_OPTION) {
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

        JButton jButtonAdv = new JButton("Advertisement...");
        jButtonAdv.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JDialogAdv dlg = new JDialogAdv(JFrameMainJudge.this, intervalAdv);
                dlg.setVisible(true);
                if (!dlg.execCode())
                    return;
                intervalAdv = dlg.getInterval();

                System.err.println("intervalAdv: " + intervalAdv);
                for (JFrameAdvertising adv : jFrameAdvertisings) {
                    adv.setInterval(intervalAdv);
                }

                JsonObject jsonObject = new JsonObject();
                jsonObject.addProperty("intervalAdv", intervalAdv);

                try {
                    PrintStream out = new PrintStream(new FileOutputStream(pathAdvJson));
                    out.print(new Gson().toJson(jsonObject));
                    out.flush();
                    out.close();
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                }
            }
        });

        // добавление всех компонентов на панель
        JPanel jPanel = new JPanel();
        jPanel.setLayout(new BoxLayout(jPanel, BoxLayout.Y_AXIS));
        jPanel.add(jScrollPane);
        jPanel.add(jStart);
        jPanel.add(jButtonLoadData);
        jPanel.add(jButtonSaveFile);
        jPanel.add(jButtonInitMice);
        jPanel.add(jButtonAdv);

        return jPanel;
    }

    private void forceMouseInit() {
        synchronized (mouseController) {
            int i = 0;
            for (Controller controller : ControllerEnvironment.getDefaultEnvironment().getControllers()) {
                if (controller.getType() == Controller.Type.MOUSE) {
                    Mouse mouse = (Mouse) controller;
                    if (i < 3) {
                        mouseController[i++] = new MouseController(mouse);
                    }
                }
            }
        }
    }

    private void initListOfPlayers(String path) {
        String JSON_DATA;
        try {
            JSON_DATA = new String(Files.readAllBytes(Paths.get(path)), StandardCharsets.UTF_8);
        } catch (IOException e1) {
            e1.printStackTrace();
            return;
        }

        final String[] heads = new String[]{"Fight #", "Red conner", "Country/Region", "Blue conner", "Country/Region",
                "Winner", "Result", "Tournament Categoty", "Duration of fight", "Duration of break", "Count of rounds",
                "In case of tie",
                "Duration of extra round"};
        final Vector<Object[]> data = new Vector<>();


        allFighting = new Vector<>();
        canStartFighting = new Vector<>();
        for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
            JsonObject object = jsonElement.getAsJsonObject();

            Fighting f = new Fighting(
                    object.get("nameOfLeftFighter").getAsString(),
                    object.get("nameOfRightFighter").getAsString(),
                    object.get("fightId").getAsInt(),
                    object.get("categoryOfFighting").getAsString(),

                    object.get("countOfRounds").getAsInt(),
                    object.get("durationOfRound").getAsInt() * 1000,
                    object.get("durationOfBreak").getAsInt() * 1000,
                    object.get("DURATION_EXTRA_ROUND").getAsInt() * 1000,
                    object.get("IN_CASE_TIE").getAsInt(),
                    //1,1,1,  0, 0

                    ImageUtils.decodeToImage(object.get("leftFlag").getAsString(), Color.red),
                    ImageUtils.decodeToImage(object.get("rightFlag").getAsString(), Color.blue),

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
            String winnerStr = "";
            if (0 < winner) {
                if (winner == left)
                    winnerStr = object.get("nameOfLeftFighter").getAsString();
                else if (winner == right)
                    winnerStr = object.get("countryOfRightFighter").getAsString();
                else
                    throw new RuntimeException();
                canStartFighting.add(false);
            } else {
                canStartFighting.add(true);
            }
            String result = winner == 0 ? "" : object.get("result").getAsString();
            int in_case_tie = object.get("IN_CASE_TIE").getAsInt();
            data.add(new Object[]{
                    object.get("fightId").getAsInt(),

                    object.get("nameOfLeftFighter").getAsString(),
                    object.get("countryOfLeftFighter").getAsString(),

                    object.get("nameOfRightFighter").getAsString(),
                    object.get("countryOfRightFighter").getAsString(),

                    winnerStr,
                    result,

                    object.get("categoryOfFighting").getAsString(),
                    object.get("durationOfRound").getAsInt(),
                    object.get("durationOfBreak").getAsInt(),
                    object.get("countOfRounds").getAsInt(),

                    in_case_tie == 0 ? "Mouse click" : in_case_tie == 1 ? "European system" : "Extra round",
                    object.get("DURATION_EXTRA_ROUND").getAsInt(),

            });
        }
        table.setModel(new AbstractTableModel() {
            @Override
            public int getRowCount() {
                return data.size();
            }

            @Override
            public int getColumnCount() {
                return heads.length;
            }

            @Override
            public Object getValueAt(int rowIndex, int columnIndex) {
                return data.get(rowIndex)[columnIndex];
            }

            @Override
            public String getColumnName(int column) {
                return heads[column];
            }
        });
    }

//    private void initJPanelFighting() {
//        jPanelFighting = new JPanel();
//        jPanelFighting.setLayout(new GridBagLayout());
//
//
//        JPanel jPanelRight = new JPanel();
//        jPanelRight.setLayout(new BoxLayout(jPanelRight, BoxLayout.Y_AXIS));
//        JLabel[] jLabels = new JLabel[]{
//                new JLabel("Q - minus кр. углу"),
//                new JLabel("O - minus син. углу"),
//                new JLabel("T - отмена последнего minus"),
//                new JLabel(" "),
//                new JLabel("A - fo. кр. углу"),
//                new JLabel("K - fo. син. углу"),
//                new JLabel("G - отмена последнего fo."),
//                new JLabel(" "),
//                new JLabel("Z - ex. кр. углу"),
//                new JLabel("M - ex. син. углу"),
//                new JLabel("V - отмена последнего ex."),
//                new JLabel(" "),
//                new JLabel("W - нокаут кр. угла"),
//                new JLabel("I - нокаут син. угла"),
//                new JLabel(" "),
//                new JLabel("S - отказ от боя кр. угла"),
//                new JLabel("J - отказ от боя син. угла"),
//                new JLabel(" "),
//                new JLabel("X - дисквалификация кр. угла"),
//                new JLabel("N - дисквалификация син. угла"),
//                new JLabel(" "),
//                new JLabel("E - остановка боя рефери кр. угла"),
//                new JLabel("U - остановка боя рефери син. угла"),
//                new JLabel(" "),
//                new JLabel("D - технический нокаут кр. угла"),
//                new JLabel("H - технический нокаут син. угла"),
//                new JLabel(" "),
//                new JLabel("C - невозможность продолжать бой кр. угла"),
//                new JLabel("B - невозможность продолжать бой син. угла"),
//                new JLabel(" "),
//                new JLabel("R - отказ секунданта кр. угла"),
//                new JLabel("Y - отказ секунданта син. угла"),
//                new JLabel(" "),
//                new JLabel("SPACE - начать бой/пауза/выход"),
//        };
//        for (JLabel jLabel : jLabels) {
//            Font font = jLabel.getFont();
//            //jLabel.setFont(new Font(font.getName(), Font.PLAIN, 20));
//            jPanelRight.add(jLabel);
//        }
//
//        GridBagConstraints c = new GridBagConstraints();
//        c.fill = GridBagConstraints.BOTH;
//        c.weightx = 0.8;
//        c.weighty = 1;
//        c.gridx = 0;
//        c.gridy = 0;
//        jPanelFighting.add(allJPanelScoreTable[0], c);
////        allJPanelScoreTable[0].setFighting(f()); // TODO
//
//        c.fill = GridBagConstraints.BOTH;
//        c.weightx = 0.2;
//        c.weighty = 1;
//        c.gridx = 1;
//        c.gridy = 0;
//        jPanelFighting.add(jPanelRight, c);
//    }


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
        if (pressedKeys.contains(Component.Identifier.Key.O)) {
            activeFighting.addMinusToRight();
        }

        // Если предупреждение кому-то
        if (pressedKeys.contains(Component.Identifier.Key.A)) {
            activeFighting.addForestallingToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.K)) {
            activeFighting.addForestallingToRight();
        }

        //  Если выход за ринг у кого-то
        if (pressedKeys.contains(Component.Identifier.Key.Z)) {
            activeFighting.addExToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.M)) {
            activeFighting.addExToRight();
        }

        if (pressedKeys.contains(Component.Identifier.Key.G)) {
            activeFighting.cancelLastAction();
        }

        if (pressedKeys.contains(Component.Identifier.Key.ESCAPE)) {
            if (activeFighting.getFightStatus() == FightStatus.NotStart || activeFighting.getWinner() != Player.unknown) {
                for (JFrameScoreTable jFrameScoreTable : scoreTable) {
                    jFrameScoreTable.setVisible(false);
                }
            }

            if (activeFighting.getWinner() != Player.unknown) {
                try {
                    String JSON_DATA = new String(Files.readAllBytes(Paths.get(pathSaveJson)), StandardCharsets.UTF_8);
                    JsonArray jsonArray = new JsonArray();
                    for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
                        JsonObject object = jsonElement.getAsJsonObject();
                        for (Fighting f : allFighting) {
                            if (f.TOURNAMENT_CATEGORIES_FK == object.get("TOURNAMENT_CATEGORIES_FK").getAsLong() &&
                                    f.VERTEX == object.get("VERTEX").getAsLong()) {
                                object.addProperty("orderUID", activeFighting.getWinner() == Player.left ? object.get("orderUID_left").getAsLong() : object.get("orderUID_right").getAsLong());
                                object.addProperty("result", f.getResult());
                            }
                        }
                        System.err.println(object.get("fightId"));
                        jsonArray.add(object);
                    }
                    System.err.println("-----------");

                    PrintStream out = new PrintStream(new FileOutputStream(pathSaveJson));
                    out.print(new Gson().toJson(jsonArray));
                    out.flush();
                    out.close();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                initListOfPlayers(pathSaveJson);
            }
        }

        if (pressedKeys.contains(Component.Identifier.Key.SPACE))
            activeFighting.pressedKeySpace();


    }


//    private static void hideCursor(Container c) {
//        // create a transparent 16 x 16 pixel cursor image
//        BufferedImage cursorIm = new BufferedImage(16, 16, BufferedImage.TYPE_INT_ARGB);
//        // create a new blank cursor
//        Cursor blankCursor = Toolkit.getDefaultToolkit().createCustomCursor(cursorIm, new Point(0, 0), "blank cursor");
//        // assign the blank cursor to the JFrame
//        c.setCursor(blankCursor);
//    }

}
