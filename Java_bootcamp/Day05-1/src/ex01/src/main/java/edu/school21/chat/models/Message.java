package edu.school21.chat.models;

import java.time.OffsetDateTime;
import java.util.Objects;

public class Message {
    private long id;
    private User authorMessage;
    private Chatroom nameRoom;
    private String textMessage;
    private OffsetDateTime dateTime;

    public Message() {
    }

    public void setId(long id) { this.id = id; }
    public void setAuthorMessage(User authorMessage) { this.authorMessage = authorMessage; }
    public void setNameRoom(Chatroom nameRoom) { this.nameRoom = nameRoom; }
    public void setTextMessage(String textMessage) { this.textMessage = textMessage; }
    public void setDateTime(OffsetDateTime dateTime) { this.dateTime = dateTime; }


    public long getId() { return id; }
    public User getAuthorMessage() { return authorMessage; }
    public Chatroom getNameRoom() { return nameRoom; }
    public String getTextMessage() { return textMessage; }
    public OffsetDateTime getDateTime() { return dateTime; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Message message = (Message) o;
        return id == message.id && Objects.equals(authorMessage, message.authorMessage) && Objects.equals(nameRoom, message.nameRoom) && Objects.equals(textMessage, message.textMessage) && Objects.equals(dateTime, message.dateTime);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, authorMessage, nameRoom, textMessage, dateTime);
    }

    @Override
    public String toString() {
        return "Message{" +
                "id=" + id +
                ", authorMessage=" + authorMessage +
                ", nameRoom=" + nameRoom +
                ", textMessage='" + textMessage + '\'' +
                ", dateTime=" + dateTime +
                '}';
    }
}
