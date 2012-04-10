DELETE FROM Questions;
DELETE FROM Exams;
DELETE FROM Users;

INSERT INTO Users (username, password) VALUES ('hurdleg','password');
INSERT INTO Users (username, password) VALUES ('willy','willy');

INSERT INTO Exams (exam_title,description,exam_date,duration) 
            VALUES('Horse Exam'
                  ,'A sweet exam about horses.'
                  ,CURRENT_DATE
                  ,'00:01:00');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Horse Exam'
                      ,'A brown horse is black.'
                      ,'true'
                      ,'false'
                      ,'false'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Horse Exam'
                      ,'How many tails does a horse have?'
                      ,'1'
                      ,'2'
                      ,'3'
                      ,'4'
                      ,'1'
                      ,'MC_4');