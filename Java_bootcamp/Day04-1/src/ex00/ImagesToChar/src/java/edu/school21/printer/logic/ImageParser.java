package edu.school21.printer.logic;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class ImageParser {
    BufferedImage image;

    public ImageParser(File file) throws IOException {
        image = ImageIO.read(file);
    }

    public int[][] getArr(char b, char w) {
        int[][] arrays = new int[image.getHeight()][image.getWidth()];
        for (int i = 0; i < arrays.length; i++) {
            for (int j = 0; j < arrays[i].length; j++) {
                int collor = image.getRGB(j, i);
                if(collor == Color.BLACK.getRGB()) {
                    arrays[i][j] = w;
                } else arrays[i][j] = b;
            }
        }
        return arrays;
    }
}
