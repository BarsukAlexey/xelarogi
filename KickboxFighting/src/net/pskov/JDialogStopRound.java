package net.pskov;

import net.pskov.some_enum.Player;

import javax.swing.*;
import java.awt.event.*;

public class JDialogStopRound extends JDialog {
    private JPanel contentPane;
    private JButton buttonOK;
    private JButton buttonCancel;
    private JRadioButton redConnerRadioButton;
    private JRadioButton blueConnerRadioButton;
    private JTextField textField1;
    private boolean accept;

    public JDialogStopRound(JDialog owner) {
        super(owner, true);

        setTitle("Stop round");
        accept = true;

        ButtonGroup group = new ButtonGroup();
        group.add(redConnerRadioButton);
        group.add(blueConnerRadioButton);

        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonOK);

        buttonOK.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onOK();
            }
        });

        buttonCancel.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

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

        setResizable(false);
        pack();
        setLocationRelativeTo(owner);
    }

    private void onOK() {
        accept = true;
        dispose();
    }

    private void onCancel() {
        accept = false;
        dispose();
    }

    public Player getWinner(){
        if (!accept)
            return Player.NoPlayer;
        if (redConnerRadioButton.isSelected())
            return Player.Left;
        if (blueConnerRadioButton.isSelected())
            return Player.Right;
        throw new RuntimeException();
    }

    public String getResult(){
        return textField1.getText();
    }

    public static void main(String[] args) {
        JDialogStopRound dialog = new JDialogStopRound(null);
        dialog.pack();
        dialog.setVisible(true);
        System.exit(0);
    }
}
