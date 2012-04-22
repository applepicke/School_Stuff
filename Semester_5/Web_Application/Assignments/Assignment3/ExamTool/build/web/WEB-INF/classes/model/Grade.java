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
    
    /**
     * Create the grade object. Calculating the final grade based on a list of results.
     * @param grades The array of grades.
     */
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
