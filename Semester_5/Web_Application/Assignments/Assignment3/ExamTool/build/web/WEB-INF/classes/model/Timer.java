/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.Serializable;
import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;

/**
 *
 * @author willy
 */
public class Timer implements Serializable{
    
    private int hour;
    private int minute;
    private int second;
    
    private long totalTime;
    private int progress;
    
    private boolean finished;
    
    public Timer(String time){
        String[] data = time.split(":");
        try {
            hour = Integer.parseInt(data[0]);
            minute = Integer.parseInt(data[1]);
            second = Integer.parseInt(data[2]);
        } catch (NumberFormatException e){
            hour = 0;
            minute = 0;
            second = 0;
        }
        finished = false;
        totalTime = ((hour * 60 * 60) + (minute * 60) + second);
    }
    
    public void checkTime(){  
        if (finished)
            return;
        
        second--;
        if (second <= 0 && minute > 0){
            minute--;
            second = 59;
        }
        if (minute <= 0 && hour > 0){       
            hour--;
            minute = 59;            
        }
        
        if (hour == 0 && minute == 0 && second == 0){
            finished = true;
            FacesContext.getCurrentInstance().addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Time is up! Grading exam...", null));
        }
        
        progress = (int) (((float)(totalTime - ((hour * 60 * 60) + (minute * 60) + second)) / totalTime) * 100) ;
    }

    public int getHour() {
        if (hour < 0)
            return 0;
        return hour;
    }

    public void setHour(int hour) {
        this.hour = hour;
    }

    public int getMinute() {
        if (minute < 0)
            return 0;
        return minute;
    }

    public void setMinute(int minute) {
        this.minute = minute;
    }

    public int getSecond() {
        if (second < 0)
            return 0;
        return second;
    }

    public void setSecond(int second) {
        this.second = second;
    }

    public int getProgress() {
        return progress;
    }

    public void setProgress(int progress) {
        this.progress = progress;
    }


    public long getTotalTime() {
        return totalTime;
    }

    public void setTotalTime(long totalTime) {
        this.totalTime = totalTime;
    }
    
    
    
    
}
