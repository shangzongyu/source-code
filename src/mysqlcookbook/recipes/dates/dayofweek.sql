# dayofweek.sql

# Day-of-week calculations

# shift to Saturday, then shift forward to desired day, two-phase formula

SELECT d, DAYNAME(d) AS day,
DATE_ADD(DATE_SUB(d,INTERVAL DAYOFWEEK(d) DAY),INTERVAL 1 DAY)
AS Sunday,
DATE_ADD(DATE_SUB(d,INTERVAL DAYOFWEEK(d) DAY),INTERVAL 7 DAY)
AS Saturday
FROM date_val;

# combined formula

SELECT d, DAYNAME(d) AS day,
DATE_ADD(d,INTERVAL 1-DAYOFWEEK(d) DAY)
AS Sunday,
DATE_ADD(d,INTERVAL 7-DAYOFWEEK(d) DAY)
AS Saturday
FROM date_val;
