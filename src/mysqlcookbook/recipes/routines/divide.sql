# divide.sql

# Demonstrate use of SIGNAL when divide-by-zero error occurs.

DROP FUNCTION IF EXISTS divide;
delimiter $$
#@ _DEFINITION_
CREATE FUNCTION divide(numerator FLOAT, divisor FLOAT)
RETURNS FLOAT DETERMINISTIC
BEGIN
  IF divisor = 0 THEN
    SIGNAL SQLSTATE '22012'
           SET MYSQL_ERRNO = 1365, MESSAGE_TEXT = 'unexpected 0 divisor';
  END IF;
  RETURN numerator / divisor;
END;
#@ _DEFINITION_
$$
delimiter ;

SELECT divide(1,1);
SELECT divide(0,1);
SELECT divide(1,0);
