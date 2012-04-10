/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.NoResultException;
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
    
    public List<String> findAllExamsTitles() {
        List<String> examList = new ArrayList<String>();
        
        try {
            Iterator<Exams> results = em.createNamedQuery("Exams.findAll").getResultList().iterator();
            
            while (results.hasNext()){
                examList.add(results.next().getExamTitle());
            }
            
        } catch (NoResultException e) {
            examList = new ArrayList<String>();
        }

        return examList;
    }
    
    public Exams findByExamTitle(String examTitle){
        Exams exam;
        
        try {
            exam = (Exams)em.createNamedQuery("Exams.findByExamTitle").setParameter("examTitle", examTitle).getSingleResult();
        } catch (NoResultException e){
            exam = null;
        }
        
        return exam;
    }
    
    
    public ExamsFacade() {
        super(Exams.class);
    }
    
}
