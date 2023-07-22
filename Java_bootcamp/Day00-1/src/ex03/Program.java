
import java.util.Scanner;

public class Program {
    static long value = 0;
    static long numGraph = 0;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String week = "";
        int numWeek = 0;

        for (int i = 1; i <= 18; i++) {
            week = in.next();
            if (week.equals("42")) break;
            if (!week.equals("Week") || (numWeek = in.nextInt()) != i) {
                System.err.println("IllegalArgument");
                System.exit(-1);
            }
            value = value * 10 + min(in);
        }

        while (value != 0) {
            numGraph = numGraph * 10 + getMinNum();
        }
        printGraph();
        in.close();
    }

    static int min(Scanner in) {
        int min = 9;
        int tmp;
        for (int i = 0; i < 5; i++) {
            tmp = in.nextInt();
            if (min > tmp) min = tmp;
        }
        return min;
    }

    static long getMinNum() {
        long res = 0;
        res = value % 10;
        value /= 10;
        return res;
    }

    static void printGraph() {
        for (int i = 1; numGraph != 0; i++) {
            System.out.print("Week " + i + " ");
            int equals = (int) numGraph % 10;
            while (equals != 0) {
                System.out.print("=");
                equals--;
            }
            System.out.println(">");
            numGraph /= 10;
        }
    }
}
