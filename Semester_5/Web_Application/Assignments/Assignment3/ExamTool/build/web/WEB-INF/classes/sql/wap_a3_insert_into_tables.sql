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

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Horse Exam'
                      ,'If a horse died, would it still be alive?'
                      ,'yes'
                      ,'no'
                      ,'no'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,c,d,e,answer,q_type)
                VALUES('Horse Exam'
                      ,'How many legs does a horse have?'
                      ,'1'
                      ,'2'
                      ,'3'
                      ,'4'
                      ,'5'
                      ,'4'
                      ,'MC_5');

INSERT INTO Questions (exam_title,question,a,b,c,d,e,answer,q_type)
                VALUES('Horse Exam'
                      ,'What do horses eat most?'
                      ,'Lead'
                      ,'Giraffes'
                      ,'Peanut Butter'
                      ,'Carrots'
                      ,'Pencils'
                      ,'Carrots'
                      ,'MC_5');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Horse Exam'
                      ,'What colour of pony should I get?'
                      ,'Blue'
                      ,'Black'
                      ,'Rainbow'
                      ,'Orange'
                      ,'Rainbow'
                      ,'MC_4');

INSERT INTO Exams (exam_title,description,exam_date,duration) 
            VALUES('Long and Pointless Exam'
                  ,'An exam about pointless and uncool things. Should be 30 questions, depending on how lazy I am'
                  ,CURRENT_DATE
                  ,'00:30:00');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'How many days are in September?'
                      ,'28'
                      ,'30'
                      ,'31'
                      ,'32'
                      ,'30'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'How many hours are in a day?'
                      ,'23'
                      ,'12'
                      ,'24'
                      ,'25'
                      ,'24'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,e,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'What is the first day of the week?'
                      ,'Sunday'
                      ,'Monday'
                      ,'Tuesday'
                      ,'Wednesday'
                      ,'Thursday'
                      ,'Sunday'
                      ,'MC_5');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'What is the best hockey team ever?'
                      ,'St. Louis Blues'
                      ,'Chicago Blackhawks'
                      ,'Nashville Predators'
                      ,'Ottawa Senators'
                      ,'Ottawa Senators'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Who is the prime minister of Canada?'
                      ,'Willy Collins'
                      ,'Nicolas Castilloux'
                      ,'Stephen Harper'
                      ,'David Jansen'
                      ,'Stephen Harper'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,e,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'What is the greatest city on Earth?'
                      ,'Ottawa'
                      ,'Las Vegas'
                      ,'Washington'
                      ,'New York'
                      ,'Toronto'
                      ,'Ottawa'
                      ,'MC_5');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'How many questions am I supposed to have in the database?'
                      ,'20'
                      ,'30'
                      ,'40'
                      ,'50'
                      ,'30'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'What is a sandwich made of?'
                      ,'eggs and milk'
                      ,'lemon and sugar'
                      ,'bread and meat'
                      ,'cows and horses'
                      ,'bread and meat'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,e,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'What fuel do you put in a car?'
                      ,'eggs'
                      ,'hot dogs'
                      ,'straw'
                      ,'animals'
                      ,'gasoline'
                      ,'gasoline'
                      ,'MC_5');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'If an animal were to get stuck in a tree, what would it likely be?'
                      ,'dog'
                      ,'cat'
                      ,'weasel'
                      ,'muskrat'
                      ,'cat'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Money is hard to come by. How much money would you like?'
                      ,'one dollar'
                      ,'ten dollars'
                      ,'1 hundred dollars'
                      ,'1 million dollars'
                      ,'1 million dollars'
                      ,'MC_4');

INSERT INTO Questions (exam_title,question,a,b,c,d,e,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'What is on a pepperoni pizza?'
                      ,'pepperoni'
                      ,'bacon'
                      ,'mushrooms'
                      ,'pineapple'
                      ,'oranges'
                      ,'pepperoni'
                      ,'MC_5');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'I like fudge.'
                      ,'true'
                      ,'false'
                      ,'true'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'The sun orbits the earth.'
                      ,'false'
                      ,'true'
                      ,'false'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'3 + 3 = 7'
                      ,'true'
                      ,'false'
                      ,'false'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Water contains two hydrogen atoms, and one oxygen atom.'
                      ,'true'
                      ,'false'
                      ,'true'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Orange juice contains a large amount of vitamin k'
                      ,'true'
                      ,'false'
                      ,'false'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Night occurs when the sun is up.'
                      ,'false'
                      ,'true'
                      ,'false'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Pizza is a form of pie.'
                      ,'true'
                      ,'false'
                      ,'true'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Socks warm your hands.'
                      ,'false'
                      ,'true'
                      ,'false'
                      ,'MC_2');

INSERT INTO Questions (exam_title,question,a,b,answer,q_type)
                VALUES('Long and Pointless Exam'
                      ,'Salad is delicious.'
                      ,'true'
                      ,'false'
                      ,'true'
                      ,'MC_2');










