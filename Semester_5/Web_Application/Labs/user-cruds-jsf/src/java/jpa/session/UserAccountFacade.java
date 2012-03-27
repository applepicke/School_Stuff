/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.entities.UserAccount;

/**
 *
 * @author willy
 */
@Stateless
public class UserAccountFacade extends AbstractFacade<UserAccount> {
    @PersistenceContext(unitName = "user-cruds-jsfPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public UserAccountFacade() {
        super(UserAccount.class);
    }
    
    public UserAccount findByUsername(String username){
        UserAccount user = (UserAccount) em.createNamedQuery("UserAccount.findByUsername").setParameter("username", username).getSingleResult();
        return user;
    }
    
}
