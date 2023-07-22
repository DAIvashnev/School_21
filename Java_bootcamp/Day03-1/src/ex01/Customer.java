public class Customer implements Runnable {
    private int count;
    private final Store store;

    public Customer(Store store, int count) {
        this.count = count;
        this.store = store;
    }

    @Override
    public void run() {
        for(int i = 0; i < count; i++) {
            try {
                store.getEgg();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
