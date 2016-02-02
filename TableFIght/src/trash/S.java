package trash;

import java.awt.*;

public class S extends Frame {

    S() {
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 0.5;
        c.weighty = 1;
        c.gridx = 0;
        c.gridy = 0;
//        add(jPanel, c);
        add(new Button("A"), c);

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 0.5;
        c.weighty = 1;
        c.gridx = 1;
        c.gridy = 0;
//        add(jPanelScoreTable, c);
        add(new Button("B"), c);


        pack();
        setVisible(true);
        setSize(1200, 800);
    }

    public static void main(String[] args) {
        new S();
    }
}
