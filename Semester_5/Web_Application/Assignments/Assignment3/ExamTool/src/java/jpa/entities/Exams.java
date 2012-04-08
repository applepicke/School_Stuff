/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa.entities;

import java.io.Serializable;
import java.util.Collection;
import java.util.Date;
import javax.persistence.*;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author willy
 */
@Entity
@Table(name = "EXAMS")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Exams.findAll", query = "SELECT e FROM Exams e"),
    @NamedQuery(name = "Exams.findByExamTitle", query = "SELECT e FROM Exams e WHERE e.examTitle = :examTitle"),
    @NamedQuery(name = "Exams.findByDescription", query = "SELECT e FROM Exams e WHERE e.description = :description"),
    @NamedQuery(name = "Exams.findByExamDate", query = "SELECT e FROM Exams e WHERE e.examDate = :examDate"),
    @NamedQuery(name = "Exams.findByDuration", query = "SELECT e FROM Exams e WHERE e.duration = :duration")})
public class Exams implements Serializable {
    @Basic(optional = false)
    @NotNull
    @Column(name = "EXAM_DATE")
    @Temporal(TemporalType.DATE)
    private Date examDate;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 8)
    @Column(name = "DURATION")
    private String duration;
    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "EXAM_TITLE")
    private String examTitle;
    @Size(max = 500)
    @Column(name = "DESCRIPTION")
    private String description;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "examTitle")
    private Collection<Questions> questionsCollection;

    public Exams() {
    }

    public Exams(String examTitle) {
        this.examTitle = examTitle;
    }

    public Exams(String examTitle, Date examDate, String duration) {
        this.examTitle = examTitle;
        this.examDate = examDate;
        this.duration = duration;
    }

    public String getExamTitle() {
        return examTitle;
    }

    public void setExamTitle(String examTitle) {
        this.examTitle = examTitle;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Date getExamDate() {
        return examDate;
    }

    public void setExamDate(Date examDate) {
        this.examDate = examDate;
    }

    @XmlTransient
    public Collection<Questions> getQuestionsCollection() {
        return questionsCollection;
    }

    public void setQuestionsCollection(Collection<Questions> questionsCollection) {
        this.questionsCollection = questionsCollection;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (examTitle != null ? examTitle.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Exams)) {
            return false;
        }
        Exams other = (Exams) object;
        if ((this.examTitle == null && other.examTitle != null) || (this.examTitle != null && !this.examTitle.equals(other.examTitle))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "jpa.entities.Exams[ examTitle=" + examTitle + " ]";
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }
    
}
