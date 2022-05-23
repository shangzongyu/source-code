# sibling.sql

# Date of birth for the Alkin's  children.  Used for age calculations

DROP TABLE IF EXISTS sibling;
CREATE TABLE sibling
(
  name  CHAR(20),
  birth DATE,
  PRIMARY KEY(name)
);

INSERT INTO sibling (name,birth) VALUES('Ilayda','2002-12-17');
INSERT INTO sibling (name,birth) VALUES('Lara','2009-06-03');

SELECT * FROM sibling;

# Age calculations

SELECT name,DATE_FORMAT(birth,'%Y-%m-%d') as dob
    , DATE_FORMAT(NOW(),'%Y-%m-%d') as today
    , TIMESTAMPDIFF( YEAR, birth, NOW() ) as age_years
    , TIMESTAMPDIFF( MONTH, birth, NOW() ) % 12 as age_months
    , FLOOR( TIMESTAMPDIFF( DAY, birth, now() ) % 30.4375 ) as age_days
 FROM sibling; 

SELECT name, birth, '2009-06-09' AS 'Lara\'s birth',
    TIMESTAMPDIFF( YEAR, birth,'2009-06-09' ) as age_years,
    TIMESTAMPDIFF( MONTH, birth,'2009-06-09' ) % 12 as age_months,
    FLOOR( TIMESTAMPDIFF( DAY, birth,'2009-06-09' ) % 30.4375 ) as age_days
 FROM sibling WHERE name <> 'Lara';
