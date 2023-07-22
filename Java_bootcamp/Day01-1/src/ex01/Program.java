package ex01;

public class Program {
    public static void main(String[] args) {
        User user1 = new User("Dmitry", 100.5);
        User user2 = new User("Vladislav", 3000.2);

        System.out.println(user1.getAllData());
        System.out.println(user2.getAllData());
    }
}
