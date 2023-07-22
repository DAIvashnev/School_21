package edu.school21.chat.app;

import edu.school21.chat.models.Message;
import edu.school21.chat.repositories.*;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;
import javax.sql.DataSource;

public class Program {

    public static void main(String[] args) throws ClassNotFoundException {

        HikariConfig config = new HikariConfig();
        config.setJdbcUrl(url);
        config.setUsername(user);
        config.setPassword(password);

        DataSource dataSource = new HikariDataSource(config);

        MessagesRepositoryJdbcImpl msg = new MessagesRepositoryJdbcImpl(dataSource);
        Message message = msg.findById(3L).get();
        System.out.println("Message : " + message.toString());
    }
}
