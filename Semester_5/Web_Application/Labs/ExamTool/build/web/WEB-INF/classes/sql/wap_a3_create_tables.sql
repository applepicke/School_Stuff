DROP TABLE Exams;
DROP TABLE Questions;
DROP TABLE Users;

CREATE TABLE Exams (
        examID      INTEGER     NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1, INCREMENT BY 1)
       ,q_listID    INTEGER     NOT NULL 
       ,title       VARCHAR(50) NOT NULL
       ,description VARCHAR(500)
       ,examDate    date        NOT NULL
       ,duration    time        NOT NULL
       
       ,CONSTRAINT pk_examID    PRIMARY KEY ( examID )
       ,CONSTRAINT uq_title     UNIQUE      ( title )
);

CREATE TABLE Questions (
        questionID  INTEGER         NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1, INCREMENT BY 1)
       ,q_listID    INTEGER         NOT NULL 
       ,question    varchar(500)    NOT NULL
       ,a           varchar(50)     NOT NULL
       ,b           varchar(50)     NOT NULL
       ,c           varchar(50)
       ,d           varchar(50)
       ,e           varchar(50)
       ,q_type      varchar(50)     NOT NULL

       ,CONSTRAINT pk_questionID    PRIMARY KEY ( questionID )
       ,CONSTRAINT fk_examID        FOREIGN KEY ( examID ) REFERENCES Exams ( examID )
       ,CONSTRAINT uq_question      UNIQUE ( question )
);

CREATE TABLE Users (
        username    VARCHAR(50)     NOT NULL
       ,password    VARCHAR(25)     NOT NULL
       ,


)