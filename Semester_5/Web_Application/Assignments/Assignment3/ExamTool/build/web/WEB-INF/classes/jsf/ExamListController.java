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
package jsf;

import java.io.Serializable;
import java.util.List;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
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
