/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import java.io.Serializable;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import model.StopwatchModel;

/**
 *
 * @author willy
 */
@ManagedBean(name = "controller")
@SessionScoped
public class StopwatchController implements Serializable {

    private StopwatchModel model;
    
    public StopwatchController() {
        super();

        model = new StopwatchModel();
    }

    public String doReset() {
        model.reset();
        return null;
    }

    public String doStart() {
        model.start();
        return null;
    }

    public String doStop() {
        model.stop();
        return null;
    }

    public StopwatchModel getModel() {
        return model;
    }

    public void handleTimer() {
        model.handleTimer();
    }
}
