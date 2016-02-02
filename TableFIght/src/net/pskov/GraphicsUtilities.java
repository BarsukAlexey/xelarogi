package net.pskov;

import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;

public class GraphicsUtilities {

    /**
     * Calculates the largest size of the given font for which the given text
     * will fit into the given size.
     */
    public static int getMaxFittingFontSize(Graphics2D g, Font font, String text, double width, double height) {
        int minSize = 1;
        int maxSize = 288;
        while (minSize < maxSize) {
            int curSize = (maxSize + minSize + 1) / 2;
            FontMetrics fm = g.getFontMetrics(new Font(font.getName(), font.getStyle(), curSize));
            Rectangle2D stringBounds = fm.getStringBounds(text, g);
            if (stringBounds.getWidth() > width || stringBounds.getHeight() > height) {
                maxSize = curSize - 1;
            } else {
                minSize = curSize;
            }
        }
        return maxSize;
    }

    public static void fitAndDrawTextInCenterOfRectangle(Graphics2D g, Color color, String text, double x, double y, double width, double height) {
//        int maxFittingFontSize = GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), text, width, height);
        int maxFittingFontSize = GraphicsUtilities.getMaxFittingFontSize(g, g.getFont(), text, 0.95 * width, 0.95 * height);
        drawTextInCenterOfRectangle(g, color, text, x, y, width, height, maxFittingFontSize);
    }


    public static void drawTextInCenterOfRectangle(Graphics2D g, Color color, String text, double x, double y, double width, double height, int maxFittingFontSize) {
        Font font = g.getFont();
        g.setFont(new Font(font.getName(), font.getStyle(), maxFittingFontSize));
        g.setColor(color);

        FontMetrics fm = g.getFontMetrics();
        Rectangle2D r = fm.getStringBounds(text, g);
        double XX = (width - r.getWidth()) / 2.0;
        double YY = (height - r.getHeight()) / 2.0 + fm.getAscent();
        g.drawString(text, (float) (x + XX), (float) (y + YY));
    }

    public static void drawTextInTheLeftOfRectangle(Graphics2D g, Color color, String text, int x, int y, int height, int maxFittingFontSize) {
        Font font = g.getFont();
        g.setFont(new Font(font.getName(), font.getStyle(), maxFittingFontSize));
        g.setColor(color);

        FontMetrics fm = g.getFontMetrics();
        Rectangle2D r = fm.getStringBounds(text, g);
        int YY = (int) ((height - r.getHeight()) / 2.0 + fm.getAscent());
        g.drawString(text, x, y + YY);
    }

    public static void drawTextInTheRightOfRectangle(Graphics2D g, Color color, String text, double x, double y, double width, double height, int maxFittingFontSize) {
        Font font = g.getFont();
        g.setFont(new Font(font.getName(), font.getStyle(), maxFittingFontSize));
        g.setColor(color);

        FontMetrics fm = g.getFontMetrics();
        Rectangle2D r = fm.getStringBounds(text, g);
        double XX = width - r.getWidth();
        double YY = (height - r.getHeight()) / 2.0 + fm.getAscent();
        g.drawString(text, (float) (x + XX), (float) (y + YY));
    }

    public static Dimension getScaledDimension(double imageSizeWidth, double imageSizeHeight, double boundaryWidth, double boundaryHeight) {
        boundaryWidth = 0.95 * boundaryWidth;
        boundaryHeight = 0.95 * boundaryHeight;

        double widthRatio = boundaryWidth / imageSizeWidth;
        double heightRatio = boundaryHeight / imageSizeHeight;
        double ratio = Math.min(widthRatio, heightRatio);

        return new Dimension((int) (imageSizeWidth * ratio), (int) (imageSizeHeight * ratio));
    }

    public static Color getGrayColor(Color color) {
        BufferedImage image = new BufferedImage(1, 1, BufferedImage.TYPE_BYTE_GRAY);
        Graphics g = image.getGraphics();
        g.setColor(color);
        g.fillRect(0, 0, 1, 1);
        g.dispose();
        return new Color(image.getRGB(0, 0));
    }


    public static BufferedImage getGrayImage(BufferedImage colorImage) {
        BufferedImage image = new BufferedImage(colorImage.getWidth(), colorImage.getHeight(), BufferedImage.TYPE_BYTE_GRAY);
        Graphics g = image.getGraphics();
        g.drawImage(colorImage, 0, 0, null);
        g.dispose();
        return image;
    }
}


