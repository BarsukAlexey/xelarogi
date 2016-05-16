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
import javax.swing.Timer;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.text.SimpleDateFormat;
import java.util.*;

public class JFrameMainJudge extends JFrame {

    private final String pathSaveJson = "save.json";
    private final String pathAdvJson = "adv.json";


    private final JTable table; // список дерущихся

    private volatile Fighting activeFighting;
    private volatile Vector<Fighting> allFighting;
    private volatile Vector<Boolean> canStartFighting;

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
        setExtendedState(Frame.MAXIMIZED_BOTH);
        setVisible(true);
//        setSize(1280, 800);

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

        final JButton jStart = new JButton("Start Fighting");
        jStart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
//                forceMouseInit();
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
                for (int i = 1; i < screenDevices.length; i++) {
                    final JFrameScoreTable jFrameScoreTable = scoreTable.get(i);
                    SwingUtilities.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            jFrameScoreTable.setVisible(true);
                        }
                    });
                }
                scoreTable.get(0).setVisible(true);

                activeFighting = null;
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
                chooser.setPreferredSize(new Dimension(800, 600));
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
                chooser.setPreferredSize(new Dimension(800, 600));
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

        JButton jButtonAdv = new JButton("Advertisement...");
        jButtonAdv.addActionListener(new ActionListener() {
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

        // добавление всех компонентов на панель
        JPanel jPanel = new JPanel();
        jPanel.setLayout(new BoxLayout(jPanel, BoxLayout.Y_AXIS));
        jPanel.add(jScrollPane);
        jPanel.add(jStart);
        jPanel.add(jButtonLoadData);
        jPanel.add(jButtonSaveFile);
        jPanel.add(jButtonAdv);

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
            e1.printStackTrace();
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
                    winnerStr = object.get("nameOfRightFighter").getAsString();
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
            if (activeFighting.getFightStatus() == FightStatus.NotStart || activeFighting.getWinner() != Player.Unknown) {
                for (JFrameScoreTable jFrameScoreTable : scoreTable) {
                    jFrameScoreTable.dispose();
                }
            }

            if (activeFighting.getWinner() != Player.Unknown) {
                try {
                    String JSON_DATA = new String(Files.readAllBytes(Paths.get(pathSaveJson)), StandardCharsets.UTF_8);

                    JsonArray jsonArray = new JsonArray();
                    for (JsonElement jsonElement : new JsonParser().parse(JSON_DATA).getAsJsonArray()) {
                        JsonObject object = jsonElement.getAsJsonObject();
                        if (activeFighting.getTOURNAMENT_CATEGORIES_FK() == object.get("TOURNAMENT_CATEGORIES_FK").getAsLong() &&
                                activeFighting.getVERTEX() == object.get("VERTEX").getAsLong()) {
                            object.addProperty("orderUID", activeFighting.getWinner() == Player.Left ? object.get("orderUID_left").getAsLong() : object.get("orderUID_right").getAsLong());
                            object.addProperty("result", activeFighting.getResult());
                        }
                        jsonArray.add(object);
                    }

                    ArrayList<String> arr = new ArrayList<>();
                    arr.add(new Gson().toJson(jsonArray));
                    Files.write(Paths.get(pathSaveJson), arr, StandardCharsets.UTF_8);
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
