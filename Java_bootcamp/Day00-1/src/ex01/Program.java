

import java.util.Scanner;

public class Program {
    public static void main(String[] args) {
        int resultIt = 1;
        int value = 0;
        final String IA = "IllegalArgument";
        Scanner in = new Scanner(System.in);
        boolean res = true;
        if (in.hasNextInt()) {
            value = in.nextInt();
        } else {
            System.err.println(IA);
            System.exit(-1);
        }
        if (value <= 1) {
            System.err.println(IA);
            System.exit(-1);
        } else {
            for (int i = 2; i * i <= value; i++) {
                if (value % i == 0) {
                    res = false;
                    break;
                }
                resultIt++;
            }
        }
        System.out.println(res + " " + resultIt);
        in.close();
    }
}
