package edu.school21.game.logic;

public class Player {

    static final int LEFT = 1;
    static final int UP = 2;
    static final int RIGHT = 3;
    static final int DOWN = 4;

    private Map map;
    private PropertiesLoader properties;
    private int x;
    private int y;
    public String playerStatus = "playing";

    public Player(Map map) {
        this.map = map;
        this.properties = map.getProperties();
        for (int y = 0; y < map.getSize(); y++) {
            for (int x = 0; x < map.getSize(); x++) {
                if (map.gameMap[x][y] == properties.getPlayerChar()) {
                    this.x = x;
                    this.y = y;
                }
            }
        }
    }

    public void move(int moveIndex) {
        if (isPossibleToMove()) {
            if (moveIndex == LEFT) moveLeft();
            else if (moveIndex == UP) moveUp();
            else if (moveIndex == RIGHT) moveRight();
            else if (moveIndex == DOWN) moveDown();
        } else playerStatus = "lose";
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    private void moveLeft() {
        if (x != 0 && isPossibleToMove(x - 1, y)) {
            swapEntities(x - 1, y);
            x--;
        }
    }

    private void moveUp() {
        if (y != 0 && isPossibleToMove(x, y - 1)) {
            swapEntities(x, y - 1);
            y--;
        }
    }

    private void moveRight() {
        if (x != map.getSize() - 1 && isPossibleToMove(x + 1, y)) {
            swapEntities(x + 1, y);
            x++;
        }
    }

    private void moveDown() {
        if (y != map.getSize() - 1 && isPossibleToMove(x, y + 1)) {
            swapEntities(x, y + 1);
            y++;
        }
    }

    public boolean isPossibleToMove() {
        boolean result = isPossibleToMove(x - 1, y);
        result |= isPossibleToMove(x + 1, y);
        result |= isPossibleToMove(x, y - 1);
        result |= isPossibleToMove(x, y + 1);

        return result;
    }

    private boolean isPossibleToMove(int newX, int newY) {
        boolean result = false;

        if (newX >= 0 && newX < map.getSize() && newY >= 0 && newY < map.getSize()) {
            if (map.gameMap[newX][newY] == properties.getEmptyChar() || map.gameMap[newX][newY] == properties.getGoalChar()) {
                result = true;
            }
        }

        return result;
    }

    private void swapEntities(int newX, int newY) {
        char temp = map.gameMap[newX][newY];
        if (temp == properties.getGoalChar()) {
            temp = properties.getEmptyChar();
            playerStatus = "win";
        }
        map.gameMap[newX][newY] = properties.getPlayerChar();
        map.gameMap[x][y] = temp;
    }
}
