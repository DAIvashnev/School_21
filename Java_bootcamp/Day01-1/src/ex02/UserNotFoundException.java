package ex02;

public class UserNotFoundException extends RuntimeException {
    UserNotFoundException(String error) {
        super(error);
    }
}
