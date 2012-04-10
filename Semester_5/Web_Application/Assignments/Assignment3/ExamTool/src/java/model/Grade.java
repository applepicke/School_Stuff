/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.Serializable;

/**
 *
 * @author willy
 */
public class Grade implements Serializable{
    
    private int numCorrect;
    private int numQuestions;
    private int percentage;
    private String letterGrade;
    
    private boolean[] gradeMap;
    
    public Grade(boolean[] grades){
        
        gradeMap = grades;
        numCorrect = 0;
        numQuestions = 0;
        
        for (boolean b: grades){
            numQuestions++;
            if (b) numCorrect++;
        }       
        
        percentage = (int)(((float)numCorrect / (float)numQuestions) * 100.0f);
        
        if (percentage >= 90 )
            letterGrade = "A+";
        else if (percentage >= 85)
            letterGrade = "A";
        else if (percentage >= 80)
            letterGrade = "A-";
        else if (percentage >= 77)
            letterGrade = "B+";
        else if (percentage >= 73)
            letterGrade = "B";
        else if (percentage >= 70)
            letterGrade = "B-";
        else if (percentage >= 67)
            letterGrade = "C+";
        else if (percentage >= 63)
            letterGrade = "C";
        else if (percentage >= 60)
            letterGrade = "C-";
        else if (percentage >= 57)
            letterGrade = "D+";
        else if (percentage >= 53)
            letterGrade = "D";
        else if (percentage >= 50)
            letterGrade = "D-";
        else
            letterGrade = "F";
        
    }

    public String getLetterGrade() {
        return letterGrade;
    }

    public int getNumCorrect() {
        return numCorrect;
    }

    public int getNumQuestions() {
        return numQuestions;
    }

    public int getPercentage() {
        return percentage;
    }
    
    
    
}
