DROP TABLE Questions;
DROP TABLE Exams;
DROP TABLE Users;

CREATE TABLE Exams (
        exam_title  VARCHAR(50) NOT NULL
       ,description VARCHAR(500)
       ,exam_date   DATE        NOT NULL
       ,duration    TIME        NOT NULL
       
       ,CONSTRAINT pk_exam_title    PRIMARY KEY ( exam_title )
);

CREATE TABLE Questions (
        questionID  INTEGER         NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1, INCREMENT BY 1)
       ,exam_title  VARCHAR(50)     NOT NULL 
       ,question    VARCHAR(500)    NOT NULL
       ,a           VARCHAR(50)     NOT NULL
       ,b           VARCHAR(50)     NOT NULL
       ,c           VARCHAR(50)
       ,d           VARCHAR(50)
       ,e           VARCHAR(50)
       ,answer      VARCHAR(50)     NOT NULL
       ,q_type      VARCHAR(50)     NOT NULL

       ,CONSTRAINT pk_questionID    PRIMARY KEY ( questionID )
       ,CONSTRAINT fk_exam_title    FOREIGN KEY ( exam_title ) REFERENCES Exams ( exam_title )
       ,CONSTRAINT uq_question      UNIQUE ( question )
);

CREATE TABLE Users (
        username    VARCHAR(50)     NOT NULL
       ,password    VARCHAR(25)     NOT NULL
       
       ,CONSTRAINT pk_username  PRIMARY KEY ( username )

);