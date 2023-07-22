package edu.school21.numbers;

public class IllegalNumberException extends RuntimeException {
    IllegalNumberException(String error) {
        super(error);
    }
}
