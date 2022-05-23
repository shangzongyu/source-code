# expt.sql

DROP TABLE IF EXISTS expt;
#@ _CREATE_TABLE_
CREATE TABLE expt
(
  subject VARCHAR(10),
  test    VARCHAR(5),
  score INT,
  PRIMARY KEY(subject, test)
);
#@ _CREATE_TABLE_

INSERT INTO expt (subject,test,score) VALUES('Jane','A',47);
INSERT INTO expt (subject,test,score) VALUES('Jane','B',50);
INSERT INTO expt (subject,test,score) VALUES('Jane','C',NULL);
INSERT INTO expt (subject,test,score) VALUES('Jane','D',NULL);
INSERT INTO expt (subject,test,score) VALUES('Marvin','A',52);
INSERT INTO expt (subject,test,score) VALUES('Marvin','B',45);
INSERT INTO expt (subject,test,score) VALUES('Marvin','C',53);
INSERT INTO expt (subject,test,score) VALUES('Marvin','D',NULL);

SELECT * FROM expt;
