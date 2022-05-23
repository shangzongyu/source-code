# profile.sql
# Character names are from "The Greater Trumps," Charles Williams.

DROP TABLE IF EXISTS profile;
#@ _CREATE_TABLE_
CREATE TABLE profile
(
  id    INT UNSIGNED NOT NULL AUTO_INCREMENT,
  name  VARCHAR(20) NOT NULL,
  birth DATE,
  color ENUM('blue','red','green','brown','black','white'),
  foods SET('lutefisk','burrito','curry','eggroll','fadge','pizza'),
  cats  INT,
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_

INSERT INTO profile
  VALUES
    (NULL,'Sybil','1970-04-13','black','lutefisk,pizza,fadge',0),
    (NULL,'Nancy','1969-09-30','white','curry,eggroll,burrito',3),
    (NULL,'Ralph','1973-11-02','red','pizza,eggroll',4),
    (NULL,'Lothair','1963-07-04','blue','burrito,curry',5),
    (NULL,'Henry','1965-02-14','red','curry,fadge',1),
    (NULL,'Aaron','1968-09-17','green','fadge,lutefisk',1),
    (NULL,'Joanna','1952-08-20','green','fadge,lutefisk',0),
    (NULL,'Stephen','1960-05-01','white','pizza,burrito',0)
;

SELECT * FROM profile;
