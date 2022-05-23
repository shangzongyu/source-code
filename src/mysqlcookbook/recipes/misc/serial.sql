# serial.sql

# try the multi-part auto_increment thing

DROP TABLE IF EXISTS serial;
CREATE TABLE serial
(
  prefix  CHAR(3) NOT NULL,
  num     INT(5) ZEROFILL NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (num,prefix)
  
);

INSERT INTO serial (prefix)
    VALUES("A"),
      ("A"),
      ("B"),
      ("C"),
      ("A"),
      ("C"),
      ("C"),
      ("C");
SELECT * FROM serial ORDER BY prefix, num;

# try it with the AUTO_INCREMENT column first in the key
DROP TABLE IF EXISTS serial;
CREATE TABLE serial
(
  prefix  CHAR(3) NOT NULL,
  num     INT(5) ZEROFILL NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (num,prefix)
  
);

# try it with more than one non-AI part

INSERT INTO serial (prefix)
    VALUES("A"),
      ("A"),
      ("B"),
      ("C"),
      ("A"),
      ("C"),
      ("C"),
      ("C");
SELECT * FROM serial ORDER BY prefix, num;

DROP TABLE IF EXISTS serial;
CREATE TABLE serial
(
  prefix  CHAR(3) NOT NULL,
  prefix2 CHAR(3) NOT NULL,
  num     INT(5) ZEROFILL NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (num,prefix,prefix2)
  
);

INSERT INTO serial (prefix,prefix2)
    VALUES("A","A"),
      ("A","A"),
      ("B","A"),
      ("C","A"),
      ("A","B"),
      ("C","B"),
      ("C","A"),
      ("C","B");
SELECT * FROM serial ORDER BY prefix, prefix2, num;
