package net.pskov;

import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;
import net.java.games.input.Mouse;
import net.pskov.controller.MouseController;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

public class JDialogInitMice extends JDialog {

    final MouseController[] mouseControllers;
    boolean isInterrupt;

    JDialogInitMice(JFrame parent, MouseController[] mouseControllers) {
        super(parent, true);
        this.mouseControllers = mouseControllers;

        JPanel jPanel = new JPanel();
        jPanel.setLayout(new BoxLayout(jPanel, BoxLayout.Y_AXIS));
        jPanel.add(new JLabel("Welcome to master of mice setting!"));
        jPanel.add(new JLabel("To continue click next..."));
        jPanel.add(new JButton("Next...") {
            {
                addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        while (0 < jPanel.getComponentCount())
                            jPanel.remove(0);
                        jPanel.add(new JLabel("Click mouse of Judge #1"));
                        jPanel.add(new JLabel("then click mouse of Judge #2"));
                        jPanel.add(new JLabel("then click mouse of Judge #3"));
                        jPanel.add(new JLabel("then this window automatically close"));
                        jPanel.add(new JButton("Cancel") {
                            {
                                addActionListener(new ActionListener() { // я добавил addActionListener в addActionListener чтобы ты мог мог слушать действие, когда слушаешь действие
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        isInterrupt = true;
                                        JDialogInitMice.this.dispatchEvent(new WindowEvent(JDialogInitMice.this, WindowEvent.WINDOW_CLOSING));
                                    }
                                });
                            }
                        });
                        jPanel.revalidate();
                        jPanel.repaint();
                        new ThreadLOL().start();
                    }
                });
            }
        });
        jPanel.add(new JButton("Cancel") {
            {
                addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        isInterrupt = true;
                        JDialogInitMice.this.dispatchEvent(new WindowEvent(JDialogInitMice.this, WindowEvent.WINDOW_CLOSING));
                    }
                });
            }
        });
        add(jPanel);

        setUndecorated(true);
//        setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        setSize(500, 500);
        setVisible(true);
    }

    class ThreadLOL extends Thread {
        @Override
        public void run() {
            synchronized (mouseControllers) {
                ArrayList<MouseController> allMouseController = new ArrayList<>();
                for (Controller controller : ControllerEnvironment.getDefaultEnvironment().getControllers()) {
                    if (controller.getType() == Controller.Type.MOUSE) {
                        Mouse mouse = (Mouse) controller;
                        allMouseController.add(new MouseController(mouse));
                        System.out.println(mouse);
                    }
                }
                MouseController[] newMouseControllers = new MouseController[3];
                for (int i = 0; i < 3 && !isInterrupt; i++) {
                    cyc:
                    while (!isInterrupt) {
                        long startTime = System.currentTimeMillis();
                        System.err.println("OK + " + i + "     " + allMouseController.size());
                        for (MouseController mouseController : allMouseController) {
                            mouseController.update();
                            if (mouseController.wasLeftClick() || mouseController.wasRightClick()) {
                                newMouseControllers[i] = mouseController;
                                allMouseController.remove(mouseController);
                                break cyc;
                            }
                        }

                        long duration = System.currentTimeMillis() - startTime;
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
                if (!isInterrupt) System.arraycopy(newMouseControllers, 0, mouseControllers, 0, 3);
            }
            JDialogInitMice.this.dispatchEvent(new WindowEvent(JDialogInitMice.this, WindowEvent.WINDOW_CLOSING));
        }
    }
}
