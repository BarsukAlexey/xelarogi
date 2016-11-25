package net.pskov;

import com.google.gson.*;
import net.java.games.input.Component;
import net.pskov.controller.KeyboardController;
import net.pskov.controller.MouseController;
import net.pskov.some_enum.FightStatus;
import net.pskov.some_enum.Player;
import net.pskov.some_enum.PointPanelMode;
import net.pskov.utils.ImageUtils;
import net.pskov.utils.ReportUtis;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.Timer;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.text.SimpleDateFormat;
import java.util.*;

public class JFrameMainJudge extends JFrame {

    public static final String pathSaveJson = "save.json";
    private final String pathAdvJson = "adv.json";


    private final JTable table; // список дерущихся

    private volatile ModelFight activeFighting;
    private volatile Vector<ModelFight> allFighting;
    private volatile Vector<Boolean> canStartFight;
    private volatile Vector<String> stringOpenSystem;

    private final MouseController[] mouseController;
    private final KeyboardController keyboardController;

    private boolean showAdv;
    private int intervalAdv;
    ArrayList<JFrameScoreTable> scoreTable;


    private final ArrayList<JFrameAdvertising> jFrameAdvertisings;

    JFrameMainJudge(MouseController[] mouseController, KeyboardController keyboardController) {
        super("Judge");

        scoreTable = new ArrayList<>();

        this.mouseController = mouseController;
        this.keyboardController = keyboardController;


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


                int width = comp.getPreferredSize().width;
                width = Math.max(width, component.getPreferredSize().width + getIntercellSpacing().width);
                width = Math.max(width, tableColumn.getPreferredWidth());
                tableColumn.setPreferredWidth(width);
                return component;
            }
        };


        try {
            String JSON_DATA = new String(Files.readAllBytes(Paths.get(pathAdvJson)), StandardCharsets.UTF_8);
            JsonObject object = new JsonParser().parse(JSON_DATA).getAsJsonObject();
            intervalAdv = object.get("intervalAdv").getAsInt();
            showAdv = object.get("showAdv").getAsBoolean();
        } catch (IOException e1) {
            e1.printStackTrace();
            showAdv = true;
            intervalAdv = 15;
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
                            else
                                System.err.println("Can't read adv file: " + file.getAbsolutePath());
                        } catch (Throwable e) {
                            e.printStackTrace();
                            System.err.println("Can't read adv file: " + file.getAbsolutePath());
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

        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        JMenu menu = new JMenu("Settings...");
        menuBar.add(menu);
        JMenuItem menuItem;

        menuItem = new JMenuItem("Add fight...");
        menuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JDialogAddPair dlg = new JDialogAddPair();
                dlg.pack();
                dlg.setLocationRelativeTo(null);
                dlg.setVisible(true);
                JFrameMainJudge.this.initListOfPlayers(JFrameMainJudge.pathSaveJson);
            }
        });
        menu.add(menuItem);

        menuItem = new JMenuItem("Select list of pairs...");
        menuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileFilter(new FileNameExtensionFilter("json", "json"));
                chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
                chooser.setPreferredSize(new Dimension(800, 600));
                if (chooser.showOpenDialog(JFrameMainJudge.this) == JFileChooser.APPROVE_OPTION) {
                    String path = chooser.getSelectedFile().getAbsolutePath();
                    try {
                        Files.copy(Paths.get(path), Paths.get(pathSaveJson), StandardCopyOption.REPLACE_EXISTING);
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    initListOfPlayers(path);
                }
            }
        });
        menu.add(menuItem);

        menuItem = new JMenuItem("Save results...");
        menuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setSelectedFile(new File("Results " + new SimpleDateFormat(" yyyy.MM.dd  HH'h'mm'm'").format(new Date()) + ".json"));
                chooser.setPreferredSize(new Dimension(800, 600));
                if (chooser.showSaveDialog(JFrameMainJudge.this) == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = chooser.getSelectedFile();
                    try {
                        Files.copy(Paths.get(pathSaveJson), selectedFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                }
            }
        });
        menu.add(menuItem);


        menuItem = new JMenuItem("Advertisement...");
        menuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JDialogAdv dlg = new JDialogAdv(JFrameMainJudge.this, showAdv, intervalAdv);
                dlg.setVisible(true);
                if (!dlg.execCode())
                    return;
                showAdv = dlg.getShowAdv();
                intervalAdv = dlg.getInterval();

                System.err.println("intervalAdv: " + intervalAdv);
                for (JFrameAdvertising adv : jFrameAdvertisings) {
                    adv.setInterval(intervalAdv);
                }

                JsonObject object = new JsonObject();
                object.addProperty("intervalAdv", intervalAdv);
                object.addProperty("showAdv", showAdv);

                try {
                    PrintStream out = new PrintStream(new FileOutputStream(pathAdvJson));
                    out.print(new Gson().toJson(object));
                    out.flush();
                    out.close();
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                }
            }
        });
        menu.add(menuItem);


        setContentPane(initUI());
        initListOfPlayers(pathSaveJson);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
