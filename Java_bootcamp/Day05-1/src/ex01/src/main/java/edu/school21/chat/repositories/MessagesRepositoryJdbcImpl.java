package edu.school21.chat.repositories;

import edu.school21.chat.models.Chatroom;
import edu.school21.chat.models.Message;
import edu.school21.chat.models.User;

import javax.sql.DataSource;
import javax.xml.transform.Result;
import java.io.PrintWriter;
import java.sql.*;
import java.util.Optional;

public class MessagesRepositoryJdbcImpl implements MessagesRepository{
    private final DataSource dataSource;

    public MessagesRepositoryJdbcImpl(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @Override
    public Optional<Message> findById(Long id) throws ClassNotFoundException {
        PrintWriter pw = null;
        Message message = new Message();
        Class.forName("org.postgresql.Driver");
        try {
            Connection connection = dataSource.getConnection();
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM messages WHERE message_id = (?)");
            statement.setLong(1, id);
            ResultSet rs = statement.executeQuery();
            while(rs.next())
                pw.println(rs.getString("*"));
            statement.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(message);
    }

    public User findAuthor(Long id) throws SQLException {
        User author = new User();

        Connection connection = dataSource.getConnection();
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE user_id = (?)");
        statement.setLong(1, id);
        ResultSet resultSet = statement.executeQuery();
        if (resultSet.next()) {
            author.setLogin(resultSet.getString("login"));
            author.setPassword(resultSet.getString("password"));
            author.setListCR(null);
            author.setUseChatUser(null);
            author.setId(id);
        }
        connection.close();
        return author;
    }

    public Chatroom findRoom(Long id) throws SQLException {
        Chatroom roomMsg = new Chatroom();

        Connection connection = dataSource.getConnection();
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM rooms WHERE room_id = (?)");
        statement.setLong(1, id);
        ResultSet resultSet = statement.executeQuery();
        if (resultSet.next()) {
            roomMsg.setName(resultSet.getString("name"));
            roomMsg.setChatMessage(null);
            roomMsg.setId(id);
        }
        connection.close();
        return roomMsg;
    }
}
