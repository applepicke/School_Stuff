/*******************************************************************/
/**                                                               **/
/**                                                               **/
/**    Student Name                :  William Collins             **/
/**    EMail Address               :  coll0300@algonquinlive.com  **/
/**    Student Number              :  040652633                   **/
/**    Student User ID             :  coll0300                    **/
/**    Course Number               :  CST 8218                    **/
/**    Lab Section Number          :  310                         **/
/**    Professor Name              :  Hurdleg                     **/
/**    Assignment Name/Number/Date :  Exam Tool / 3 / 4/13/2012   **/
/**    Optional Comments           :  I like pie                  **/
/**                                                               **/
/**                                                               **/
/*******************************************************************/
package model;

import java.io.Serializable;
import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;

/**
 *
 * @author willy
 */
public class Timer implements Serializable {

    private int hour;
    private int minute;
    private int second;
    private long totalTime;
    private int progress;
    private boolean finished;

    public Timer(String time) {
        String[] data = time.split(":");
        try {
            hour = Integer.parseInt(data[0]);
            minute = Integer.parseInt(data[1]);
            second = Integer.parseInt(data[2]);
        } catch (NumberFormatException e) {
            hour = 0;
            minute = 0;
            second = 0;
        }
        finished = false;
        totalTime = ((hour * 60 * 60) + (minute * 60) + second);
    }

    /**
     * Removes a second from the timer.
     * @return whether or not the timer has expired
     */
    public boolean checkTime() {

        second--;
        if (second <= 0 && minute > 0) {
            minute--;
            second = 59;
        }
        if (minute <= 0 && hour > 0) {
            hour--;
            minute = 59;
        }

        if (hour == 0 && minute == 0 && second == 1){
            FacesContext.getCurrentInstance().addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Time is up! Grading exam...", null));
        }
        
        if (hour == 0 && minute == 0 && second == 0) {
            return true;

        }

        progress = (int) (((float) (totalTime - ((hour * 60 * 60) + (minute * 60) + second)) / totalTime) * 100);
        return false;
    }

    public int getHour() {
        if (hour < 0) {
            return 0;
        }
        return hour;
    }

    public void setHour(int hour) {
        this.hour = hour;
    }

    public int getMinute() {
        if (minute < 0) {
            return 0;
        }
        return minute;
    }

    public void setMinute(int minute) {
        this.minute = minute;
    }

    public int getSecond() {
        if (second < 0) {
            return 0;
        }
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
