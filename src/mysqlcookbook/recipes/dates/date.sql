# date.sql

# How to determine the day of the week for a given date (for example,
# to find out what day of the week you were born on or when an event
# took place)

SELECT
  '1776-07-04' AS date,
  DAYOFWEEK('1776-07-04') AS number,
  DAYNAME('1776-07-04') AS name
;
SELECT
  '1956-03-29' AS date,
  DAYOFWEEK('1956-03-29') AS number,
  DAYNAME('1956-03-29') AS name
;

# Determine how many days in the month for a particular date

SET @x:='1956-03-29';
SELECT @x;

# Determine first day of month
SELECT CONCAT(YEAR(@x),'-',MONTH(@x),'-01')
;
# Determine first day of following month
SELECT DATE_ADD(CONCAT(YEAR(@x),'-',MONTH(@x),'-01'),INTERVAL 1 MONTH)
;
# Determine the day before that
SELECT DATE_SUB(
        DATE_ADD(CONCAT(YEAR(@x),'-',MONTH(@x),'-01'),INTERVAL 1 MONTH),
        INTERVAL 1 DAY)
;
# Find the days part of that
SELECT DAYOFMONTH(
        DATE_SUB(
          DATE_ADD(CONCAT(YEAR(@x),'-',MONTH(@x),'-01'),INTERVAL 1 MONTH),
          INTERVAL 1 DAY)
        )
;
