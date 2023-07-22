package ex02;

public class UserIdsGenerator {
    private int id = 0;
    private static UserIdsGenerator INSTANCE;

    private UserIdsGenerator() {
    }

    public static UserIdsGenerator getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new UserIdsGenerator();
        }
        return INSTANCE;
    }

    public int generateId() {
        return id++;
    }
}