//        setUndecorated(true);
        pack();
        setBounds(defaultBounds);
        setExtendedState(Frame.MAXIMIZED_BOTH);
        setVisible(true);
//        setSize(1280, 800);

        new Timer(20, new ActionListener() { //
            //new Timer(50, new ActionListener() {
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





        final JButton jStart = new JButton("Start Fight");
        jStart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
//                forceMouseInit();
                //
                if (!updateMice()) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "Close this program, connect mice and start this program");
                    return;
                }
                if (table.getSelectedRow() < 0) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "Select fight #");
                    return;
                }
                if (!canStartFight.get(table.getSelectedRow())) {
                    JOptionPane.showMessageDialog(JFrameMainJudge.this, "It can not be started");
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
                final ModelFight finalFighting = activeFighting;
                scoreTable = new ArrayList<>();
                for (int i = 0; i < screenDevices.length; i++) {
                    scoreTable.add(new JFrameScoreTable(i == 0, bounds[i], finalFighting));
                }


                for (int i = 1; i < screenDevices.length; i++) {
                    scoreTable.get(i).setModal(false);
                    scoreTable.get(i).setVisible(true);
//                    final JFrameScoreTable jFrameScoreTable = scoreTable.get(i);
//                    SwingUtilities.invokeLater(new Runnable() {
//                        @Override
//                        public void run() {
//                            jFrameScoreTable.setVisible(true);
//                        }
//                    });
                }
                scoreTable.get(0).setVisible(true);
                activeFighting = null;
            }
        });


        final JButton buttonOpeningSystem = new JButton("Show detail report");
        buttonOpeningSystem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int row = table.getSelectedRow();
                if (row < 0) return;

                JDialog dlg = new JDialog(JFrameMainJudge.this, "", true);

                JScrollPane jsp;
                JTextPane jta;

                jta = new JTextPane();
                jta.setEditable(false);
                jta.setContentType("text/html");
                jta.setText(stringOpenSystem.get(row));

                jsp = new JScrollPane(jta);
                //jsp.setPreferredSize(new Dimension(250, 450));

                dlg.setLayout(new BorderLayout());
                dlg.add(jsp, BorderLayout.CENTER);
                dlg.pack();
                dlg.setLocationRelativeTo(null);
                dlg.setVisible(true);

            }
        });




        // добавление всех компонентов на панель
        JPanel jPanel = new JPanel();
        jPanel.setLayout(new BoxLayout(jPanel, BoxLayout.Y_AXIS));
        jPanel.add(jScrollPane);
        jPanel.add(jStart);
        jPanel.add(buttonOpeningSystem);

        return jPanel;
    }

