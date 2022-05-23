# within_week.sql

# Find birthdays in the window from a given date to that date plus 7 days.
# The trick here is to account for wraparound.

# Unfortunately, this method doesn't work *quite* properly for leap
# years, because it uses DAYOFYEAR().

#@ _SET_VARIABLES_
SET @target = CURDATE();
SET @doy1 = DAYOFYEAR(@target);
SET @doy2 = DAYOFYEAR(DATE_ADD(@target,INTERVAL 7 DAY));
#@ _SET_VARIABLES_
SELECT @target, @doy1, @doy2;

# show dates and whether they're within the window
#@ _SHOW_WHETHER_IN_WINDOW_
SELECT name, birth, DAYOFYEAR(birth), @doy1, @doy2,
IF(@doy1 < @doy2,
  DAYOFYEAR(birth) BETWEEN @doy1 AND @doy2,
  DAYOFYEAR(birth) >= @doy1 OR DAYOFYEAR(birth) <= @doy2)
  AS 'in window'
FROM profile
ORDER BY name, MONTH(birth), DAYOFMONTH(birth);
#@ _SHOW_WHETHER_IN_WINDOW_

# select only records with dates within the window
#@ _SELECT_IN_WINDOW_
SELECT name, birth, DAYOFYEAR(birth), @doy1, @doy2
FROM profile
WHERE
  IF(@doy1 < @doy2,
    DAYOFYEAR(birth) BETWEEN @doy1 AND @doy2,
    DAYOFYEAR(birth) >= @doy1 OR DAYOFYEAR(birth) <= @doy2)
ORDER BY name, MONTH(birth), DAYOFMONTH(birth);
#@ _SELECT_IN_WINDOW_

