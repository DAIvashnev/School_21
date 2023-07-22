package edu.school21.game.logic;

import edu.school21.game.exceptions.IllegalParametersException;

import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;
import java.util.stream.Collectors;

import static java.lang.System.exit;

public class Game {
    private static final int[] allowedInputs = {1, 2, 3, 4, 9};
    private static boolean isDev;
    private Map map;
    private PropertiesLoader properties;
    private int enemiesCount;

    public Game(boolean isDev, String profile, int enemiesCount, int wallsCount, int size) {
        Game.isDev = isDev;
        properties = new PropertiesLoader();
        properties.loadProperties(profile);
        this.enemiesCount = enemiesCount;

        map = Map.getInstance();
        map.setProperties(properties);
        map.initMap(enemiesCount, wallsCount, size);
        map.generateMap();

        if (!map.isCorrect()) throw new IllegalParametersException("Incorrect arguments");
    }

    public void startGame() {
        clearScreen();
        Scanner scanner = new Scanner(System.in);
        Player player = new Player(map);
        Vector<Enemy> enemyVector = new Vector<>();

        addAllEnemies(enemyVector, player);

        printGuide();
        map.printMap();
        while (scanner.hasNextInt()) {
            int input = scanner.nextInt();
            boolean isAllowed = Arrays.stream(allowedInputs)
                    .boxed()
                    .collect(Collectors.toSet())
                    .contains(input);
            if (!isAllowed) {
                System.out.println("Wrong int command, try again");
                continue;
            }

            player.move(input);
            clearScreen();
            printGuide();
            map.printMap();

            for (Enemy enemy : enemyVector) {
                String enemyDirection = enemy.move();
                if (isDev) {
                    System.out.println("Enemy move: " + enemyDirection);
                    System.out.println("Confirm the step by entering '8'");
                    if (scanner.hasNextInt() && scanner.nextInt() == 8) {
                        clearScreen();
                        map.printMap();
                    } else {
                        System.out.println("Program error detected, exit");
                        exit(2);
                    }
                } else {
                    clearScreen();
                    map.printMap();
                }
            }

            if (!player.playerStatus.equals("playing") || input == 9) break;
        }

        gameOverMessage(player.playerStatus);
    }

    public static void printGuide() {
        System.out.println("Movement: 1 - Left, 2 - UP, 3 - Right, 4 - Down, " +
                "9 - Give Up");
    }

    private void addAllEnemies(Vector<Enemy> enemyVector, Player target) {
        Enemy enemy = new Enemy(map, null, target);
        enemyVector.add(enemy);
        for (int i = 1; i < enemiesCount; i++) {
            enemyVector.add(new Enemy(map, enemyVector.elementAt(i-1), target));
        }
    }

    private void gameOverMessage(String playerStatus) {
        if (playerStatus.equals("win")) {
            System.out.println("You win");
        } else {
            System.out.println("You lost");
        }
    }

    private void clearScreen() {
        if (isDev) {
            System.out.println();
        } else {
            System.out.print("\033[H\033[J");
        }
    }
}
