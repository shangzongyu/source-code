# name.sql

# Create a table with first and last names

DROP TABLE IF EXISTS name;
#@ _CREATE_TABLE_
CREATE TABLE name
(
  last_name   CHAR(20),
  first_name  CHAR(20),
  PRIMARY KEY(last_name, first_name)
);
#@ _CREATE_TABLE_

INSERT INTO name (first_name,last_name) VALUES('Kevin','Brown');
INSERT INTO name (first_name,last_name) VALUES('Vida','Blue');
INSERT INTO name (first_name,last_name) VALUES('Pete','Gray');
INSERT INTO name (first_name,last_name) VALUES('Devon','White');
INSERT INTO name (first_name,last_name) VALUES('Rondell','White');

SELECT * FROM name;
