package DataSource;

import java.io.PrintWriter;
import java.sql.*;

public class LibraryServlet {
    public static void main(String[] args) {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        try {
            Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/postgres",
                    "postgres", "059332");
            Statement statement = connection.createStatement();
            ResultSet rs = statement.executeQuery("SELECT * FROM users");

            while(rs.next()) {
                System.out.println(rs.getString("id") + " " + rs.getString("login") + " "
                        + rs.getString("password"));
            }
            statement.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
