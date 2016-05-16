package net.pskov;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class JFrameAdvertising extends JDialog {


    private JPanel panel1;
    private ArrayList<BufferedImage> avd;
    private Timer timer;
    private int posAdv = 0;
    private int intervalAdv = 0;

    JFrameAdvertising(String title, Rectangle bounds, final ArrayList<BufferedImage> avd, int intervalAdv) {
        setTitle(title);
        this.avd = avd;
        this.intervalAdv = intervalAdv;

        setContentPane(panel1);
        setUndecorated(true);
        pack();
        setBounds(bounds);
        setVisible(true);
        setResizable(false);

        timer = new Timer(Math.max(1, intervalAdv) * 1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ++posAdv;
                if (posAdv == avd.size())
                    posAdv = 0;
                repaint();
            }
        });
        timer.start();
    }

    @Override
    public void paint(Graphics g) {
        Graphics screengc = g;
        Image buffer = new BufferedImage(screengc.getClipBounds().width, screengc.getClipBounds().height, BufferedImage.TYPE_INT_RGB);
        g = buffer.getGraphics();

        g.setColor(Color.black);
        g.fillRect(0, 0, screengc.getClipBounds().width, screengc.getClipBounds().height);
        if (intervalAdv != 0) {
            BufferedImage image = avd.get(posAdv);
            double coef = Math.min((double) screengc.getClipBounds().width / image.getWidth(), (double) screengc.getClipBounds().height / image.getHeight());
            int w = (int) (coef * image.getWidth());
            int h = (int) (coef * image.getHeight());
            g.drawImage(image, (screengc.getClipBounds().width - w) / 2, (screengc.getClipBounds().height - h) / 2, w, h, null);
        }
        screengc.drawImage(buffer, 0, 0, null);
    }

    void setInterval(int interval) {
        intervalAdv = interval;
        if (0 < interval)
            timer.setDelay(interval * 1000);
//        System.err.println("interval: " + interval);
        repaint();
    }
}
