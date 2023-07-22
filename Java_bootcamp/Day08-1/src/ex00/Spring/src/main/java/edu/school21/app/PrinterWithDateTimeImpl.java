package edu.school21.app;

import edu.school21.app.Renderer;

import java.time.LocalDateTime;

public class PrinterWithDateTimeImpl implements Printer{
    private Renderer renderer;

    public PrinterWithDateTimeImpl(Renderer renderer){
        this.renderer = renderer;
    }

    @Override
    public void print(String msg) {
        renderer.render(LocalDateTime.now() + " " + msg);
    }
}
