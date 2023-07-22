package edu.school21.app;

public class PreProcessorToLowerImpl implements PreProcessor {
    @Override
    public String process(String msg) {
        return msg.toLowerCase();
    }
}
