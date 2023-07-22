import static java.lang.System.exit;

public class Program  {
    static int count = 0;

    public static void main(String[] args) throws InterruptedException {
        if (args.length == 1) {
            String[] strArgs = args[0].split("=");
            if (strArgs[0].equals("--count")) {
                count = Integer.parseInt(strArgs[1]);
            }
            MyThread egg = new MyThread("Egg", count);
            MyThread hen = new MyThread("Hen", count);

            egg.start();
            hen.start();

            egg.join();
            hen.join();

            for (int i = 0; i < count; i++) {
                System.out.println("Human");
            }
        } else {
            System.err.println("Many arguments");
            exit(-1);
        }
    }

}
