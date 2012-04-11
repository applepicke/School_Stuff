/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jsf;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.util.*;
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
import org.primefaces.model.DefaultStreamedContent;
import org.primefaces.model.StreamedContent;

/**
 *
 * @author willy
 */
@ManagedBean (name = "exam")
@SessionScoped
public class ExamController implements Serializable, Comparator {
    
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
        
        cleanup();
        
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
        exam.setQuestionsCollection(randomizeQuestionsAndAnswers());
        timer = new Timer(exam.getDuration());
        userAnswers = new String[100];
        finished = false;
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
    
    /**
     * Randomize all the questions and answers of the exam
     * @return A collection of all the questions in the exam, randomized
     */
    private Collection<Questions> randomizeQuestionsAndAnswers(){
        List<Questions> newCollection = new ArrayList<Questions>(exam.getQuestionsCollection());
        
        //Sort a couple of times for super randomness
        for (Questions q : newCollection){
            Collections.sort(newCollection, this);
        }
        
        for (Questions q : newCollection) {
            List<String> answersList = new ArrayList<String>();
            answersList.add(q.getA());
            answersList.add(q.getB());
            if (q.getQType().equals(MC_4) || q.getQType().equals(MC_5)) {
                answersList.add(q.getC());
                answersList.add(q.getD());
            }
            if (q.getQType().equals(MC_5)){
                answersList.add(q.getE());
            }
            
            for (String s: answersList){
                Collections.sort(answersList, this);
            }
            
            q.setA(answersList.get(0));
            q.setB(answersList.get(1));
            
            if (q.getQType().equals(MC_4) || q.getQType().equals(MC_5)) {
                q.setC(answersList.get(2));
                q.setD(answersList.get(3));
            }
            if (q.getQType().equals(MC_5)){
                q.setE(answersList.get(4));
            }           
        }
        
        
        return newCollection;
    }
    
    public void finishExam() throws IOException {
        started = false;
        finished = true;
        gradeExam();
        timer = null;
        questionIndex = 0;
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
        
        finished = false;
        
    }
    
    public void cleanup(){
        exam = null;
        userAnswers = null;
        userGrade = null;
        timer = null;
        questionIndex = 0;
        finished = false;
        started = false;
    }
    
    public void testForExam() throws IOException{
        if (finished){
            FacesContext.getCurrentInstance().getExternalContext().redirect("grades.xhtml");
        }
        
    }
    
    public void testForExamStarted() throws IOException{
        if (started){
            FacesContext.getCurrentInstance().getExternalContext().redirect("exam.xhtml");
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
    
    public StreamedContent downloadResults() throws UnsupportedEncodingException{
        ArrayList<Integer> resultList = new ArrayList<Integer>();
        Questions[] questions = new Questions[exam.getQuestionsCollection().size()];
        exam.getQuestionsCollection().toArray(questions);
        
        for (int i = 0; i < exam.getQuestionsCollection().size(); i++){
            if (questions[i].getAnswer().equals(userAnswers[i])){
                resultList.add(Integer.valueOf(1));
            }
            else resultList.add(Integer.valueOf(0));
        }
        
        StringBuilder builder = new StringBuilder();
        builder.append(exam.getExamTitle());
        builder.append(",");
        for (int i: resultList){
            builder.append(i);
            builder.append(",");
        }
        builder.append(userGrade.getNumCorrect());
        builder.append(",");
        builder.append(userGrade.getPercentage());
        builder.append(",");
        builder.append(userGrade.getLetterGrade());
        
        StreamedContent content = new DefaultStreamedContent(new ByteArrayInputStream(builder.toString().getBytes("UTF-8")), "txt/plain" ,"results.csv");
        
        return content;
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
    
    public String getQuestionImage(Questions question){
        int i;
        Questions questions[] = new Questions[exam.getQuestionsCollection().size()];
        exam.getQuestionsCollection().toArray(questions);
        
        for (i = 0; i < exam.getQuestionsCollection().size(); i++){
            if (questions[i].getQuestion().equals(question.getQuestion())){
                break;
            }
        }
        
        if (i == exam.getQuestionsCollection().size())
            return "resources/images/error.gif";
        

        if (question.getAnswer().equals(userAnswers[i]))
            return "resources/images/checkmark.gif";
        
        
        return "resources/images/error.gif";
        
    }

    @Override
    public int compare(Object o1, Object o2) {
        Random random = new Random();
        return random.nextInt();
    }
    
    
}
