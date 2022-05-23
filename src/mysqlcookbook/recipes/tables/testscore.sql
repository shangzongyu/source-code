# testscore.sql

DROP TABLE IF EXISTS testscore;
#@ _CREATE_TABLE_
CREATE TABLE testscore
(
  subject INT UNSIGNED NOT NULL AUTO_INCREMENT,
  age     INT UNSIGNED NOT NULL,
  sex     ENUM('M','F') NOT NULL,
  score   INT,
  PRIMARY KEY (subject)
);
#@ _CREATE_TABLE_

INSERT INTO testscore (age,sex,score)
  VALUES
  (5,'M',5),
  (5,'M',4),
  (5,'F',6),
  (5,'F',7),
  (6,'M',8),
  (6,'M',9),
  (6,'F',4),
  (6,'F',6),
  (7,'M',8),
  (7,'M',6),
  (7,'F',9),
  (7,'F',7),
  (8,'M',9),
  (8,'M',6),
  (8,'F',7),
  (8,'F',10),
  (9,'M',9),
  (9,'M',7),
  (9,'F',10),
  (9,'F',9)
;

SELECT subject, age, sex, score FROM testscore ORDER BY subject;
