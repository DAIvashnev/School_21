package edu.school21.printer.app;

import edu.school21.printer.logic.ImageParser;
import edu.school21.printer.logic.PrintImage;
import java.io.File;
import java.io.IOException;

public class Program {
    public static void main(String[] args) throws IOException {
        if(args.length != 3) {
            System.err.println("Error count arguments\nwrite: . 0 path");
            System.exit(-1);
        }

        String pathImage = args[2];
        File file = null;

        try {
            file = new File(pathImage);
        } catch (Exception e) {
            e.printStackTrace();
        }

        ImageParser ip = new ImageParser(file);
        int[][] arrays = ip.getArr(args[0].charAt(0), args[1].charAt(0));

        PrintImage pi = new PrintImage();
        pi.outputImage(arrays);

    }
}
