package trash;

import net.java.games.input.Component;
import net.pskov.controller.KeyboardController;

import javax.swing.*;
import java.awt.*;
import java.util.HashSet;

public class TestFrame {
    public static void createGUI() {
        JFrame frame = new JFrame("Test frame");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(550, 300));
        frame.pack();
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);
    }

    public static void main(String[] args) {
        createGUI();
        KeyboardController keyboardController = new KeyboardController();
        new Thread(new Runnable() {
            @Override
            public void run() {
                for (; ; ) {
                    long timeMillis = System.currentTimeMillis();
                    HashSet<Component.Identifier> capture = keyboardController.capture();
//                    if (!capture.isEmpty())
//                        System.err.println(capture);
                    long end = System.currentTimeMillis();
                    if (end - timeMillis < 50) {
                        try {
                            Thread.sleep(50 - (end - timeMillis));
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }).start();
    }
}