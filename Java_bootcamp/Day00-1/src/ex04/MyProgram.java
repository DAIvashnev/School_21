package ex04;

import java.util.Arrays;
import java.util.Scanner;
import java.lang.String;

public class MyProgram {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String str = in.nextLine();
        char[] charArr = str.toCharArray();
        int[] numArr = new int[65535];

        for (int i = 0; i < charArr.length; i++) {
            numArr[(int) charArr[i]]++;
        }
        int count = 0;
        for (int i = 0; i < numArr.length; i++) {
            if (numArr[i] > 0) count++;
        }
        int[][] arrays = new int[count][2];
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < numArr.length; j++) {
                if(numArr[j] > 0) {
                    arrays[i][0] = j;
                    arrays[i][1] = numArr[j];
                    i++;
                }
            }
        }
        /*for (int[] i : arrays) {
            System.out.println(Arrays.toString(i));
        }*/
        System.out.println();
        for(int i = 1; i < arrays.length; i++) {
            for(int j = 0; j < arrays[i].length; j++) {
                for(int k = 1; k < arrays.length; k++) {
                    if (arrays[k][1] > arrays[k - 1][1]) {
                        int[][] tmp = new int[1][2];
                        tmp[0][0] = arrays[k][0];
                        tmp[0][1] = arrays[k][1];
                        arrays[k][0] = arrays[k - 1][0];
                        arrays[k][1] = arrays[k - 1][1];
                        arrays[k - 1][0] = tmp[0][0];
                        arrays[k - 1][1] = tmp[0][1];
                    }
                }
            }
        }
        for (int[] i : arrays) {
            System.out.println(Arrays.toString(i));
        }

        int[] reshotka = new int[10];
        for(int i = 0; i < arrays.length && i < 10; i++) {
            int tmp = arrays[i][1];
            int cc = 0;
            while(cc <= tmp && tmp >= 4) {
                cc+=4;
                reshotka[i] += 1;
            }
        }
        System.out.println(Arrays.toString(reshotka));
        System.out.println();
        System.out.println(arrays[0][1]);
        for(int i = 1; i < arrays.length && i < 10; i++) {
            System.out.print("# ");
            for (int j = 1; j < i; j++) {
                System.out.print("# ");
            }
            System.out.print(arrays[i][1]);
            System.out.println();
        }
        //System.out.println(count);
        /*for (int[] i : arrays) {
            System.out.println(Arrays.toString(i));
            AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAASSSSSSSSSSSSSSSSSSSSSSSSDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDWEWWKFKKDKKDSKAKLSLDKSKALLLLLLLLLLRTRTETWTWWWWWWWWWWOOOOOOO42

        }*/
    }
}
