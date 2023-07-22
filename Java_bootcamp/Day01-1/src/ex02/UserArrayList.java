package ex02;

public class UserArrayList implements UserList {
    private User[] dataUsers = new User[10];
    private int i = 0;

    public boolean addUser(User user) {
        dataUsers[i] = user;
        i++;
        if (i == dataUsers.length) {
            User[] upDataUsers = new User[dataUsers.length * 2];
            for (int i = 0; i < dataUsers.length; i++) {
                upDataUsers[i] = dataUsers[i];
            }
            dataUsers = upDataUsers;
        }
        return true;
    }

    public User getUserById(int id) {
        for (int i = 0; i < dataUsers.length; i++) {
            if (dataUsers[i].getId() == id) return dataUsers[i];
        }
        throw new UserNotFoundException("User not found");
    }

    public User getUserByIndex(int index) {
        return dataUsers[index];
    }

    public int getAllCountUsers() {
        return i;
    }

}
