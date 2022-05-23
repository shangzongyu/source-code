# avg_legs.sql

DROP FUNCTION IF EXISTS avg_legs;
#@ _DELIMITER_
delimiter $$
#@ _DEFINITION_
CREATE FUNCTION avg_legs()
RETURNS FLOAT READS SQL DATA
BEGIN
  DECLARE f FLOAT;
  SELECT AVG(legs) FROM limbs INTO f;
  RETURN f;
END;
#@ _DEFINITION_
$$
delimiter ;
SELECT avg_legs();
#@ _DELIMITER_
