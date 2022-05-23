# avg_mail_size.sql

# This version returns the average mail message size over all users

DROP FUNCTION IF EXISTS avg_mail_size;
#@ _DEFINITION_1_
CREATE FUNCTION avg_mail_size()
RETURNS FLOAT READS SQL DATA
RETURN (SELECT AVG(size) FROM mail);
#@ _DEFINITION_1_
SELECT avg_mail_size();

# This version returns the average mail message size for the user named
# in the argument, or the average size over all users if the argument
# is NULL.

DROP FUNCTION IF EXISTS avg_mail_size;
delimiter $$
#@ _DEFINITION_2_
CREATE FUNCTION avg_mail_size(user VARCHAR(8))
RETURNS FLOAT READS SQL DATA
BEGIN
  DECLARE avg FLOAT;
  IF user IS NULL
  THEN # average message size over all users
    SET avg = (SELECT AVG(size) FROM mail);
  ELSE # average message size for given user
    SET avg = (SELECT AVG(size) FROM mail WHERE srcuser = user);
  END IF;
  RETURN avg;
END;
#@ _DEFINITION_2_
$$
delimiter ;
SELECT avg_mail_size(NULL), avg_mail_size('barb');
