# contact_trigger.sql

# Use BEFORE INSERT trigger to reject bad data, preprocess other data


DROP TABLE IF EXISTS contact_info;
#@ _CREATE_TABLE_
CREATE TABLE contact_info
(
  id     INT NOT NULL AUTO_INCREMENT,
  name   VARCHAR(30),   # state of residence
  state  CHAR(2),       # state of residence
  email  VARCHAR(50),   # email address
  url    VARCHAR(255),  # web address
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_

# Set up a BEFORE INSERT trigger that:
# * Rejects state codes not in the states table
# * Rejects email addresses not containing a '@' character
# * Strips from url any leading http://

delimiter $$
#@ _BEFORE_INSERT_TRIGGER_
CREATE TRIGGER bi_contact_info BEFORE INSERT ON contact_info
FOR EACH ROW
BEGIN
  IF (SELECT COUNT(*) FROM states WHERE abbrev = NEW.state) = 0 THEN
    SIGNAL SQLSTATE 'HY000'
           SET MYSQL_ERRNO = 1525, MESSAGE_TEXT = 'invalid state code';
  END IF;
  IF INSTR(NEW.email,'@') = 0 THEN
    SIGNAL SQLSTATE 'HY000'
           SET MYSQL_ERRNO = 1525, MESSAGE_TEXT = 'invalid email address';
  END IF;
  SET NEW.url = TRIM(LEADING 'http://' FROM NEW.url);
END;
#@ _BEFORE_INSERT_TRIGGER_
$$

delimiter ;

INSERT INTO contact_info (name,state,email,url)
VALUES('Jen','NY','jen@example.com','http://www.example.com');
INSERT INTO contact_info (name,state,email,url)
VALUES('Jen','XX','jen@example.com','http://www.example.com');
INSERT INTO contact_info (name,state,email,url)
VALUES('Jen','NY','jen','http://www.example.com');
SELECT * FROM contact_info;
