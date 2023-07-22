public class Program {
    public static int count = 0;

    public static void main(String[] args) throws InterruptedException {
        if (args.length == 1) {
            String[] strArgs = args[0].split("=");
            if (strArgs[0].equals("--count")) {
                count = Integer.parseInt(strArgs[1]);
            }
            Store store = new Store();
            store.addFirstEgg();

            Thread egg = new Thread(new Customer(store, count));
            Thread hen = new Thread(new Producer(store, count));

            egg.start();
            hen.start();

            egg.join();
            hen.join();

        } else System.out.println("Error counts arguments");
    }
}
