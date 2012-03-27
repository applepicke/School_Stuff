/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jsf;

import java.io.Serializable;
import javax.ejb.EJB;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.component.UIInput;
import javax.faces.context.FacesContext;
import jpa.entities.UserAccount;
import jpa.session.UserAccountFacade;

/**
 *
 * @author willy
 */
@ManagedBean(name = "loginController")
@SessionScoped
public class LoginController implements Serializable {

    @EJB
    private jpa.session.UserAccountFacade ejbFacade;
    private Boolean isAuthenticated;
    private String password;
    private String username;

    public LoginController() {
        
    }

    public String doAuthenticate() {
        FacesMessage message;

        FacesContext context = FacesContext.getCurrentInstance();

        // assume authentication will fail
        isAuthenticated = false;

        // retrieve the account from the db
        UserAccount loginAccount = ejbFacade.findByUsername(username);

        // authenticate username
        if ((loginAccount == null) || (loginAccount.getUsername().equals(username) == false)) {
            ((UIInput) context.getViewRoot().findComponent("LoginForm:username")).setValid(false);
            message = new FacesMessage("Unknown Username: " + username);
            context.addMessage("username", message);
            return "login";
        }

        // authenticate password
        if (loginAccount.getPassword().equals(password) == false) {
            ((UIInput) context.getViewRoot().findComponent("LoginForm:password")).setValid(false);
            message = new FacesMessage("Invalid password: " + password);
            context.addMessage("password", message);
            return "login";
        }

        isAuthenticated = true;
        return "authenticated?faces-redirect=true";
    }

    public String doLogin() {
        return this.doLogout();
    }

    public String doLogout() {
        this.setUsername("");
        this.setPassword("");
        isAuthenticated = false;

        return "login?faces-redirect=true";
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

    public UserAccountFacade getEjbFacade() {
        return ejbFacade;
    }

    public Boolean getIsAuthenticated() {
        return isAuthenticated;
    }

    public void setEjbFacade(UserAccountFacade ejbFacade) {
        this.ejbFacade = ejbFacade;
    }

    public void setIsAuthenticated(Boolean isAuthenticated) {
        this.isAuthenticated = isAuthenticated;
    }
    
    
}