package net.pskov;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

public class JDialogAdv extends JDialog {
    private JPanel panel;
    private JCheckBox showAdvertisementCheckBox;
    private JSpinner spinner;
    private JButton OKButton;
    private boolean pressedOK;

    JDialogAdv(Frame owner, int interaval) {
        super(owner, "", true);
        pressedOK = false;

        showAdvertisementCheckBox.setSelected(interaval != 0);
        showAdvertisementCheckBox.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                spinner.setEnabled(showAdvertisementCheckBox.isSelected());
            }
        });
        spinner.setModel(new SpinnerNumberModel(interaval == 0 ? 15 : interaval, 1, 100500, 1));
        spinner.setEnabled(showAdvertisementCheckBox.isSelected());

        OKButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                pressedOK = true;
                JDialogAdv.this.setVisible(false);
            }
        });

        setContentPane(panel);
        pack();
        setLocationRelativeTo(owner);
        setResizable(false);
    }

    int getInterval() {
        if (showAdvertisementCheckBox.isSelected())
            return (int) spinner.getValue();
        return 0;
    }

    boolean execCode() {
        return pressedOK;
    }
}
