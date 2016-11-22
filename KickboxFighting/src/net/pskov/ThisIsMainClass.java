package net.pskov;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;
import net.java.games.input.Mouse;
import net.pskov.controller.MouseController;
import net.pskov.some_enum.Player;
import net.pskov.utils.ReportUtis;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class ThisIsMainClass {

    public static void main(String[] args) {
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
        /*/
        dlg.pack();
        dlg.setBounds(GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds());
        dlg.setVisible(true);
        if (!dlg.isInitMice())
            System.exit(0);
        /**/

        final ArrayList<MouseController> allMouseController = new ArrayList<>();
        for (Controller controller : ControllerEnvironment.getDefaultEnvironment().getControllers()) {
            if (controller.getType() == Controller.Type.MOUSE) {
                Mouse mouse = (Mouse) controller;
                allMouseController.add(new MouseController(mouse));
                System.out.println(mouse);
            }
        }

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new JFrameMainJudge(allMouseController.toArray(new MouseController[3]), dlg.getKeyboardController());
//                new JFrameMainJudge(dlg.getMouseControllers(), dlg.getKeyboardController());
            }
        });



        /**/
    }
}

