package edu.school21.numbers;

public class NumberWorker {

    public boolean isPrime(int number) throws IllegalNumberException{
        boolean result = true;
        if( number <= 1)
            throw new IllegalNumberException("Incorrect number");

        for (int i = 2; i * i <= number; i++) {
            if (number % i == 0) {
                result = false;
                break;
            }
        }
        return result;
    }

    public int digitsSum(int number) {
        int result = 0;
        while (number != 0) {
            result += number % 10;
            number /= 10;
        }
        return result;
    }

}
