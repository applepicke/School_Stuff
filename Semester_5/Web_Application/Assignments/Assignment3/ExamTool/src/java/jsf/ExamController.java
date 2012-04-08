/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jsf;

import java.io.IOException;
import java.io.Serializable;
import javax.ejb.EJB;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import jpa.entities.Exams;
import jpa.session.ExamsFacade;

/**
 *
 * @author willy
 */
@ManagedBean (name = "exam")
@SessionScoped
public class ExamController implements Serializable{
    
    @EJB
    private ExamsFacade ejbFacade;

    private Exams exam;
    private String examName;
    
    public ExamController(){
        
    }

    public Exams getExam() {
        return exam;
    }

    public void setExam(Exams exam){
        this.exam = exam;
    }

    public String getExamName() {
        return examName;
    }

    public void setExamName(String examName) {
        this.examName = examName;
    }
    
    
    
    public boolean setExam(String examName) throws IOException{
        
        if (examName == null) {
            FacesContext context = FacesContext.getCurrentInstance();
            FacesMessage message = new FacesMessage( FacesMessage.SEVERITY_ERROR ,"No exam selected!", null);
            context.addMessage("Exam", message);
            return false;
        }
        
        Exams examToTake = ejbFacade.findByExamTitle(examName);
        
        //If for some reason we can't find the exam, go back to the examlist
        if (examToTake == null){
            FacesContext.getCurrentInstance().getExternalContext().redirect("examlist.xhtml");
            FacesMessage message = new FacesMessage( FacesMessage.SEVERITY_ERROR ,"Could not find exam!", null);
            FacesContext.getCurrentInstance().addMessage("Exam", message);
            return false;
        }
        
        exam = examToTake;
        return true;
    }
    
    public void takeExam() throws IOException{
        if (setExam(examName))
            FacesContext.getCurrentInstance().getExternalContext().redirect("exam.xhtml");
    }
    
    
    
}
