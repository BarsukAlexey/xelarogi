package net.pskov.utils;

import sun.misc.BASE64Decoder;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;

public class ImageUtils {

    public static BufferedImage decodeToImage(String imageString, Color defaultColor) {
        BufferedImage image = null;
        byte[] imageByte;
        try {
            BASE64Decoder decoder = new BASE64Decoder();
            imageByte = decoder.decodeBuffer(imageString);
            ByteArrayInputStream bis = new ByteArrayInputStream(imageByte);
            image = ImageIO.read(bis);
            bis.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (image == null) {
            image = new BufferedImage(1, 1, BufferedImage.TYPE_INT_BGR);
            Graphics2D graphics = image.createGraphics();
            graphics.setColor(defaultColor);
            graphics.fillRect(0, 0, 1, 1);
        }
        return image;
    }

}
