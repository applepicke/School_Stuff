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
import javax.faces.context.FacesContext;
import jpa.entities.Exams;
import jpa.entities.Questions;
import jpa.session.ExamsFacade;
import model.Grade;
import model.Timer;

/**
 *
 * @author willy
 */
@ManagedBean (name = "exam")
@SessionScoped
public class ExamController implements Serializable{
    
    public static final String MC_4 = "MC_4";
    public static final String MC_5 = "MC_5";
    public static final String MC_2 = "MC_2";

    
    @EJB
    private ExamsFacade ejbFacade;

    private Exams exam;
    private String examName;
    private Timer timer;
    
    private int questionIndex;
    private boolean started;
    private boolean finished;
    
    private String[] userAnswers;
    private boolean lastQuestion;
    private boolean firstQuestion;
    
    private Grade userGrade;
    
    public ExamController(){
        exam = null;
        timer = null;
        questionIndex=0;
        userAnswers = new String[100];
        started = false;
    }

    public Exams getExam() {
        return exam;
    }

    public void setExam(Exams exam){
        this.exam = exam;
    }

    public String getExamName() {
        return examName;
    }

    public void setExamName(String examName) {
        this.examName = examName;
    }

    public Timer getTimer() {
        return timer;
    }

    public void setTimer(Timer timer) {
        this.timer = timer;
    }  
    
    public boolean setExam(String examName) throws IOException{
        
        if (examName == null) {
            FacesContext context = FacesContext.getCurrentInstance();
            FacesMessage message = new FacesMessage( FacesMessage.SEVERITY_ERROR ,"No exam selected!", null);
            context.addMessage("Exam", message);
            return false;
        }
        
        Exams examToTake = ejbFacade.findByExamTitle(examName);
        
        //If for some reason we can't find the exam, go back to the examlist
        if (examToTake == null){
            FacesContext.getCurrentInstance().getExternalContext().redirect("examlist.xhtml");
            FacesMessage message = new FacesMessage( FacesMessage.SEVERITY_ERROR ,"Could not find exam!", null);
            FacesContext.getCurrentInstance().addMessage("Exam", message);
            return false;
        }
        
        exam = examToTake;
        timer = new Timer(exam.getDuration());
        return true;
    }
    
    public void takeExam() throws IOException{
        if (setExam(examName))
            FacesContext.getCurrentInstance().getExternalContext().redirect("exam.xhtml");
    }
    
    public Questions getCurrentQuestion(){
        return (Questions) exam.getQuestionsCollection().toArray()[questionIndex];
    }
    
    public void setUserAnswer(String userAnswer){
        userAnswers[questionIndex] = userAnswer;
    }
    
    public String getUserAnswer(){
        if (userAnswers[questionIndex] == null)
            return "";
        return userAnswers[questionIndex];
    }
    
    public boolean isMC4(){
        return getCurrentQuestion().getQType().equals(MC_4);
    }
    
    public boolean isMC5(){
        return getCurrentQuestion().getQType().equals(MC_5);
    }
    
    public void startExam(){
        started = true;
        checkQuestionLocation();
    }
    
    public void finishExam() throws IOException {
        started = false;
        gradeExam();
        exam = null;
        timer = null;
        questionIndex = 0;
        userAnswers = new String[100];
        FacesContext.getCurrentInstance().getExternalContext().redirect("grades.xhtml");
    }
    
    private void gradeExam(){
        
        Questions[] questions = new Questions[exam.getQuestionsCollection().size()];
        exam.getQuestionsCollection().toArray(questions);
        boolean[] results = new boolean[questions.length];
        
        for (int i = 0; i < questions.length; i++){
            results[i] = questions[i].getAnswer().equals(userAnswers[i]);
        }
        
        userGrade = new Grade(results);
        
        
    }
    
    public void testForExam() throws IOException{
        if (exam == null){
            FacesContext.getCurrentInstance().getExternalContext().redirect("examlist.xhtml");
        }
    }
    
    public void nextQuestion(){
        if (questionIndex < exam.getQuestionsCollection().size()-1)            
            questionIndex++;
        
        checkQuestionLocation();       
    }
    
    private void checkQuestionLocation(){
        lastQuestion = false;
        firstQuestion = false;        
        if (questionIndex == exam.getQuestionsCollection().size()-1){
            lastQuestion = true;
        }
        if (questionIndex == 0){
            firstQuestion = true;
        }
    }
    
    public void prevQuestion(){       
        if (questionIndex > 0)           
            questionIndex--;
        checkQuestionLocation();
    }

    public boolean isStarted() {
        return started;
    }

    public void setStarted(boolean started) {
        this.started = started;
    }

    public boolean isFinished() {
        return finished;
    }

    public void setFinished(boolean finished) {
        this.finished = finished;
    }
    
    public void testExamStarted() throws IOException{
        if (started){
            FacesContext.getCurrentInstance().getExternalContext().redirect("exam.xhtml");
        }
    }
    
    public void testForNullGrade() throws IOException{
        if (userGrade == null){
            FacesContext.getCurrentInstance().getExternalContext().redirect("examlist.xhtml");
        }
    }

    public boolean isRenderPrevButton(){
        return (started && !firstQuestion);
    }
    
    public boolean isRenderNextButton(){
        return (started && !lastQuestion);
    }

    public boolean isFirstQuestion() {
        return firstQuestion;
    }

    public boolean isLastQuestion() {
        return lastQuestion;
    }

    public int getQuestionIndex() {
        return questionIndex;
    }

    public Grade getUserGrade() {
        return userGrade;
    }
    
    
    
    
}
