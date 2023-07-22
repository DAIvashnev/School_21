package ex01;

public class User {
    private int id;
    private String name;
    private double balance;

    public User(String name, double balance) {
        this.id = UserIdsGenerator.getInstance().generateId();
        this.name = name;
        if (balance < 0) {
            this.balance = 0;
        } else {
            this.balance = balance;
        }
    }

    public void setBalance(double balance) {
        if (balance >= 0.) {
            this.balance = balance;
        } else this.balance = 0.;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public double getBalance() {
        return balance;
    }

    public String getAllData() {
        return "User: id - " + id + ", name - " + name + ", balance = " + balance + "\n";
    }
}


