/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
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

    public static final Logger log;
    
    static {
        log = Logger.getLogger("ExamLogger");
        log.setLevel(Level.ALL);
    }
    
    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
    public List<String> findAllExamsTitles() {
        log.log(Level.INFO, "Searching database for exam titles");
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
        log.log(Level.INFO, "Retrieving exam from database: " + examTitle);
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
