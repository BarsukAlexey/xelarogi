package net.pskov;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import net.pskov.some_enum.Player;
import net.pskov.utils.ReportUtis;

import javax.swing.*;
import java.awt.*;

public class ThisIsMainClass {

    public static void main(String[] args) {
        /*/
        {
            Fighting fighting = new Fighting("nameL", "nameR", 3, "category",
                    3,
                    3 * 1000,
                    3 * 1000,
                    30 * 1000, 2,
                    null, null, "cL", "cR", -1, -1);

            JDialog dlg = new JDialog();
            dlg.setModal(true);

            JScrollPane jsp;
            JTextPane jta;

            jta = new JTextPane();
            jta.setEditable(false);
            jta.setContentType("text/html");
            jta.setText(ReportUtis.getOpeningSystem(fighting));

            jsp = new JScrollPane(jta);
            jsp.setPreferredSize(new Dimension(800, 600));

            dlg.setLayout(new BorderLayout());
            dlg.add(jsp, BorderLayout.CENTER);
            dlg.pack();
            dlg.setLocationRelativeTo(null);
            dlg.setVisible(true);
        }
        System.exit(0);
        /*/

        //
//        for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
//            if ("Nimbus".equals(info.getName())) {
//                try {
//                    UIManager.setLookAndFeel(info.getClassName());
//                } catch (ClassNotFoundException | InstantiationException | UnsupportedLookAndFeelException | IllegalAccessException e) {
//                    e.printStackTrace();
//                }
//                break;
//            }
//        }

        final JDialogInitMiceAndKeyboard dlg = new JDialogInitMiceAndKeyboard();
        dlg.pack();
        dlg.setBounds(GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds());
        dlg.setVisible(true);
        if (!dlg.isInitMice())
            System.exit(0);

//        final ArrayList<MouseController> allMouseController = new ArrayList<>();
//        for (Controller controller : ControllerEnvironment.getDefaultEnvironment().getControllers()) {
//            if (controller.getType() == Controller.Type.MOUSE) {
//                Mouse mouse = (Mouse) controller;
//                allMouseController.add(new MouseController(mouse));
//                System.out.println(mouse);
//            }
//        }

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
//                new JFrameMainJudge(allMouseController.toArray(new MouseController[3]), dlg.getKeyboardController());
                new JFrameMainJudge(dlg.getMouseControllers(), dlg.getKeyboardController());
            }
        });

        /**/
    }
}

