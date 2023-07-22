package edu.school21.app;

import edu.school21.classes.*;
import java.lang.reflect.*;
import java.util.Map;
import java.util.Scanner;

public class Program {
    static private Map<String, Class<?>> classes;
    public static void main(String[] args) throws IllegalAccessException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Classes:");
        System.out.println("---------------------");
        System.out.println("Enter class name");
        if(scanner.nextLine().equals("Users")) {
            Users user = new Users();
            Class cl = user.getClass();
            Field[] fields = cl.getDeclaredFields();
            Method[] methods = cl.getDeclaredMethods();
            System.out.println("---------------------");
            System.out.println("fields:");
            for (Field field : fields) {
                System.out.println("\t\t" + field.getType().getSimpleName() + "  " + field.getName());
            }
            System.out.println("methods:");
            for (Method method : methods) {
                System.out.println("\t\t" + method.getName());
            }
            System.out.println("---------------------");
            System.out.println("Let's create an object.");
            for (Field field : fields) {
                field.setAccessible(true);
                if(field.getType().getSimpleName().equals("String")) {
                    System.out.println("userName:");
                    field.set(user, scanner.nextLine());
                }
                if(field.getType().getSimpleName().equals("int")) {
                    System.out.println("age:");
                    field.setInt(user, scanner.nextInt());
                }
                if(field.getType().getSimpleName().equals("double")) {
                    System.out.println("height:");
                    field.setDouble(user, scanner.nextDouble());
                }
            }
            System.out.print("Object created: " + cl.getSimpleName());
            for (Field field : fields) {
                field.setAccessible(true);
                if(field.getType().getSimpleName().equals("String")) {
                    System.out.print("[userName="+field.get(user));
                }
                if(field.getType().getSimpleName().equals("int")) {
                    System.out.print(", age="+field.getInt(user));
                }
                if(field.getType().getSimpleName().equals("double")) {
                    System.out.print(", height="+field.getDouble(user)+"]");
                }
            }
        }
    }
}
