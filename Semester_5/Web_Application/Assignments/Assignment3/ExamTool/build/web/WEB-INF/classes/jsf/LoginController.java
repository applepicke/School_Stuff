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
import javax.faces.component.UIInput;
import javax.faces.context.FacesContext;
import jpa.entities.Users;
import jpa.session.UsersFacade;

/**
 *
 * @author willy
 */
@ManagedBean(name = "login")
@SessionScoped
public class LoginController implements Serializable {

    @EJB
    private UsersFacade ejbFacade;
    private Boolean isAuthenticated;
    private String password;
    private String username;

    public LoginController() {
        isAuthenticated = false;
        password = "";
        username = "";
    }

    public void login() throws IOException {
        FacesMessage message;

        FacesContext context = FacesContext.getCurrentInstance();

        // assume authentication will fail
        isAuthenticated = false;

        // retrieve the account from the db
        Users loginAccount = ejbFacade.findByUsername(username);

        // authenticate username
        if ((loginAccount == null) || (loginAccount.getUsername().equals(username) == false)) {
            ((UIInput) context.getViewRoot().findComponent("loginForm:username")).setValid(false);
            message = new FacesMessage( FacesMessage.SEVERITY_ERROR ,"Unknown Username", null);
            context.addMessage("username", message);
            return;
        }

        // authenticate password
        if (loginAccount.getPassword().equals(password) == false) {
            ((UIInput) context.getViewRoot().findComponent("loginForm:password")).setValid(false);
            message = new FacesMessage( FacesMessage.SEVERITY_ERROR, "Invalid password", null);
            context.addMessage("password", message);
            return;
        }

        isAuthenticated = true;

        context.getExternalContext().redirect("examlist.xhtml");
    }
    
    public void logout() throws IOException{
        setUsername( "" );
        setPassword( "" );
        isAuthenticated = false;
        
        FacesContext.getCurrentInstance().getExternalContext().redirect("login.xhtml");
    }
    
    public void testAuthentication() throws IOException{
        if (isAuthenticated == null || !isAuthenticated){
            FacesContext.getCurrentInstance().getExternalContext().redirect("login.xhtml");
        }
    }

    public Boolean getIsAuthenticated() {
        return isAuthenticated;
    }

    public void setIsAuthenticated(Boolean isAuthenticated) {
        this.isAuthenticated = isAuthenticated;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }
    
    
}
