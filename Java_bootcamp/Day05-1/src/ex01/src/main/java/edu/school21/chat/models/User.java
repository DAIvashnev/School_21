package edu.school21.chat.models;

import java.util.List;
import java.util.Objects;

public class User {
    private long id;
    private String login;
    private String password;
    private List<Chatroom> createdRooms;
    private List<Chatroom> useChatUser;

    public User() {
    }

    public void setId(long id) { this.id = id; }
    public void setLogin(String login) { this.login = login; }
    public void setPassword(String password) { this.password = password; }
    public void setListCR(List<Chatroom> listCR) { this.createdRooms = listCR; }
    public void setUseChatUser(List<Chatroom> useChatUser) { this.useChatUser = useChatUser; }

    public long getId() { return id; }
    public String getLogin() { return login; }
    public String getPassword() { return password; }
    public List<Chatroom> getListCR() { return createdRooms; }
    public List<Chatroom> getUseChatUser() { return useChatUser; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return id == user.id && Objects.equals(login, user.login) && Objects.equals(password, user.password) && Objects.equals(createdRooms, user.createdRooms) && Objects.equals(useChatUser, user.useChatUser);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, login, password, createdRooms, useChatUser);
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", login='" + login + '\'' +
                ", password='" + password + '\'' +
                ", listCR=" + createdRooms +
                ", useChatUser=" + useChatUser +
                '}';
    }
}
