package edu.school21.game.logic;

import java.util.Vector;
import logic.ChaseLogic;

public class Enemy {
    static final int LEFT = 1;
    static final int UP = 2;
    static final int RIGHT = 3;
    static final int DOWN = 4;

    private Map map;
    private PropertiesLoader properties;
    private Player player;
    private int x;
    private int y;

    public Enemy(Map map, Enemy prevEnemy, Player player) {
        this.map = map;
        this.properties = map.getProperties();
        this.player = player;

        fillEnemyCords(prevEnemy);
    }

    private void fillEnemyCords(Enemy prevEnemy) {
        int prevEnemyX = 0, prevEnemyY = 0;
        if (prevEnemy != null) {
            prevEnemyX = prevEnemy.getX();
            prevEnemyY = prevEnemy.getY();
        }

        first:
        for (int y = 0; y < map.getSize(); y++) {
            for (int x = 0; x < map.getSize(); x++) {
                if (map.gameMap[x][y] == properties.getEnemyChar() && x!= prevEnemyX && y != prevEnemyY) {
                    this.x = x;
                    this.y = y;
                    break first;
                }
            }
        }
    }

    public String move() {
        ChaseLogic chaseLogic = new ChaseLogic(player.getX(), player.getY(), x, y);
        Vector<Integer> moveDirections = chaseLogic.getChaseDirections();

        for (int moveDirection : moveDirections) {
            if (moveDirection == LEFT && isPossibleToMove(x - 1, y)) {
                moveLeft();
                return ("LEFT");
            } else if (moveDirection == UP && isPossibleToMove(x, y - 1))  {
                moveUp();
                return ("UP");
            } else if (moveDirection == RIGHT && isPossibleToMove(x + 1, y)) {
                moveRight();
                return ("RIGHT");
            } else if (moveDirection == DOWN && isPossibleToMove(x, y + 1)) {
                moveDown();
                return ("LEFT");
            }
        }
        return "No enemy direction, smth went wrong";
    }

    private void moveLeft() {
        swapEntities(x - 1, y);
        x--;
    }

    private void moveUp() {
        swapEntities(x, y - 1);
        y--;
    }

    private void moveRight() {
        swapEntities(x + 1, y);
        x++;
    }

    private void moveDown() {
        swapEntities(x, y + 1);
        y++;
    }

    private boolean isPossibleToMove(int newX, int newY) {
        boolean result = false;
        if (newX >= 0 && newX < map.getSize() && newY >=0 && newY < map.getSize()) {
            if (map.gameMap[newX][newY] == properties.getEmptyChar() || map.gameMap[newX][newY] == properties.getPlayerChar()) {
                result = true;
            }
        }
        return result;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    private void swapEntities(int newX, int newY) {
        char temp = map.gameMap[newX][newY];
        if (temp == properties.getPlayerChar()) {
            temp = properties.getEmptyChar();
            player.playerStatus = "lose";
        }
        map.gameMap[newX][newY] = properties.getEnemyChar();
        map.gameMap[x][y] = temp;
    }
}
