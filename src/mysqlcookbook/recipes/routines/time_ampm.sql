DROP FUNCTION IF EXISTS time_ampm;
delimiter $$
#@ _FRAG_
CREATE FUNCTION time_ampm (t TIME)
RETURNS VARCHAR(13) # mm:dd:ss {a.m.|p.m.} format
DETERMINISTIC
RETURN CONCAT(LEFT(TIME_FORMAT(t, '%r'), 9),
              IF(TIME_TO_SEC(t) < 12*60*60, 'a.m.', 'p.m.'));
#@ _FRAG_
$$
delimiter ;
SET @t = '00:00:00';
SELECT @t, TIME_FORMAT(@t, '%r'), time_ampm(@t);
SET @t = '00:00:01';
SELECT @t, TIME_FORMAT(@t, '%r'), time_ampm(@t);
SET @t = '12:00:00';
SELECT @t, TIME_FORMAT(@t, '%r'), time_ampm(@t);
SET @t = '12:00:01';
SELECT @t, TIME_FORMAT(@t, '%r'), time_ampm(@t);
