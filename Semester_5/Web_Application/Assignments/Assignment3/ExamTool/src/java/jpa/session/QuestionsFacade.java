/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.entities.Questions;

/**
 *
 * @author willy
 */
@Stateless
public class QuestionsFacade extends AbstractFacade<Questions> {
    @PersistenceContext(unitName = "ExamToolPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public QuestionsFacade() {
        super(Questions.class);
    }
    
}
