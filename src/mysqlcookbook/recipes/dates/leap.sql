# leap.sql

# Illustrate leap year calculation; also show how to combine it with
# ELT() to perform days-in-month() calculations

SELECT
d,
#@ _LEAP_TEST_THUMB_
YEAR(d) % 4 = 0
#@ _LEAP_TEST_THUMB_
AS 'rule-of-thumb test',
#@ _LEAP_TEST_FULL_
(YEAR(d) % 4 = 0) AND ((YEAR(d) % 100 <> 0) OR (YEAR(d) % 400 = 0))
#@ _LEAP_TEST_FULL_
AS 'complete test'
FROM date_val
;

SELECT
d,
#@ _DAYS_IN_MONTH_
ELT(MONTH(d),
31,
IF((YEAR(d) % 4 = 0) AND ((YEAR(d) % 100 <> 0) OR (YEAR(d) % 400 = 0)),29,28),
31,30,31,30,31,31,30,31,30,31)
#@ _DAYS_IN_MONTH_
AS 'days in month'
FROM date_val;
