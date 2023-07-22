package ex02;

public class Program {
    public static void main(String[] args) {
        UserArrayList dataUser = new UserArrayList();

        User user0 = new User("Dima", 10);
        User user1 = new User("Vlad", 20);
        User user2 = new User("Katya", 30);
        User user3 = new User("Dima", 10);
        User user4 = new User("Vlad", 20);
        User user5 = new User("Katya", 30);
        User user6 = new User("Dima", 10);
        User user7 = new User("Vlad", 20);
        User user8 = new User("Katya", 30);
        User user9 = new User("Dima", 10);
        User user10 = new User("Vlad", 20);
        User user11 = new User("Katya", 30);

        dataUser.addUser(user0);
        dataUser.addUser(user1);
        dataUser.addUser(user2);
        dataUser.addUser(user3);
        dataUser.addUser(user4);
        dataUser.addUser(user5);
        dataUser.addUser(user6);
        dataUser.addUser(user7);
        dataUser.addUser(user8);

        System.out.println(dataUser.getAllCountUsers());

        System.out.println(dataUser.getUserByIndex(1).getName());
        System.out.println(dataUser.getUserById(3).getName());
        dataUser.addUser(user9);
        dataUser.addUser(user10);
        dataUser.addUser(user11);
        System.out.println(dataUser.getAllCountUsers());
        System.out.println(dataUser.getUserByIndex(11).getName());
        System.out.println(dataUser.getUserById(19).getName());
    }
}
