# insect.sql

# This requires the multi-row INSERT syntax

DROP TABLE IF EXISTS insect;
#@ _CREATE_TABLE_FULL_
#@ _CREATE_TABLE_PART_1_
CREATE TABLE insect
(
#@ _CREATE_TABLE_PART_1_
  id      INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id),
#@ _CREATE_TABLE_PART_2_
  name    VARCHAR(30) NOT NULL,   # type of insect
  date    DATE NOT NULL,          # date collected
  origin  VARCHAR(30) NOT NULL    # where collected
);
#@ _CREATE_TABLE_PART_2_
#@ _CREATE_TABLE_FULL_

#@ _INSERT_EXPLICIT_
INSERT INTO insect (id,name,date,origin) VALUES
  (NULL,'housefly','2014-09-10','kitchen'),
  (NULL,'millipede','2014-09-10','driveway'),
  (NULL,'grasshopper','2014-09-10','front yard'),
  (NULL,'stink bug','2014-09-10','front yard');
#@ _INSERT_EXPLICIT_

#@ _INSERT_IMPLICIT_
INSERT INTO insect (name,date,origin) VALUES
  ('cabbage butterfly','2014-09-10','garden'),
  ('ant','2014-09-10','back yard'),
  ('ant','2014-09-10','back yard'),
  ('termite','2014-09-10','kitchen woodwork');
#@ _INSERT_IMPLICIT_

SELECT * FROM insect;
