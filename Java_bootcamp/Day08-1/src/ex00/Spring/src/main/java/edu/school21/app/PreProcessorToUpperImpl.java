package edu.school21.app;

public class PreProcessorToUpperImpl implements PreProcessor {
    @Override
    public String process(String msg) {
        return msg.toUpperCase();
    }
}
