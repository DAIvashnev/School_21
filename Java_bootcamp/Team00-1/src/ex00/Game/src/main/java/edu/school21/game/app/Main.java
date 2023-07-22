package edu.school21.game.app;

import com.beust.jcommander.JCommander;
import com.beust.jcommander.Parameter;
import com.beust.jcommander.Parameters;
import edu.school21.game.logic.Game;

@Parameters(separators = "=")
public class Main {
    @Parameter(names={"--enemiesCount"}, required = true)
    private static int enemiesCount;
    @Parameter(names={"--wallsCount"}, required = true)
    private static int wallsCount;
    @Parameter(names={"--size"}, required = true)
    private static int size;
    @Parameter(names={"--profile"})
    private static String profile;

    public static void main(String[] args) {

        Main program = new Main();
        JCommander.newBuilder()
                .addObject(program)
                .build()
                .parse(args);
        program.run();
    }

    private void run() {
        boolean isDev = false;
        if (profile.equals("dev")) {
            isDev = true;
        }
        Game game = new Game(isDev, profile, enemiesCount, wallsCount, size);
        game.startGame();
    }
}