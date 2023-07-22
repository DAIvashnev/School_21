package edu.school21.game.logic;

import edu.school21.game.exceptions.IllegalParametersException;

import java.io.IOException;
import java.util.Properties;

import static java.lang.System.exit;

public class PropertiesLoader {
    private char enemyChar;
    private char playerChar;
    private char wallChar;
    private char goalChar;
    private char emptyChar;

    private String enemyColor;
    private String playerColor;
    private String wallColor;
    private String goalColor;
    private String emptyColor;

    public char getEnemyChar() {
        return enemyChar;
    }
    public char getPlayerChar() {
        return playerChar;
    }
    public char getWallChar() {
        return wallChar;
    }
    public char getGoalChar() {
        return goalChar;
    }
    public char getEmptyChar() {
        return emptyChar;
    }

    public String getEnemyColor() {
        return enemyColor;
    }
    public String getPlayerColor() {
        return playerColor;
    }
    public String getWallColor() {
        return wallColor;
    }
    public String getGoalColor() {
        return goalColor;
    }
    public String getEmptyColor() {
        return emptyColor;
    }


    public void loadProperties(String profile) {
        String path;

        path = "/application-" + profile + ".properties";

        Properties props = new Properties();
        try {
            props.load(PropertiesLoader.class.getResourceAsStream(path));

            String charProperty = props.getProperty("enemy.char", "X");
            if (charProperty.length() > 0) enemyChar = charProperty.charAt(0);
            else enemyChar = 'X';
            charProperty = props.getProperty("player.char", "P");
            if (charProperty.length() > 0) playerChar = charProperty.charAt(0);
            else playerChar = 'P';
            charProperty = props.getProperty("wall.char", "#");
            if (charProperty.length() > 0) wallChar = charProperty.charAt(0);
            else wallChar = '#';
            charProperty = props.getProperty("goal.char", "G");
            if (charProperty.length() > 0) goalChar = charProperty.charAt(0);
            else goalChar = 'G';
            charProperty = props.getProperty("empty.char", "");
            if (charProperty.length() > 0) emptyChar = charProperty.charAt(0);
            else emptyChar = ' ';
            enemyColor = props.getProperty("enemy.color", "RED");
            playerColor = props.getProperty("player.color", "GREEN");
            wallColor = props.getProperty("wall.color", "MAGENTA");
            goalColor = props.getProperty("goal.color", "BLUE");
            emptyColor = props.getProperty("empty.color", "YELLOW");

        } catch (IOException e) {
            e.printStackTrace();
            exit(1);
        } catch (NullPointerException e) {
            throw new IllegalParametersException("There is no profile .properties file");
        }
    }

}
