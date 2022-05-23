# date_calc.sql

# Various date-calculation recipes.  These use the date_val table
# that is set up by date_val.sql in the tables directory.


# Equivalence of DATE_ADD() and DATE_SUB()

SELECT d,
#@ _DATE_ADD_DATE_SUB_EQUIVALENCE_1_
  DATE_ADD(d,INTERVAL -3 MONTH)
#@ _DATE_ADD_DATE_SUB_EQUIVALENCE_1_
  ,
#@ _DATE_ADD_DATE_SUB_EQUIVALENCE_2_
  DATE_SUB(d,INTERVAL 3 MONTH)
#@ _DATE_ADD_DATE_SUB_EQUIVALENCE_2_
  FROM date_val
;

# Special case for first day of month for given date, then
# general case for any number of months from now, illustrated using
# -1 and 1 for previous/next month. (To calculate first for any other
# month, substitute the proper value for the months unit.)

SELECT d,
#@ _FIRST_OF_MONTH_WITH_DAYOFMONTH_
DATE_SUB(d,INTERVAL DAYOFMONTH(d) - 1 DAY)
#@ _FIRST_OF_MONTH_WITH_DAYOFMONTH_
AS '1st_of_month',
#@ _FIRST_OF_PREV_MONTH_WITH_DAYOFMONTH_
DATE_ADD(DATE_SUB(d,INTERVAL DAYOFMONTH(d) - 1 DAY),INTERVAL -1 MONTH)
#@ _FIRST_OF_PREV_MONTH_WITH_DAYOFMONTH_
AS '1st_of_prev_month',
#@ _FIRST_OF_NEXT_MONTH_WITH_DAYOFMONTH_
DATE_ADD(DATE_SUB(d,INTERVAL DAYOFMONTH(d) - 1 DAY),INTERVAL 1 MONTH)
#@ _FIRST_OF_NEXT_MONTH_WITH_DAYOFMONTH_
AS '1st_of_next_month'
FROM date_val
;

# First day of month methods using CONCAT():
# Concat year and month of date with '01' as day.
# The following statement shows the concat by itself to show that months
# sometimes end up as a single digit; then it shows how to fix that
# using either using LPAD() or using DATE_ADD() and adding 0 days to
# convert the string to ISO format. The last method avoids CONCAT()
# entirely.

SELECT d,
#@ _FIRST_OF_MONTH_WITH_CONCAT
CONCAT(YEAR(d),'-',MONTH(d),'-01')
#@ _FIRST_OF_MONTH_WITH_CONCAT
AS '1st_of_month',
#@ _FIRST_OF_MONTH_WITH_LPAD_
CONCAT(YEAR(d),'-',LPAD(MONTH(d),2,'0'),'-01')
#@ _FIRST_OF_MONTH_WITH_LPAD_
AS '1st_of_month2',
#@ _FIRST_OF_MONTH_WITH_DATE_ADD_
DATE_ADD(CONCAT(YEAR(d),'-',MONTH(d),'-01'),INTERVAL 0 DAY)
#@ _FIRST_OF_MONTH_WITH_DATE_ADD_
AS '1st_of_month3'
FROM date_val
;

# Last day of month: Use LAST_DAY()

SELECT d, LAST_DAY(d) AS 'last_of_month' FROM date_val;


# First day of previous month: apply the "first of month" method to
# the given month minus a day

SELECT d,
#@ _FIRST_OF_PREV_MONTH_WITH_DAYOFMONTH_
DATE_SUB(DATE_SUB(d,INTERVAL DAYOFMONTH(d) - 1 DAY), INTERVAL 1 MONTH)
#@ _FIRST_OF_PREV_MONTH_WITH_DAYOFMONTH_
AS '1st_of_prev_month',
#@ _FIRST_OF_PREV_MONTH_WITH_CONCAT
CONCAT(
    YEAR(DATE_SUB(d,INTERVAL 1 MONTH)),
    '-',
    MONTH(DATE_SUB(d,INTERVAL 1 MONTH)),
    '-01')
#@ _FIRST_OF_PREV_MONTH_WITH_CONCAT
AS '1st_of_prev_month2',
#@ _FIRST_OF_PREV_MONTH_WITH_DATE_ADD_
DATE_ADD(
    CONCAT(
        YEAR(DATE_SUB(d,INTERVAL 1 MONTH)),
        '-',
        MONTH(DATE_SUB(d,INTERVAL 1 MONTH)),
        '-01'),
    INTERVAL 0 DAY)
#@ _FIRST_OF_PREV_MONTH_WITH_DATE_ADD_
AS '1st_of_prev_month3'
FROM date_val
;

# Last day of previous month: shift back a month, then use LAST_DAY()

SELECT d,
LAST_DAY(DATE_ADD(d,INTERVAL -1 MONTH))
AS 'last_of_prev_month'
FROM date_val
;

# First day of next month:
# - find first of current month, add 1 month (two ways)

SELECT d,
#@ _FIRST_OF_NEXT_MONTH_WITH_DAYOFMONTH
DATE_ADD(DATE_SUB(d,INTERVAL DAYOFMONTH(d) - 1 DAY),INTERVAL 1 MONTH)
#@ _FIRST_OF_NEXT_MONTH_WITH_DAYOFMONTH
AS '1st_of_next_month1',
#@ _FIRST_OF_NEXT_MONTH_WITH_CONCAT
DATE_ADD(CONCAT(YEAR(d),'-',MONTH(d),'-01'),INTERVAL 1 MONTH)
#@ _FIRST_OF_NEXT_MONTH_WITH_CONCAT
AS '1st_of_next_month2'
FROM date_val
;

# Last day of next month: shift forward a month, then use LAST_DAY()

SELECT d,
LAST_DAY(DATE_ADD(d,INTERVAL 1 MONTH))
AS 'last_of_next_month'
FROM date_val
;
