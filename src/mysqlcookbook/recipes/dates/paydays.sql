# paydays.sql

# paydays(year): Find all the paydays of the given year, assuming that
# they fall on the 2nd and 4th Thursdays of each month

# Uses a user-defined variable named @first.

DROP PROCEDURE IF EXISTS paydays;
delimiter $$
CREATE PROCEDURE paydays (year INT)
BEGIN
  DECLARE month INT DEFAULT 1;
  PREPARE stmt FROM '
    SELECT
      DATE_FORMAT(?,''%m/%Y'') AS ''MM/YYYY'',
      DATE_ADD(DATE_ADD(?,INTERVAL 5-DAYOFWEEK(?) DAY),
               INTERVAL IF(DAYOFWEEK(?) <= 5, 7, 14) DAY)
        AS ''2nd Thursday'',
      DATE_ADD(DATE_ADD(?,INTERVAL 5-DAYOFWEEK(?) DAY),
               INTERVAL IF(DAYOFWEEK(?) <= 5, 21, 28) DAY)
        AS ''4th Thursday''
  ';
  # Run a loop to construct the first day of the month for each month.
  # Run a query based on each first-of-month date.
  WHILE month <= 12 DO
    SET @first = CONCAT(year,'-',month,'-01');
    EXECUTE stmt
      USING @first, @first, @first, @first, @first, @first, @first;
    SET month = month + 1;
  END WHILE;
  DEALLOCATE PREPARE stmt;
END;
$$

delimiter ;

CALL paydays(2014);
