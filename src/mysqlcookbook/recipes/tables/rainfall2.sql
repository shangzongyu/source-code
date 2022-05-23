# rainfall2.sql

# rainfall table: each record indicates date of measurement and amount
# of precipitation on that day.

# See also the rainfall.sql file.

SOURCE rainfall.sql;

# calculate running total and average, permitting missing days

# create a couple of "missing" days.  The precip values are zero,
# so the cumulative totals and averages for the days that remain
# should be the same as those computed above.  (That makes it easy
# to compare the result from the following SELECT with the result
# from the SELECT in rainfall.sql.)

DELETE FROM rainfall WHERE precip = 0;

SELECT t1.date, t1.precip AS 'daily precip',
SUM(t2.precip) AS 'cum. precip',
DATEDIFF(MAX(t2.date),MIN(t2.date)) + 1 AS days,
SUM(t2.precip) / (TO_DAYS(MAX(t2.date)) - TO_DAYS(MIN(t2.date)) + 1)
AS 'avg. precip'
FROM rainfall AS t1, rainfall AS t2
WHERE t1.date >= t2.date
GROUP BY t1.date, t1.precip;
