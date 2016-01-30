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
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;

public class JFrameAdmin extends JFrame {

    private JPanelScoreTable jPanelScoreTableForJudge;
    private JFrame[] scoreBoardFrame; // Окна, которые отображаются на мониторах для зрителей. На каждом мониторе по одному окну

    private JPanelScoreTable[] allJPanelScoreTable;
    private Fighting activeFighting;

    private Fighting[] allActiveFighting;

    /**
     * время отпроса мышки и клавиатуры
     */
    private static final int DELAY = 50;
    private MouseController[] mouseController;

    private KeyboardController keyboardController;

    public JFrameAdmin() {
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


        allJPanelScoreTable = new JPanelScoreTable[originPoint.length];
        allJPanelScoreTable[0] = jPanelScoreTableForJudge = new JPanelScoreTable(true);
        scoreBoardFrame = new JFrame[originPoint.length - 1];
        for (int i = 0; i < scoreBoardFrame.length; i++) {
            scoreBoardFrame[i] = createFrameAtLocation(originPoint[i + 1], allJPanelScoreTable[i + 1] = new JPanelScoreTable(false));
        }

//        setLayout(new GridLayout(1, 2));
        setLayout(new GridBagLayout());

        JPanel jPanel = new JPanel();
//        jPanel.setLayout(new BoxLayout(jPanel, BoxLayout.Y_AXIS));
        jPanel.setLayout(new FlowLayout());
//        jPanel.setLayout(new GridBagLayout());
//        GridBagConstraints cc = new GridBagConstraints();
//        cc.fill = GridBagConstraints.BOTH;
//        c.weightx = 0.8;
//        c.weighty = 1;
//        cc.gridx = 0;
//        cc.gridy = 0;

        { // TODO DELETE
            activeFighting = f();
            for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                panelScoreTable.setFighting(activeFighting);
            }
        }

        Button buttonStart = new Button("Start");
        Button buttonPause = new Button("Pause");
        Button buttonContinue = new Button("Continue");
        buttonStart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                if (activeFighting == null) {
                    return; // TODO выберете раунд
                }
                for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                    panelScoreTable.setFighting(activeFighting);
                }
                buttonStart.setVisible(false);
                buttonPause.setVisible(true);
                revalidate();
                buttonPause.requestFocus();

//                jPanelScoreTableForJudge.setVisible(false);
//                jPanel.setVisible(false);

                // TODO перевести из состояния finishPending в finish
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        activeFighting.startRound();
                        while (true) { // на весь этот цикл даётся 200 мс
                            long beginTime = System.currentTimeMillis();
                            activeFighting.updateTime();
                            for (JPanelScoreTable panelScoreTable : allJPanelScoreTable) {
                                panelScoreTable.repaint();
                            }
                            if (activeFighting.getStatusFighting() == StatusFighting.fighting) {
                                if (!buttonPause.isVisible()) {
                                    buttonPause.setVisible(true);
                                    revalidate();
                                    buttonPause.requestFocus();
                                }
                            } else {
                                if (buttonPause.isVisible()) {
                                    buttonPause.setVisible(false);
                                    revalidate();
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
//                        buttonStart.setVisible(true);
//                        buttonStart.requestFocus();
//                        buttonPause.setVisible(false);
//                        buttonContinue.setVisible(false);
//                        revalidate();
                    }
                }).start();
                /**/
            }
        });
        buttonPause.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                activeFighting.pauseRound();
                buttonPause.setVisible(false);
                buttonContinue.setVisible(true);
                revalidate();
                buttonContinue.requestFocus();
            }
        });
        buttonContinue.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                activeFighting.continueRound();
                buttonPause.setVisible(true);
                buttonContinue.setVisible(false);
                revalidate();
                buttonContinue.requestFocus();
            }
        });


        buttonPause.setVisible(false);
        buttonContinue.setVisible(false);

        jPanel.add(buttonStart);
        jPanel.add(buttonPause);
        jPanel.add(buttonContinue);


//        add(jPanelScoreTableForJudge);
//        add(jPanel);

        jPanelScoreTableForJudge.setBorder(BorderFactory.createLineBorder(Color.black));
        jPanel.setBorder(BorderFactory.createLineBorder(Color.red));


        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 0.8;
        c.weighty = 1;
        c.gridx = 0;
        c.gridy = 0;
        add(jPanelScoreTableForJudge, c);

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 0.2;
        c.weighty = 1;
        c.gridx = 1;
        c.gridy = 0;
        add(jPanel, c);


