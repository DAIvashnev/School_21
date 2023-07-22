package edu.school21.chat.models;

import java.util.List;
import java.util.Objects;

public class Chatroom {
    private long id;
    private String name;
    private User owner;
    private List<Message> chatMessage;

    public Chatroom() {
    }

    public void setId(long id) { this.id = id; }
    public void setName(String name) { this.name = name; }
    public void setOwner(User owner) { this.owner = owner; }
    public void setChatMessage(List<Message> chatMessage) { this.chatMessage = chatMessage; }

    public long getId() { return id; }
    public String getName() { return name; }
    public User getOwner() { return owner; }
    public List<Message> getChatMessage() { return chatMessage; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Chatroom chatroom = (Chatroom) o;
        return id == chatroom.id && Objects.equals(name, chatroom.name) && Objects.equals(owner, chatroom.owner) && Objects.equals(chatMessage, chatroom.chatMessage);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name, owner, chatMessage);
    }

    @Override
    public String toString() {
        return "Chatroom{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", owner=" + owner +
                ", chatMessage=" + chatMessage +
                '}';
    }
}
