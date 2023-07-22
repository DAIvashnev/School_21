package ex00;

public class Program {
    public static void main(String[] args) {
        User user1 = new User("Dmitry", 100.5);

        User user2 = new User("Vladislav", 3000.2);

        Transaction transaction1 = new Transaction(user1, user2, TransferCategory.DEBITS, 500.5);
        Transaction transaction2 = new Transaction(user2, user1, TransferCategory.CREDITS, -2000.0);

        System.out.println(transaction1.getAllData());
        System.out.println(transaction2.getAllData());

        System.out.println(user1.getAllData());
        System.out.println(user2.getAllData());
    }
}
