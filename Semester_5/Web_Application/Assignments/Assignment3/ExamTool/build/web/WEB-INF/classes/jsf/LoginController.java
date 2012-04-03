/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jsf;

import java.io.IOException;
import java.io.Serializable;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;

/**
 *
 * @author willy
 */
@ManagedBean (name="login")
@SessionScoped
public class LoginController implements Serializable{
    
    @EJB private jpa.session.UsersFacade ejbFacade;
    private Boolean isAuthenticated;
    private String password;
    private String username;
    
    public LoginController(){
        
    }
    
    public void login() throws IOException{
        
        
        FacesContext.getCurrentInstance().getExternalContext().redirect("examlist.xhtml");
    }
    
}
