package net.pskov;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import net.pskov.some_enum.PointPanelMode;
import net.pskov.utils.ImageUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;
import java.util.ArrayList;

public class JDialogAddPair extends JDialog {
    private JPanel contentPane;
    private JButton buttonOK;
    private JButton buttonCancel;
    private JTextField textFieldNameLeft;
    private JTextField textFieldCountyLeft;
    private JTextField textFieldNameRight;
    private JTextField textFieldCountryRight;
    private JSpinner spinnerRound;
    private JSpinner spinnerFight;
    private JSpinner spinnerBreak;
    private JComboBox comboBoxTie;
    private JSpinner spinnerExtraRound;
    private JComboBox comboBoxMode;

    public JDialogAddPair() {
        createUIComponents();
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

        // call onCancel() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                onCancel();
            }
        });

        // call onCancel() on ESCAPE
        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    }

    private void onOK() {
        JsonObject object = new JsonObject();
        object.addProperty("nameOfLeftFighter", textFieldNameLeft.getText());
        object.addProperty("nameOfRightFighter", textFieldNameRight.getText());
        object.addProperty("fightId", -1);
        object.addProperty("categoryOfFightingShort", 0);
        object.addProperty("categoryOfFighting", "");

        object.addProperty("countOfRounds", (int) spinnerRound.getValue());
        object.addProperty("durationOfRound", (int) spinnerFight.getValue());
        object.addProperty("durationOfBreak", (int) spinnerBreak.getValue());
        object.addProperty("DURATION_EXTRA_ROUND", (int) spinnerExtraRound.getValue());
        object.addProperty("IN_CASE_TIE", comboBoxTie.getSelectedIndex());

        object.addProperty("leftFlag", "");
        object.addProperty("rightFlag", "");

        object.addProperty("regionOfLeftFighter", textFieldCountyLeft.getText());
        object.addProperty("regionOfRightFighter", textFieldCountryRight.getText());

        object.addProperty("TOURNAMENT_CATEGORIES_FK", System.currentTimeMillis() % (int) 1e9);
        object.addProperty("VERTEX", System.currentTimeMillis() % (int) 1e9);

        object.addProperty("POINT_PANEL_MODE", comboBoxMode.getSelectedIndex());

        object.addProperty("orderUID_left", System.currentTimeMillis() % (int) 1e9);
        object.addProperty("orderUID_right", System.currentTimeMillis() % (int) 1e9);


        try {
            String JSON_DATA = "[]";
            try {
                JSON_DATA = new String(Files.readAllBytes(Paths.get(JFrameMainJudge.pathSaveJson)), StandardCharsets.UTF_8);
            } catch (NoSuchFileException e) {
                //e.printStackTrace();
            }

            JsonArray jsonArray = new JsonParser().parse(JSON_DATA).getAsJsonArray();
            jsonArray.add(object);

            ArrayList<String> arr = new ArrayList<>();
            arr.add(new Gson().toJson(jsonArray));

            Files.write(Paths.get(JFrameMainJudge.pathSaveJson), arr, StandardCharsets.UTF_8);

        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        dispose();
    }

    private void onCancel() {
        // add your code here if necessary
        dispose();
    }

    public static void main(String[] args) {
        JDialogAddPair dialog = new JDialogAddPair();
        dialog.pack();
        dialog.setVisible(true);
        System.exit(0);
    }

    private void createUIComponents() {
        spinnerRound.setValue(3);
        spinnerFight.setValue(120);
        spinnerBreak.setValue(60);
        spinnerExtraRound.setValue(60);
    }
}
