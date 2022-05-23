# time_val.sql

DROP TABLE IF EXISTS time_val;
CREATE TABLE time_val
(
  id  INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  t1  TIME,
  t2  TIME
);

INSERT INTO time_val (t1,t2) VALUES('15:00:00','15:00:00');
INSERT INTO time_val (t1,t2) VALUES('05:01:30','02:30:20');
INSERT INTO time_val (t1,t2) VALUES('12:30:20','17:30:45');

SELECT * FROM time_val;
