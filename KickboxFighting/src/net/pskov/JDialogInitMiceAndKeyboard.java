package net.pskov;

import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;
import net.java.games.input.Mouse;
import net.pskov.controller.KeyboardController;
import net.pskov.controller.MouseController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Vector;

public class JDialogInitMiceAndKeyboard extends JDialog {
    private JPanel contentPane;
    private JButton buttonCancel;
    private JLabel label0;
    private JLabel label1;
    private JLabel label2;

    private Timer timer;
    private boolean initMice;
    private ArrayList<MouseController> mouseControllers, allMouseController;
    private KeyboardController keyboardController;

    public JDialogInitMiceAndKeyboard() {
        super((Window)null);
        keyboardController = new KeyboardController();


        mouseControllers = new ArrayList<>();
        allMouseController = new ArrayList<>();
        for (Controller controller : ControllerEnvironment.getDefaultEnvironment().getControllers()) {
            if (controller.getType() == Controller.Type.MOUSE) {
                Mouse mouse = (Mouse) controller;
                allMouseController.add(new MouseController(mouse));
                System.out.println(mouse);
            }
        }

        if (allMouseController.size() < 3){
            JOptionPane.showMessageDialog(null,
                    "You have only " + allMouseController.size() + " mice.\n" +
                    "Connect a mouse (mice) and restart a program.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE);
            System.exit(0);
        }

        timer = new Timer(50, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                for (MouseController mouseController : allMouseController) {
                    mouseController.update();
                    if (mouseController.wasLeftClick() || mouseController.wasRightClick()) {
                        mouseControllers.add(mouseController);
                        allMouseController.remove(mouseController);

                        int size = mouseControllers.size();
                        System.err.println("OK + " + size);
                        if (size == 1) label0.setForeground(Color.green);
                        else if (size == 2) label1.setForeground(Color.green);
                        else if (size == 3) label2.setForeground(Color.green);
                        break;
                    }
                }

                if (mouseControllers.size() == 3) {
                    initMice = true;
                    timer.stop();
                    setVisible(false);
                    dispose();
                }
            }
        });
        timer.start();


        setTitle("Mice init");
        setContentPane(contentPane);
        setModal(true);
        setResizable(true);


        buttonCancel.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

        // call onCancel() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                onCancel();
            }
        });

        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    }

    private void onCancel() {
        timer.stop();
        dispose();
    }

    public boolean isInitMice() {
        return initMice;
    }

    public MouseController[] getMouseControllers() {
        return mouseControllers.toArray(new MouseController[3]);
    }

    public KeyboardController getKeyboardController() {
        return keyboardController;
    }

    public static void main(String[] args) {
        JDialogInitMiceAndKeyboard dialog = new JDialogInitMiceAndKeyboard();
        dialog.pack();
        dialog.setLocationRelativeTo(null);
        dialog.setVisible(true);
        System.exit(0);
    }
}