//    private void forceMouseInit() {
//        synchronized (mouseController) {
//            int i = 0;
//            for (Controller controller : ControllerEnvironment.getDefaultEnvironment().getControllers()) {
//                if (controller.getType() == Controller.Type.MOUSE) {
//                    Mouse mouse = (Mouse) controller;
//                    if (i < 3) {
//                        mouseController[i++] = new MouseController(mouse);
//                    }
//                }
//            }
//        }
//    }

    private void initListOfPlayers(String path) {
        String JSON_DATA;
        try {
            JSON_DATA = new String(Files.readAllBytes(Paths.get(path)), StandardCharsets.UTF_8);
        } catch (IOException e1) {
            //e1.printStackTrace();
            return;
        }

//        String JSON_DATA = "";
//        Path pat2h = Paths.get(pathSaveJson);
//        java.util.List<String> strings = null;
//        try {
//            strings = Files.readAllLines(pat2h, );
//            for (String string : strings) {
//                System.err.println(string);
//                System.err.flush();
//                JSON_DATA += string;
//            }
//        } catch (IOException e) {
//            e.printStackTrace();
//        }

//        String JSON_DATA = "";
//        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
//            StringBuilder sb = new StringBuilder();
//            String line = br.readLine();
//
//            while (line != null) {
//                sb.append(line);
//                sb.append(System.lineSeparator());
//                line = br.readLine();
//            }
//            JSON_DATA = sb.toString();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }


        final String[] heads = new String[]{"Fight #", "Can be started?", "Red conner", "Country/Region", "Blue conner", "Country/Region",
                "Winner", "Result", "Tournament Categoty", "Duration of fight", "Duration of break", "Count of rounds",
                "In case of tie",
                "Duration of extra round",
                "Point panel mode"
        };
        final Vector<Object[]> data = new Vector<>();

        allFighting = new Vector<>();
        canStartFight = new Vector<>();
        stringOpenSystem = new Vector<>();
        for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
            JsonObject object = jsonElement.getAsJsonObject();

            ModelFight f = new ModelFight(
                    object.get("nameOfLeftFighter").getAsString(),
                    object.get("nameOfRightFighter").getAsString(),
                    object.get("fightId").getAsInt(),
                    object.get("categoryOfFightingShort").getAsString(),

                    object.get("countOfRounds").getAsInt(),
                    object.get("durationOfRound").getAsInt() * 1000,
                    object.get("durationOfBreak").getAsInt() * 1000,
                    object.get("DURATION_EXTRA_ROUND").getAsInt() * 1000,
                    object.get("IN_CASE_TIE").getAsInt(),
//                    2, 10 * 1000, 3 * 1000, 0 * 1000, 1,

                    ImageUtils.decodeToImage(object.get("leftFlag").getAsString(), Color.red),
                    ImageUtils.decodeToImage(object.get("rightFlag").getAsString(), Color.blue),

                    object.get("regionOfLeftFighter").getAsString(),
                    object.get("regionOfRightFighter").getAsString(),
                    object.get("TOURNAMENT_CATEGORIES_FK").getAsLong(),
                    object.get("VERTEX").getAsInt(),
                    object.get("POINT_PANEL_MODE").getAsInt() == 0 ? PointPanelMode.LightContact :
                            object.get("POINT_PANEL_MODE").getAsInt() == 1 ? PointPanelMode.K1 :
                                    PointPanelMode.FullContact
            );
            allFighting.add(f);
            long winner = object.get("orderUID") == null ? -1 : object.get("orderUID").getAsLong();
            long left = object.get("orderUID_left") == null ? -1 : object.get("orderUID_left").getAsLong();
            long right = object.get("orderUID_right") == null ? -1 : object.get("orderUID_right").getAsLong();
            String winnerStr = "";
            if (0 < winner) {
                if (winner == left)
                    winnerStr = object.get("nameOfLeftFighter").getAsString();
                else if (winner == right)
                    winnerStr = object.get("nameOfRightFighter").getAsString();
//                else TODO
//                    throw new RuntimeException();
            }
            String result = winner == -1 ? "" : object.get("result").getAsString();
            int in_case_tie = object.get("IN_CASE_TIE").getAsInt();

            boolean canStart =
                    object.get("orderUID_left") != null && 0 < object.get("orderUID_left").getAsLong() &&
                            object.get("orderUID_right") != null && 0 < object.get("orderUID_right").getAsLong() &&
                            object.get("orderUID") == null;
            canStartFight.add(canStart);

            String report;
            if (object.get("report") != null)
                report = object.get("report").getAsString();
            else
                report = "#";
            stringOpenSystem.add(report);

            data.add(new Object[]{
                    object.get("fightId").getAsInt(),
                    canStart ? "Yes" : "No",

                    object.get("nameOfLeftFighter").getAsString(),
                    object.get("regionOfLeftFighter").getAsString(),

                    object.get("nameOfRightFighter").getAsString(),
                    object.get("regionOfRightFighter").getAsString(),

                    winnerStr,
                    result,

                    object.get("categoryOfFighting").getAsString(),
                    object.get("durationOfRound").getAsInt(),
                    object.get("durationOfBreak").getAsInt(),
                    object.get("countOfRounds").getAsInt(),

                    in_case_tie == 0 ? "Mouse click" : in_case_tie == 1 ? "European system" : "Extra round",
                    object.get("DURATION_EXTRA_ROUND").getAsInt(),
                    object.get("POINT_PANEL_MODE").getAsInt() == 0 ? "Light contact mode" :
                            object.get("POINT_PANEL_MODE").getAsInt() == 1 ? "K-1 mode" :
                                    "Full contact mode"
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

                if (mouse.wasLeftClick()) {
                    if (activeFighting != null) {
                        activeFighting.addOnePointToLeftFighter(i);
                        System.err.println("mouse click # " + i + "  Left");
                    }
                }
                if (mouse.wasRightClick()) {
                    if (activeFighting != null) {
                        activeFighting.addOnePointToRightFighter(i);
                        System.err.println("mouse click # " + i + "  right");
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

        //  Если выход за ринг у кого-то или KNOCK DOWN
        if (pressedKeys.contains(Component.Identifier.Key.Z)) {
            if (activeFighting.getPointPanelMode() == PointPanelMode.LightContact)
                activeFighting.addExToLeft();
            else if (activeFighting.getPointPanelMode() == PointPanelMode.K1 ||
                    activeFighting.getPointPanelMode() == PointPanelMode.FullContact)
                activeFighting.addKnockDownToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.M)) {
            if (activeFighting.getPointPanelMode() == PointPanelMode.LightContact)
                activeFighting.addExToRight();
            else if (activeFighting.getPointPanelMode() == PointPanelMode.K1 ||
                    activeFighting.getPointPanelMode() == PointPanelMode.FullContact)
                activeFighting.addKnockDownToRight();
        }

        if (pressedKeys.contains(Component.Identifier.Key.W)) {
            if (activeFighting.getPointPanelMode() == PointPanelMode.FullContact)
                activeFighting.addKickCountToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.I)) {
            if (activeFighting.getPointPanelMode() == PointPanelMode.FullContact)
                activeFighting.addKickCountToRight();
        }

        if (pressedKeys.contains(Component.Identifier.Key.G)) {
            activeFighting.cancelLastAction();
        }

        if (pressedKeys.contains(Component.Identifier.Key.ESCAPE)) {
            if (activeFighting.getStatus() == FightStatus.NotStart || activeFighting.getWinner() != Player.NoPlayer) {
                for (JFrameScoreTable jFrameScoreTable : scoreTable) {
                    jFrameScoreTable.dispose();
                }
            }

            if (activeFighting.getWinner() != Player.NoPlayer) {
                try {
                    String JSON_DATA = new String(Files.readAllBytes(Paths.get(pathSaveJson)), StandardCharsets.UTF_8);

                    JsonArray jsonArray = new JsonParser().parse(JSON_DATA).getAsJsonArray();
                    JsonObject object1 = null;
                    for (JsonElement jsonElement : jsonArray) {
                        JsonObject object = jsonElement.getAsJsonObject();
                        if (activeFighting.getTOURNAMENT_CATEGORIES_FK() == object.get("TOURNAMENT_CATEGORIES_FK").getAsLong() &&
                                activeFighting.getVERTEX() == object.get("VERTEX").getAsLong()) {
                            object.addProperty("orderUID", activeFighting.getWinner() == Player.Left ? object.get("orderUID_left").getAsLong() : object.get("orderUID_right").getAsLong());
                            object.addProperty("result", activeFighting.getResult());
                            object.addProperty("report", ReportUtis.getOpeningSystem(activeFighting));
                            object1 = object;
                            break;
                        }
                    }

                    String[] winnerKeys;
                    if (activeFighting.getWinner() == Player.Left) {
                        winnerKeys = new String[]{"nameOfLeftFighter", "orderUID_left", "regionOfLeftFighter", "leftFlag"};
                    } else {
                        winnerKeys = new String[]{"nameOfRightFighter", "orderUID_right", "regionOfRightFighter", "rightFlag"};
                    }

                    long TOURNAMENT_CATEGORIES_FK = activeFighting.getTOURNAMENT_CATEGORIES_FK();
                    int VERTEX = activeFighting.getVERTEX();
                    for (int i = 0; i < jsonArray.size(); ++i) {
                        JsonObject currentObject = jsonArray.get(i).getAsJsonObject();
                        if (currentObject.get("TOURNAMENT_CATEGORIES_FK").getAsLong() == TOURNAMENT_CATEGORIES_FK &&
                                currentObject.get("VERTEX").getAsLong() == VERTEX / 2) {

                            int pos = 0;
                            for (String key : new String[]{VERTEX % 2 == 1 ? "nameOfLeftFighter" : "nameOfRightFighter",
                                    VERTEX % 2 == 1 ? "orderUID_left" : "orderUID_right",
                                    VERTEX % 2 == 1 ? "regionOfLeftFighter" : "regionOfRightFighter",
                                    VERTEX % 2 == 1 ? "leftFlag" : "rightFlag"}) {
                                currentObject.add(key, object1.get(winnerKeys[pos++]));
                            }
                        }
                    }
                    // конец этого кода из пойнтфатинга

                    ArrayList<String> arr = new ArrayList<>();
                    arr.add(new Gson().toJson(jsonArray));
                    Files.write(Paths.get(pathSaveJson), arr, StandardCharsets.UTF_8);
//                    String JSON_DATA = new String(Files.readAllBytes(Paths.get(pathSaveJson)), StandardCharsets.UTF_8);
//
//                    JsonArray jsonArray = new JsonArray();
//                    for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
//                        JsonObject object = jsonElement.getAsJsonObject();
//                        if (activeFighting.getTOURNAMENT_CATEGORIES_FK() == object.get("TOURNAMENT_CATEGORIES_FK").getAsLong() &&
//                                activeFighting.getVERTEX() == object.get("VERTEX").getAsLong()) {
//                            object.addProperty("orderUID", activeFighting.getWinner() == Player.Left ? object.get("orderUID_left").getAsLong() : object.get("orderUID_right").getAsLong());
//                            object.addProperty("result", activeFighting.getResult());
//                        }
//                        jsonArray.add(object);
//                    }
//
//                    ArrayList<String> arr = new ArrayList<>();
//                    arr.add(new Gson().toJson(jsonArray));
//                    Files.write(Paths.get(pathSaveJson), arr, StandardCharsets.UTF_8);
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                initListOfPlayers(pathSaveJson);
            }
        }

        if (pressedKeys.contains(Component.Identifier.Key.SPACE))
            activeFighting.pressedKeySpace();
    }
}
