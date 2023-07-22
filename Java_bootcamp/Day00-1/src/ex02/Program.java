
import java.util.Scanner;

public class Program {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        final String COCR = "Count of coffee-request – ";
        int count = 0;
        int setNum = 0;
        while ((setNum = in.nextInt()) != 42) {
            if (simple(getDigit((setNum)))) count++;
        }
        System.out.println(COCR + count);
        in.close();
    }

    static int getDigit(int num) {
        int result = 0;
        while (num != 0) {
            result += num % 10;
            num /= 10;
        }
        return result;
    }

    static boolean simple(int digit) {
        boolean result = true;
        for (int i = 2; i * i < digit; i++) {
            if (digit % i == 0) {
                result = false;
                break;
            }
        }
        return result;
    }
}
