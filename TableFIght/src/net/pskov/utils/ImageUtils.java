package net.pskov.utils;

import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;

public class ImageUtils {

//    S() {
//
//
//        String imageDataString = Base64.encodeBase64URLSafeString(imageByteArray)
//        Now, we have image file as string da
//

//        String imageInBase64String = "R0lGODlhEAALANUAANPTAPZva/n5AfLySPz8iYqY3O01NgoksbGZa+kYGOskJKi05vb2XZ+r4+05O\"<tab>+\"Pv7eO3tKPv7bZak4dSvebC76tC2iPNISPX1UMkAAMm6U/NWTeYAAF5y1LqlevNaWpSh3e7uQ+1CQt\"<tab>+\"gAAKOv5Vds1C1IvpGf37a/7OnTYZ6q6NGkamd71/LyPusvLvFiTEFbx9rPb/HuaczATd7eAPAAAH2\"<tab>+\"N2vE+PMqiYuXQUsKufJqn4jlRxUlhy+CpelFnz/PxbyH5BAAAAAAALAAAAAAQAAsAAAaQwBVnSBIY\"<tab>+\"jzTaZsk5OSmEKOHxCAQ8nk1zMUo9Ir8Y42Kx2Dyi5qihi1QqkxzZZtCISBS2JNILoFQDdC0WIj4UO\"<tab>+\"hImDBMoLjcsBi0KISI8C4kFMB0uOAgykgkOGC8LJgUFFx0IqxAKCQkGGDsjpzUDLBkZEBCvCS0YJW\"<tab>+\"wfBQxjAyAgDpG/OwfOBzPRANMY1dVBADsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\"<tab>+\"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
//        BufferedImage image = null;
//        try {
//            byte[] imageInByte;
//            BASE64Decoder decoder = new BASE64Decoder();
//            imageInByte = decoder.decodeBuffer(imageInBase64String);
//            ByteArrayInputStream bis = new ByteArrayInputStream(imageInByte);
//            image = ImageIO.read(bis);
//            bis.close();
//
//        } catch (IOException e1) {
//            e1.printStackTrace();
//            return;
//        }
//        if (image == null) image = new BufferedImage(100, 100, Image.SCALE_DEFAULT);
//        JFrame frame = new JFrame();
//        frame.getContentPane().setLayout(new FlowLayout());
//        frame.getContentPane().add(new JLabel(new ImageIcon(image)));
//        frame.pack();
//        frame.setVisible(true);
//    }

    //public static void main(String[] args) {
//        new S();
//    }
//


    /**
     * Decode string to image
     *
     * @param imageString The string to decode
     * @return decoded image
     */
    public static BufferedImage decodeToImage(String imageString) {
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

//        JFrame frame = new JFrame();
//        frame.getContentPane().setLayout(new FlowLayout());
//        frame.getContentPane().add(new JLabel(new ImageIcon(image)));
//        frame.pack();
//        frame.setVisible(true);

        return image;
    }

//    /**
//     * Encode image to string
//     *
//     * @param image The image to encode
//     * @param type  jpeg, bmp, ...
//     * @return encoded string
//     */
//    public static String encodeToString(BufferedImage image, String type) {
//        String imageString = null;
//        ByteArrayOutputStream bos = new ByteArrayOutputStream();
//
//        try {
//            ImageIO.write(image, type, bos);
//            byte[] imageBytes = bos.toByteArray();
//
//            BASE64Encoder encoder = new BASE64Encoder();
//            imageString = encoder.encode(imageBytes);
//
//            bos.close();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        return imageString;
//    }

    public static void main(String args[]) throws IOException {
        /* Test image to string and string to image start */
//        BufferedImage img = ImageIO.read(new File("C:\\code\\xelarogi\\TableFIght\\resources\\images\\Canada.png"));
        BufferedImage newImg;
//        String imgstr;
//        imgstr = encodeToString(img, "png");
//
//        System.out.println(imgstr);

//        newImg = decodeToImage(imgstr);
        //newImg = decodeToImage("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");
        newImg = decodeToImage("iVBORw0KGgoAAAANSUhEUgAAAAkAAAAGCAYAAAARx7TFAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAJElEQVQImWP8////fwYCgImQAgYGBgZGBstlVDLpqrYcdUwCABTqCAE9u0b5AAAAAElFTkSuQmCC");
        newImg = decodeToImage("iVBORw0KGgoAAAANSUhEUgAAAAkAAAAGCAYAAAARx7TFAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAJElEQVQImWP8////fwYCgImQAgYGBgZGBstlVDLpqrYcdUwCABTqCAE9u0b5AAAAAElFTkSuQmCC");
        ImageIO.write(newImg, "png", new File("C:\\code\\xelarogi\\TableFIght\\resources\\images\\CopyOfTestImage.png"));

        JFrame frame = new JFrame();
        frame.getContentPane().setLayout(new FlowLayout());
        frame.getContentPane().add(new JLabel(new ImageIcon(newImg)));
        frame.pack();
        frame.setVisible(true);


    }
}
