package edu.school21.numbers.NumberWorker;

public class IllegalNumberException extends RuntimeException {
    IllegalNumberException(String error) {
        super(error);
    }
}
