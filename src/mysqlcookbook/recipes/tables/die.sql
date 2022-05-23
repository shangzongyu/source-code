# die.sql

DROP TABLE IF EXISTS die;
#@ _CREATE_TABLE_DIE_
CREATE TABLE die (
  n INT
);
#@ _CREATE_TABLE_DIE_

# Insert values 1 through 6, corresponding to faces of a die

INSERT INTO die (n) VALUES(1);
INSERT INTO die (n) VALUES(2);
INSERT INTO die (n) VALUES(3);
INSERT INTO die (n) VALUES(4);
INSERT INTO die (n) VALUES(5);
INSERT INTO die (n) VALUES(6);

SELECT * FROM die;
