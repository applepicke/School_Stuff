/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jsf;

import java.io.IOException;
import java.io.Serializable;
import java.util.List;
import javax.ejb.EJB;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
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
    
    public ExamListController(){
       
    }

    public List<String> getExams() {
        return ejbFacade.findAllExamsTitles();
    }

    
}
