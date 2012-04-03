/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

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

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public Users findByUsername(String username) {
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
