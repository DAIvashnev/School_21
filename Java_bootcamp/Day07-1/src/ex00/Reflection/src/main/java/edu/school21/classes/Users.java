package edu.school21.classes;

public class Users {
    private String name;
    private int age;
    private double height;

    public Users() {
        this.name = "Default user name";
        this.age = 0;
        this.height = 0;
    }

    public Users(String name, int age, double height) {
        this.name = name;
        this.age = age;
        this.height = height;
    }

    public double grow(double value) {
        this.height += value;
        return height;
    }

    @Override
    public String toString() {
        return "Users{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", height=" + height +
                '}';
    }
}
