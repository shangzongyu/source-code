# multicolseq.sql

DROP TABLE IF EXISTS multicolseq;
CREATE TABLE multicolseq
(
  c CHAR(10) NOT NULL,
  i INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (i,c)
)
;

INSERT INTO multicolseq (c) VALUES('a'),('b'),('a'),('c'),('b'),('b');

SELECT * FROM multicolseq ORDER BY c, i;
