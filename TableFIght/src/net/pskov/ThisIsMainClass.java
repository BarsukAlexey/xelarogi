package net.pskov;

import javax.swing.*;

public class ThisIsMainClass {

    public static void main(String[] args) {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    try {
                        UIManager.setLookAndFeel(info.getClassName());
                    } catch (ClassNotFoundException e) {
                        e.printStackTrace();
                    } catch (InstantiationException e) {
                        e.printStackTrace();
                    } catch (IllegalAccessException e) {
                        e.printStackTrace();
                    } catch (UnsupportedLookAndFeelException e) {
                        e.printStackTrace();
                    }
                    break;
                }
            }

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new JFrameMainJudge();
            }
        });
    }
}

