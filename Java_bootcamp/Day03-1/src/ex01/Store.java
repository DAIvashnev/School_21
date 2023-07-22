public class Store {
    private String egg;
    private String hen;

    public void getEgg() throws InterruptedException {
        synchronized (this) {
            while(egg == null) wait();
            System.out.println(egg);
            egg = null;
            hen = "Hen";
            notify();
        }
    }
    public void getHen() throws InterruptedException {
        synchronized (this) {
            while(hen == null) wait();
            System.out.println(hen);
            hen = null;
            egg = "Egg";
            notify();
        }
    }

    public void addFirstEgg() {
        egg = "Egg";
    }
}
