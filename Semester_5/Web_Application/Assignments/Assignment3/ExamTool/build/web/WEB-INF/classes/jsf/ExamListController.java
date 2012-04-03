/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jsf;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import jpa.entities.Exams;
import jpa.session.ExamsFacade;

/**
 *
 * @author willy
 */
@ManagedBean (name = "examList")
@SessionScoped
public class ExamListController implements Serializable{
    
    @EJB
    private ExamsFacade ejbFacade;
    private String examToTake;
    
    public ExamListController(){
        
    }

    public List<String> getExams() {
        return ejbFacade.findAllExamsTitles();
    }

    public String getExamToTake() {
        return examToTake;
    }

    public void setExamToTake(String examToTake) {
        this.examToTake = examToTake;
    }

    
    
}
