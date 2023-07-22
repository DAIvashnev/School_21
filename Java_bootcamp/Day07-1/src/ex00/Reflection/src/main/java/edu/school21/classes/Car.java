package edu.school21.classes;

public class Car {
    private String name;
    private double power;
    private String typeEngine;
    private int maxSpeed;

    public Car() {
        this.name = "Default car name";
        this.power = 0;
        this.typeEngine = "Default type engine";
        this.maxSpeed = 0;
    }

    public Car(String name, double power, String typeEngine, int maxSpeed) {
        this.name = name;
        this.power = power;
        this.typeEngine = typeEngine;
        this.maxSpeed = maxSpeed;
    }

    public double upgradePower(double value) {
        this.power += value;
        this.maxSpeed += value/10;
        return power;
    }

    @Override
    public String toString() {
        return "Car{" +
                "name='" + name + '\'' +
                ", power=" + power +
                ", typeEngine='" + typeEngine + '\'' +
                ", maxSpeed=" + maxSpeed +
                '}';
    }
}
