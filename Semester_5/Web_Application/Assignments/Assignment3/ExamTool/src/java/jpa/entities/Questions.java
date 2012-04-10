/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.entities;

import java.io.Serializable;
import javax.persistence.*;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author willy
 */
@Entity
@Table(name = "QUESTIONS")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Questions.findAll", query = "SELECT q FROM Questions q"),
    @NamedQuery(name = "Questions.findByQuestionid", query = "SELECT q FROM Questions q WHERE q.questionid = :questionid"),
    @NamedQuery(name = "Questions.findByQuestion", query = "SELECT q FROM Questions q WHERE q.question = :question"),
    @NamedQuery(name = "Questions.findByA", query = "SELECT q FROM Questions q WHERE q.a = :a"),
    @NamedQuery(name = "Questions.findByB", query = "SELECT q FROM Questions q WHERE q.b = :b"),
    @NamedQuery(name = "Questions.findByC", query = "SELECT q FROM Questions q WHERE q.c = :c"),
    @NamedQuery(name = "Questions.findByD", query = "SELECT q FROM Questions q WHERE q.d = :d"),
    @NamedQuery(name = "Questions.findByE", query = "SELECT q FROM Questions q WHERE q.e = :e"),
    @NamedQuery(name = "Questions.findByAnswer", query = "SELECT q FROM Questions q WHERE q.answer = :answer"),
    @NamedQuery(name = "Questions.findByQType", query = "SELECT q FROM Questions q WHERE q.qType = :qType")})
public class Questions implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @NotNull
    @Column(name = "QUESTIONID")
    private Integer questionid;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 500)
    @Column(name = "QUESTION")
    private String question;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "A")
    private String a;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "B")
    private String b;
    @Size(max = 50)
    @Column(name = "C")
    private String c;
    @Size(max = 50)
    @Column(name = "D")
    private String d;
    @Size(max = 50)
    @Column(name = "E")
    private String e;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "ANSWER")
    private String answer;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "Q_TYPE")
    private String qType;
    @JoinColumn(name = "EXAM_TITLE", referencedColumnName = "EXAM_TITLE")
    @ManyToOne(optional = false)
    private Exams examTitle;
    
    public Questions() {
    }

    public Questions(Integer questionid) {
        this.questionid = questionid;
    }

    public Questions(Integer questionid, String question, String a, String b, String answer, String qType) {
        this.questionid = questionid;
        this.question = question;
        this.a = a;
        this.b = b;
        this.answer = answer;
        this.qType = qType;
    }

    public Integer getQuestionid() {
        return questionid;
    }

    public void setQuestionid(Integer questionid) {
        this.questionid = questionid;
    }

    public String getQuestion() {
        return question;
    }

    public void setQuestion(String question) {
        this.question = question;
    }

    public String getA() {
        return a;
    }

    public void setA(String a) {
        this.a = a;
    }

    public String getB() {
        return b;
    }

    public void setB(String b) {
        this.b = b;
    }

    public String getC() {
        return c;
    }

    public void setC(String c) {
        this.c = c;
    }

    public String getD() {
        return d;
    }

    public void setD(String d) {
        this.d = d;
    }

    public String getE() {
        return e;
    }

    public void setE(String e) {
        this.e = e;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getQType() {
        return qType;
    }

    public void setQType(String qType) {
        this.qType = qType;
    }

    public Exams getExamTitle() {
        return examTitle;
    }

    public void setExamTitle(Exams examTitle) {
        this.examTitle = examTitle;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (questionid != null ? questionid.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Questions)) {
            return false;
        }
        Questions other = (Questions) object;
        if ((this.questionid == null && other.questionid != null) || (this.questionid != null && !this.questionid.equals(other.questionid))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "jpa.entities.Questions[ questionid=" + questionid + " ]";
    }
    
}
