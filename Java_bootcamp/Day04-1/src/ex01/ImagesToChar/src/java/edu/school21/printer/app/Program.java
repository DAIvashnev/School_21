package edu.school21.printer.app;

import edu.school21.printer.logic.ImageParser;
import edu.school21.printer.logic.PrintImage;
import java.io.IOException;

public class Program {
    public static void main(String[] args) throws IOException {
        if(args.length != 2) {
            System.err.println("Error count arguments\nwrite: . 0");
            System.exit(-1);
        }

        ImageParser ip = new ImageParser();
        int[][] arrays = ip.getArr(args[0].charAt(0), args[1].charAt(0));

        PrintImage pi = new PrintImage();
        pi.outputImage(arrays);

    }
}