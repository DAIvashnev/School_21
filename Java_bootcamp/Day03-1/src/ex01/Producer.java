public class Producer implements Runnable {
    private int count;
    private final Store store;

    public Producer(Store store, int count) {
        this.count = count;
        this.store = store;
    }

    public void run() {
        for(int i = 0; i < count; i++) {
            try {
                store.getHen();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
