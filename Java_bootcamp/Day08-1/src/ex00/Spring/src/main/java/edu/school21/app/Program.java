package edu.school21.app;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Program {
    public static void main(String[] args) {
        /*PreProcessor preProcessor = new PreProcessorToUpperImpl();
        Renderer renderer = new RendererErrImpl(preProcessor);
        PrinterWithPrefixImpl printer = new PrinterWithPrefixImpl(renderer);
        printer.setPrefix("Prefix");
        printer.print("Hello!");*/

        ApplicationContext context = new ClassPathXmlApplicationContext("context.xml");
        Printer printer = context.getBean("printerWithPrefixStdToUpper", Printer.class);
        printer.print("Hello!");

    }
}
