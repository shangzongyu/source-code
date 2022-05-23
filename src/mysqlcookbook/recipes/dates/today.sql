# today.sql

# Date calculations relative to today.  (Can be generalized to any date,
# of course).

# What day of the week is it today (numeric and name forms)?

SELECT DAYOFWEEK(CURDATE()), DAYNAME(CURDATE());

# What's the date on Sunday of this week?
# Sunday is day 1 in DAYOFWEEK() terms.  Compute it by
# subtracting DAYOFWEEK(today)-1 from today.  For other days
# of the week, subtract:
# Monday: DAYOFWEEK(today)-2
# Tuesday: DAYOFWEEK(today)-3
# Wednesday: DAYOFWEEK(today)-4
# ...
# Saturday: DAYOFWEEK(today)-7

SELECT
  CURDATE() AS Today,
  DAYNAME(CURDATE()) AS 'Day of week',
  DATE_SUB(CURDATE(), INTERVAL (DAYOFWEEK(CURDATE()) - 1) DAY)
  AS 'Sunday',
  DATE_SUB(CURDATE(), INTERVAL (DAYOFWEEK(CURDATE()) - 2) DAY)
  AS 'Monday',
  DATE_SUB(CURDATE(), INTERVAL (DAYOFWEEK(CURDATE()) - 3) DAY)
  AS 'Tuesday',
  DATE_SUB(CURDATE(), INTERVAL (DAYOFWEEK(CURDATE()) - 7) DAY)
  AS 'Saturday'
;

# What date is next Friday (Friday of the upcoming week)?
# Determine two ways:
# - Determine Sunday of this week, then add 12 days
# - Determine Sunday of next week, then add 5 days

SELECT
  CURDATE() AS Today,
  DAYNAME(CURDATE()) AS 'Day of week',
  DATE_ADD(
    DATE_SUB(CURDATE(), INTERVAL (DAYOFWEEK(CURDATE()) - 1) DAY),
    INTERVAL 12 DAY)
  AS 'Next Friday'
;

SELECT
  CURDATE() AS Today,
  DAYNAME(CURDATE()) AS 'Day of week',
  DATE_ADD(
    DATE_ADD(CURDATE(), INTERVAL (8 - DAYOFWEEK(CURDATE())) DAY),
    INTERVAL 5 DAY)
  AS 'Next Friday'
;
