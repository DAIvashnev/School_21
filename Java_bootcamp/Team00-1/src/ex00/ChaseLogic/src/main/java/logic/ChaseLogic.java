package logic;

import java.util.Vector;

public class ChaseLogic {

    static final int LEFT = 1;
    static final int UP = 2;
    static final int RIGHT = 3;
    static final int DOWN = 4;

    private int playerX = 0, playerY = 0;
    private int enemyX = 0, enemyY = 0;

    public ChaseLogic(int playerX, int playerY, int enemyX, int enemyY) {
        this.playerX = playerX;
        this.playerY = playerY;
        this.enemyX = enemyX;
        this.enemyY = enemyY;
    }

    public Vector<Integer> getChaseDirections() {
        Vector<Integer> directions = new Vector<Integer>();
        if (enemyX > playerX) directions.add(LEFT);
        else if (enemyX < playerX) directions.add(RIGHT);

        if (enemyY > playerY) directions.add(UP);
        else if (enemyY < playerY) directions.add(DOWN);
        return directions;
    }
}
