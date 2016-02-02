package net.pskov;

import net.java.games.input.Component;
import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;
import net.java.games.input.Mouse;
import net.pskov.controller.KeyboardController;
import net.pskov.controller.MouseController;
import net.pskov.someEnum.StatusFighting;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;

public class JFrameMainJudge extends JFrame {

    private JPanel jPanelStartPage; // панелька, на которой выбирается бой, настраиваются мышки, сохраняются результаты...
    private JPanel jPanelFighting;  // панелька, на которой находится табло боя и подсказки как управлять боем

    private JFrame[] jFrameSpectator; // Окна, которые отображаются на мониторах для зрителей. На каждом мониторе по одному окну

    private JPanelScoreTable[] allJPanelScoreTable; // все табло, включая то, что у главного судьи (оно 0ое в массиве)

    private volatile Fighting activeFighting;

    private MouseController[] mouseController;
    private KeyboardController keyboardController;

    public JFrameMainJudge() {
        super();

        initMiceAndKeyboard();

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

//        add(jPanelFighting);
//        remove(jPanelFighting);
        add(jPanelStartPage);
//        remove(jPanelStartPage);

//        jPanelFighting.setVisible(false);
//        revalidate();

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLocation(originPoint[0]);
//        setUndecorated(true);
//        setExtendedState(Frame.MAXIMIZED_BOTH);
        pack();
        setVisible(true);
        setSize(1200, 800);

        new Updater().start();

    }

