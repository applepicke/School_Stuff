/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.NoResultException;
import javax.persistence.PersistenceContext;
import jpa.entities.Users;

/**
 *
 * @author willy
 */
@Stateless
public class UsersFacade extends AbstractFacade<Users> {

    @PersistenceContext(unitName = "ExamToolPU")
    private EntityManager em;

    public static final Logger log;
    
    static {
        log = Logger.getLogger("UsersLogger");
        log.setLevel(Level.ALL);
    }
    
    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public Users findByUsername(String username) {
        log.log(Level.INFO, "Retreiving user from database:" + username);
        Users user = null;

        try {
            user = (Users) em.createNamedQuery("Users.findByUsername").setParameter("username", username).getSingleResult();
        } catch (NoResultException e) {
            user = null;
        }

        return user;
    }

    public UsersFacade() {
        super(Users.class);
    }
}
