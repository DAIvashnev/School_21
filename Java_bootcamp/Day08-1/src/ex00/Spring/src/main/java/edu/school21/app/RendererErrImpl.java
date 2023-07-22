package edu.school21.app;

import edu.school21.app.PreProcessor;

public class RendererErrImpl implements Renderer{
    private PreProcessor preprocessor;

    public RendererErrImpl(PreProcessor preprocessor){
        this.preprocessor = preprocessor;
    }

    @Override
    public void render(String msg) {
        System.err.println(preprocessor.process(msg));
    }
}
