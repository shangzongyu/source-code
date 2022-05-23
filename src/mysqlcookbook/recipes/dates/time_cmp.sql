# time_cmp.sql

# Find TIME values that occur from 9 AM to 2PM

SELECT t1
FROM time_val
#@ _9AM_2PM_1_
WHERE t1 BETWEEN '09:00:00' AND '14:00:00';
#@ _9AM_2PM_1_

SELECT t1
FROM time_val
#@ _9AM_2PM_2_
WHERE HOUR(t1) BETWEEN 9 AND 14;
#@ _9AM_2PM_2_

# The HOUR() method works not only with TIME, but DATETIME and TIMESTAMP.
# Example with DATETIME:

SELECT dt
FROM datetime_val
WHERE HOUR(dt) BETWEEN 9 AND 14;
