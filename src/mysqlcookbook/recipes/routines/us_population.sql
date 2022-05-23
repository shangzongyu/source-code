# us_population.sql: Illustrate cursor-based fetch loop that computes total
# US population.

DROP PROCEDURE IF EXISTS us_population;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE us_population()
BEGIN
  DECLARE done BOOLEAN DEFAULT FALSE;
  DECLARE state_pop, total_pop BIGINT DEFAULT 0;
  DECLARE cur CURSOR FOR SELECT pop FROM states;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

  OPEN cur;
  fetch_loop: LOOP
    FETCH cur INTO state_pop;
    IF done THEN
      LEAVE fetch_loop;
    END IF;
    SET total_pop = total_pop + state_pop;
  END LOOP;
  CLOSE cur;
  SELECT total_pop AS 'Total US Population';
END;
#@ _DEFINITION_
$$

delimiter ;
SELECT 'Population calculated by us_population()' AS Message;
CALL us_population();

# Test whether we get the same value using a direct aggregate query

SELECT 'Population calculated by aggregate query' AS Message;
SELECT SUM(pop) FROM states;