    private void initJPanelStartPage() {
        // создания списка боёв
        final JList<Fighting> jList;
        Fighting[] fightings;
        try {
            fightings = new Fighting[]{
                    new Fighting("Быстрий Иван", "Быстрый Егор", 4, "FC M-2", 1, 3, 2, ImageIO.read(new File("resources\\images\\rus.png")), ImageIO.read(new File("resources\\images\\Switzerland.png")), "Rus", "Switzerland"),
                    new Fighting("Иван  Иванович", "Василий Васильевич", 1, "FC f-52", 2, 30, 20, ImageIO.read(new File("resources\\images\\Canada.png")), ImageIO.read(new File("resources\\images\\Qatar.png")), "Canada", "Qatar"),
                    new Fighting("Петров Петрович", "Максим Максимыч", 2, "FC f-2", 3, 20, 13, ImageIO.read(new File("resources\\images\\rus.png")), ImageIO.read(new File("resources\\images\\Switzerland.png")), "Rus", "Switzerland"),
                    new Fighting("Петрова Ирина", "Шаманова Виктория", 3, "FC f-2", 3, 20, 13, ImageIO.read(new File("resources\\images\\rus.png")), ImageIO.read(new File("resources\\images\\Switzerland.png")), "Rus", "Switzerland"),
            };

        } catch (IOException e) {
            e.printStackTrace();
            fightings = new Fighting[0];
        }
        jList = new JList<>(fightings);
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
                Fighting selectedValue = jList.getSelectedValue();
                if (selectedValue == null) return;
                System.err.println("Fight: " + selectedValue); // TODO

                // Инифиализируем текущий бой
                activeFighting = selectedValue;
                for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                    panelScoreTable.setFighting(activeFighting);
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
                    System.out.println("You chose to open this file: " +
                            chooser.getSelectedFile().getAbsolutePath()
                    ); // TODO
                }
            }
        });


        JButton jButtonSaveFile = new JButton("Save results");
        jButtonSaveFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                int returnVal = chooser.showOpenDialog(jPanelStartPage);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    System.out.println("You chose to open this file: " + chooser.getSelectedFile().getAbsolutePath()); // TODO
                }
            }
        });

        // добавление всех компонентов на панель
        jPanelStartPage = new JPanel();
        jPanelStartPage.setLayout(new BoxLayout(jPanelStartPage, BoxLayout.Y_AXIS));
        jPanelStartPage.add(jScrollPane);
        jPanelStartPage.add(jStart);
        jPanelStartPage.add(jButtonSelectFile);
        jPanelStartPage.add(jButtonSaveFile);
    }

    void initJPanelFighting() {
        jPanelFighting = new JPanel();
        jPanelFighting.setLayout(new GridBagLayout());


        JPanel jPanelRight = new JPanel();
        jPanelRight.setLayout(new BoxLayout(jPanelRight, BoxLayout.Y_AXIS));
        JLabel[] jLabels = new JLabel[]{
                new JLabel("Q - minus to red"),
                new JLabel("O - minus to blue"),
                new JLabel("T - cancel last minus"),
                new JLabel(" "),
                new JLabel("A - fo. to red"),
                new JLabel("K - fo. to blue"),
                new JLabel("G - cancel last fo."),
                new JLabel(" "),
                new JLabel("Z - ex. to red"),
                new JLabel("M - ex. to blue"),
                new JLabel("V - cancel last ex."),
                new JLabel(" "),
                new JLabel("SPACE - start/pause round and exit"),
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


    private void initMiceAndKeyboard() {
        ControllerEnvironment ce = ControllerEnvironment.getDefaultEnvironment();
        Controller[] ca = ce.getControllers();
        if (ca.length == 0) {
            throw new RuntimeException();
        }
        // collect the IDs of all the mouse controllers
        ArrayList<Integer> mouseIDs = new ArrayList<>();
//        System.out.println("Mouse Controllers:");
        for (int i = 0; i < ca.length; i++) {
            if (ca[i].getType() == Controller.Type.MOUSE) {
//                System.out.println("  ID " + i + "; \"" + ca[i].getName() + "\"");
                mouseIDs.add(i);
            }
        }

        mouseController = new MouseController[mouseIDs.size()];
        for (int i = 0; i < mouseIDs.size(); i++) {
            mouseController[i] = new MouseController((Mouse) ca[mouseIDs.get(i)]);
        }

        keyboardController = new KeyboardController();
    }


    private boolean updateMice() {
        boolean update = false;
        for (int i = 0; i < Math.min(3, mouseController.length); i++) {
            MouseController mouse = mouseController[i];
            if (!mouse.update()) {
                System.out.println("Controller #" + i + " no longer valid");
                System.exit(-1); // TODO ОПАСНО!
            }
            if (mouse.wasLeftClick()) {
                if (activeFighting != null) {
                    activeFighting.addOnePointToLeftFighter(i);
                    update = true;
                }
            }
            if (mouse.wasRightClick()) {
                if (activeFighting != null) {
                    activeFighting.addOnePointToRightFighter(i);
                    update = true;
                }
            }
        }
        return update;
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

        // поставить на паузу
        if (pressedKeys.contains(Component.Identifier.Key.SPACE)) {
            if (activeFighting.getStatusFighting() == StatusFighting.notBegin) {
                activeFighting.startRound();
            } else if (activeFighting.getStatusFighting() == StatusFighting.fighting) {
                activeFighting.pauseRound();
            } else if (activeFighting.getStatusFighting() == StatusFighting.fightingPause) {
                activeFighting.continueRound();
            } else if (activeFighting.getStatusFighting() == StatusFighting.finishPending) {
                remove(jPanelFighting);
                add(jPanelStartPage);
                revalidate();
                repaint();
            }
        }
    }

    class Updater extends Thread {
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


    private Fighting f() {
        try {
            return new Fighting("Иван  Иванович", "Василий Васильевич", 2, "FC f-52", 2, 30, 20, ImageIO.read(new File("resources\\images\\Canada.png")), ImageIO.read(new File("resources\\images\\Qatar.png")), "Canada", "Qatar");
        } catch (IOException e) {
            return null;
        }
    }

    private JFrame createFrameAtLocation(Point p, JPanel jPanel) {
        JFrame frame = new JFrame();
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
