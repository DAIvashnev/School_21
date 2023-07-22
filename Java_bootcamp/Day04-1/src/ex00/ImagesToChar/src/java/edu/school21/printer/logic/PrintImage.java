package edu.school21.printer.logic;

public class PrintImage {
    public void outputImage(int[][] charArrays) {

        for(int i = 0; i < charArrays.length; i++) {
            for(int j = 0; j < charArrays[i].length; j++) {
                System.out.print((char)charArrays[i][j]);
            }
            System.out.println();
        }
    }
}
