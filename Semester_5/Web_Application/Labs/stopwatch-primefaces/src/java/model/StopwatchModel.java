/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.Serializable;
import java.text.NumberFormat;

/**
 *
 * @author willy
 */
public class StopwatchModel implements Serializable {

    private static final NumberFormat NF;

    static {
        NF = NumberFormat.getInstance();
        NF.setMaximumIntegerDigits(2);
        NF.setMinimumIntegerDigits(2);
    }
    private int hours;
    private boolean isRunning;
    private int minutes;
    private int seconds;

    public StopwatchModel() {
        this(0, 0, 0);
    }

    public StopwatchModel(int hours, int minutes, int seconds) {
        super();

        this.hours = hours;
        this.minutes = minutes;
        this.seconds = seconds;

        isRunning = false;
    }

    public boolean getlsRunning() {
        return false;
    }

    public void handleTimer() {
        seconds++;
        if (seconds == 60){
            seconds = 0;
            minutes++;
        }
        if (minutes == 60){
            minutes = 0;
            hours++;
        }
    }

    public void reset() {
        hours = minutes = seconds = 0;
    }

    public void start() {
        isRunning = true;
    }

    public void stop() {
        isRunning = false;
    }

    @Override
    public String toString() {
        return (NF.format(hours) + ":" + NF.format(minutes) + ":" + NF.format(seconds));
    }

    public int getHours() {
        return hours;
    }

    public void setHours(int hours) {
        this.hours = hours;
    }

    public boolean isIsRunning() {
        return isRunning;
    }

    public void setIsRunning(boolean isRunning) {
        this.isRunning = isRunning;
    }

    public int getMinutes() {
        return minutes;
    }

    public void setMinutes(int minutes) {
        this.minutes = minutes;
    }

    public int getSeconds() {
        return seconds;
    }

    public void setSeconds(int seconds) {
        this.seconds = seconds;
    }
}
