# show_part_of_day.sql

DROP PROCEDURE IF EXISTS show_part_of_day;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE show_part_of_day()
BEGIN
  DECLARE cur_time, day_part TEXT;
  SET cur_time = CURTIME();
  IF cur_time < '12:00:00' THEN
    SET day_part = 'morning';
  ELSEIF cur_time = '12:00:00' THEN
    SET day_part = 'noon';
  ELSE
    SET day_part = 'afternoon or night';
  END IF;
  SELECT cur_time, day_part;
END;
#@ _DEFINITION_
$$

delimiter ;
CALL show_part_of_day();
