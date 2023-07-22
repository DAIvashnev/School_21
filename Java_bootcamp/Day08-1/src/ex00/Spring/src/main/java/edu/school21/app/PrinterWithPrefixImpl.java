package edu.school21.app;

import edu.school21.app.Renderer;

public class PrinterWithPrefixImpl implements Printer{
    private Renderer renderer;
    private String prefix;

    public PrinterWithPrefixImpl(Renderer renderer){
        this.renderer = renderer;
        this.prefix = "PREFIX";
    }

    public void setPrefix(String prefix){
        this.prefix = prefix;
    }
    @Override
    public void print(String msg) {
        renderer.render(prefix + " " + msg);
    }
}
