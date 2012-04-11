package jpa.entities;

import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import jpa.entities.Questions;

@Generated(value="EclipseLink-2.3.0.v20110604-r9504", date="2012-04-11T07:43:32")
@StaticMetamodel(Exams.class)
public class Exams_ { 

    public static volatile SingularAttribute<Exams, Date> examDate;
    public static volatile SingularAttribute<Exams, String> duration;
    public static volatile SingularAttribute<Exams, String> description;
    public static volatile SingularAttribute<Exams, String> examTitle;
    public static volatile CollectionAttribute<Exams, Questions> questionsCollection;

}