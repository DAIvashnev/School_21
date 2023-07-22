package ex02;

public interface UserList {
    boolean addUser(User user);

    User getUserById(int id) throws UserNotFoundException;

    User getUserByIndex(int index);

    int getAllCountUsers();
}
