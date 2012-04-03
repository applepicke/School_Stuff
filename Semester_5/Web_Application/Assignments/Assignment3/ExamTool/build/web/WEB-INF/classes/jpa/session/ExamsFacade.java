/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.entities.Exams;

/**
 *
 * @author willy
 */
@Stateless
public class ExamsFacade extends AbstractFacade<Exams> {
    @PersistenceContext(unitName = "ExamToolPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public ExamsFacade() {
        super(Exams.class);
    }
    
}