//        initMiceAndKeyboard();


        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLocation(originPoint[0]);
        pack();
//        setExtendedState(Frame.MAXIMIZED_BOTH);
        setVisible(true);
        setSize(1200, 800);


        allActiveFighting = new Fighting[0];

//        buttonStart.addKeyListener(new KeyAdapter() {
//                                       @Override
//                                       public void keyPressed(KeyEvent e) {
//                                           System.err.println(e);
//                                       }
//
//                                       @Override
//                                       public void keyReleased(KeyEvent e) {
//                                           System.err.println(e);
//                                       }
//
//                                       @Override
//                                       public void keyTyped(KeyEvent e) {
//                                           System.err.println(e);
//                                       }
//                                   }
//        );

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    long startTime = System.currentTimeMillis();
                    updateMice();
                    updateKeyboard();
                    long duration = System.currentTimeMillis() - startTime;
//                    System.err.println(duration);
                    if (duration < DELAY) {
                        try {
                            Thread.sleep(DELAY - duration);  // wait until DELAY time has passed
                        } catch (Exception ex) {
                            ex.printStackTrace();
                        }
                    } else {
                        System.err.println("LOL: " + (duration - DELAY));
                    }
                }
            }
        }).start();
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


        // Если минус балл кому-то
        if (pressedKeys.contains(Component.Identifier.Key.Q)) {
            if (activeFighting != null)
                activeFighting.addMinusToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.T)) {
            if (activeFighting != null)
                activeFighting.cancelLastMinus();
        }
        if (pressedKeys.contains(Component.Identifier.Key.O)) {
            if (activeFighting != null)
                activeFighting.addMinusToRight();
        }


        // Если предупреждение кому-то
        if (pressedKeys.contains(Component.Identifier.Key.A)) {
            if (activeFighting != null)
                activeFighting.addForestallingToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.G)) {
            if (activeFighting != null)
                activeFighting.cancelLastForestalling();
        }
        if (pressedKeys.contains(Component.Identifier.Key.K)) {
            if (activeFighting != null)
                activeFighting.addForestallingToRight();
        }


        //  Если выход за ринг у кого-то
        if (pressedKeys.contains(Component.Identifier.Key.Z)) {
            if (activeFighting != null)
                activeFighting.addExToLeft();
        }
        if (pressedKeys.contains(Component.Identifier.Key.V)) {
            if (activeFighting != null)
                activeFighting.cancelLastEx();
        }
        if (pressedKeys.contains(Component.Identifier.Key.M)) {
            if (activeFighting != null)
                activeFighting.addExToRight();
        }
    }

    private Fighting f() {
        try {
            return new Fighting("Иван  Иванович", "Василий Васильевич", 2, "FC f-52", 2, 3, 1, ImageIO.read(new File("resources\\images\\Canada.png")), ImageIO.read(new File("resources\\images\\Qatar.png")), "Canada", "Qatar");
        } catch (IOException e) {
            return null;
        }
    }

    private JFrame createFrameAtLocation(Point p, JPanel jPanel) {
        JFrame frame = new JFrame();
        frame.add(jPanel);
//        frame.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE); // TODO
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // TODO
        frame.setLocation(p);
        frame.setAlwaysOnTop(true); // TODO
        frame.setUndecorated(true);
//        hideCursor(container);
        frame.pack();
        frame.setExtendedState(Frame.MAXIMIZED_BOTH);
        frame.setVisible(true);

//        frame.setSize(4 * 200, 3 * 200);
//        frame.setSize(3 * 200, 2 * 200);
//        frame.setSize(16 * 200, 9 * 200);
//        frame.setSize((int) (1.85 * 700), 700);
//        frame.setSize((int) (2.39 * 700), 700);


//        frame.addWindowFocusListener(new WindowAdapter() { // TODO
//            @Override
//            public void windowLostFocus(WindowEvent e) {
//                frame.setExtendedState(Frame.MAXIMIZED_BOTH);
//                frame.requestFocus();
//            }
//        });
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
