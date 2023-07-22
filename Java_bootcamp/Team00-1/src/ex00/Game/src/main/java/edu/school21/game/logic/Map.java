package edu.school21.game.logic;

import com.diogonunes.jcdp.color.ColoredPrinter;
import com.diogonunes.jcdp.color.api.Ansi;
import edu.school21.game.exceptions.IllegalParametersException;

import java.util.Collections;
import java.util.Vector;

import static java.lang.System.exit;

public class Map {

    private static Map  map;

    public  char[][] gameMap;
    private boolean isCorrectMap;
    private int enemiesCount;
    private int wallsCount;
    private int size;
    private PropertiesLoader properties;

    public static Map getInstance() {
        if (map == null) {
            map = new Map();
        }
        return map;
    }

    public void initMap(int enemiesCount, int wallsCount, int size) {
        try {
            validateData(enemiesCount, wallsCount, size);
        } catch (Exception e) {
            e.printStackTrace();
            exit(1);
        }
        this.enemiesCount = enemiesCount;
        this.wallsCount = wallsCount;
        this.size = size;
        this.gameMap = new char[size][size];
    }

    public void generateMap() {
        isCorrectMap = true;
        int times = 10, i = 0;
        for (; i < times && !map.canReachGoal(); i++) {
            map.generateMap_();
        }
        if (i == times - 1) isCorrectMap = false;
    }

    private void generateMap_() {
        Vector<Character> tempMap = new Vector<Character>();

        for (int i = 0; i < enemiesCount; i++) tempMap.add(properties.getEnemyChar());
        for (int i = 0; i < wallsCount; i++) tempMap.add(properties.getWallChar());
        for (int i = 0; i < size * size - enemiesCount - wallsCount -2; i++) tempMap.add(properties.getEmptyChar());
        tempMap.add(properties.getGoalChar());
        tempMap.add(properties.getPlayerChar());
        Collections.shuffle(tempMap);

        int i = 0;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                gameMap[x][y] = tempMap.get(i);
                i++;
            }
        }
    }

    public void printMap() {
        ColoredPrinter printer = new ColoredPrinter.Builder(1, false).build();
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (gameMap[x][y] == properties.getEnemyChar()) {
                    printer.setBackgroundColor(Ansi.BColor.valueOf(properties.getEnemyColor()));
                    printer.print(properties.getEnemyChar());

                } else if (gameMap[x][y] == properties.getPlayerChar()) {
                    printer.setBackgroundColor(Ansi.BColor.valueOf(properties.getPlayerColor()));
                    printer.print(properties.getPlayerChar());

                } else if (gameMap[x][y] == properties.getWallChar()) {
                    printer.setBackgroundColor(Ansi.BColor.valueOf(properties.getWallColor()));
                    printer.print(properties.getWallChar());

                } else if (gameMap[x][y] == properties.getGoalChar()) {
                    printer.setBackgroundColor(Ansi.BColor.valueOf(properties.getGoalColor()));
                    printer.print(properties.getGoalChar());

                } else if (gameMap[x][y] == properties.getEmptyChar()) {
                    printer.setBackgroundColor(Ansi.BColor.valueOf(properties.getEmptyColor()));
                    printer.print(properties.getEmptyChar());
                }
//                temp
                printer.print(" ");
            }
            System.out.println();
        }
    }

    public int getSize() {
        return size;
    }

    public boolean isCorrect() {
        return isCorrectMap;
    }

    public PropertiesLoader getProperties() {
        return properties;
    }

    public void setProperties(PropertiesLoader properties) {
        this.properties = properties;
    }

    private void validateData(int enemiesCount, int wallsCount, int size) throws Exception {
//        Добавить нормальную валидацию
        if (enemiesCount < 1 || wallsCount < 0 ||
            enemiesCount + wallsCount + 2 > size * size) {
            throw new IllegalParametersException("IllegalParametersException");
        }
    }

    public boolean canReachGoal() {
        int playerRow = -1;
        int playerCol = -1;
        int goalRow = -1;
        int goalCol = -1;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (map.gameMap[i][j] == properties.getPlayerChar()) {
                    playerRow = i;
                    playerCol = j;
                } else if (map.gameMap[i][j] == properties.getGoalChar()) {
                    goalRow = i;
                    goalCol = j;
                }
            }
        }

        return canReachGoalHelper(playerRow, playerCol, goalRow, goalCol);
    }

    private boolean canReachGoalHelper(int row, int col, int goalRow, int goalCol) {
        if (row < 0 || row >= size || col < 0 || col >= size || map.gameMap[row][col] == properties.getWallChar()) {
            return false;
        }

        if (row == goalRow && col == goalCol) {
            return true;
        }

        char originalSymbol = map.gameMap[row][col];
        map.gameMap[row][col] = properties.getWallChar();

        boolean canReachGoal = canReachGoalHelper(row - 1, col, goalRow, goalCol) ||
                canReachGoalHelper(row + 1, col, goalRow, goalCol) ||
                canReachGoalHelper(row, col - 1, goalRow, goalCol) ||
                canReachGoalHelper(row, col + 1, goalRow, goalCol);

        map.gameMap[row][col] = originalSymbol;
        return canReachGoal;
    }
}
