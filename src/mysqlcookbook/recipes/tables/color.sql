# color.sql

DROP TABLE IF EXISTS color;
#@ _CREATE_TABLE_
CREATE TABLE color
(
  name  CHAR(10),
  PRIMARY KEY(name)
)
#@ _CREATE_TABLE_
;

#@ _POPULATE_TABLE_
INSERT INTO color (name)
VALUES('blue'),('green'),('indigo'),('orange'),('red'),('violet'),('yellow')
#@ _POPULATE_TABLE_
;

SELECT name FROM color;
