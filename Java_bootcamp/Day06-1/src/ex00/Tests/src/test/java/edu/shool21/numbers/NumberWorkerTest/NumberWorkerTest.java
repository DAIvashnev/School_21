package edu.shool21.numbers.NumberWorkerTest;

import edu.school21.numbers.NumberWorker.IllegalNumberException;
import edu.school21.numbers.NumberWorker.NumberWorker;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.*;

public class NumberWorkerTest {
    NumberWorker nw = new NumberWorker();
    @ParameterizedTest
    @ValueSource(ints = {7,13,113})
    void isPrimeForPrimes(int number) {
        assertTrue(nw.isPrime(number));
    }

    @ParameterizedTest
    @ValueSource(ints = {33,52,88})
    void isPrimeForNotPrimes(int number) {
        assertFalse(nw.isPrime(number));
    }

    @ParameterizedTest
    @ValueSource(ints = {1,0,-11})
    void isPrimeForIncorrectNumbers(int number) {
        assertThrows(IllegalNumberException.class, () -> { nw.isPrime(number); });
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/data.csv")
    void digitsum(int number, int sum) {
        assertEquals(nw.digitsSum(number), sum);
    }
}
