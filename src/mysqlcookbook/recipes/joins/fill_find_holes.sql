# fill_find_holes.sql

# Produce a master-detail summary using a reference table to make sure
# all categories appear in the summary.

# Problem: Summarize rows in the driver_log table to show how many
# drivers were on the road each day.

# First try:

SELECT trav_date, COUNT(trav_date) AS drivers
FROM driver_log GROUP BY trav_date ORDER BY trav_date;

# That doesn't work, because it doesn't show entries for dates on
# which no drivers were active.  To fix that, create a reference table
# that lists each date in the date range represented in the driver_log
# table, and LEFT JOIN it to the driver_log table.

DROP TABLE IF EXISTS dates;
CREATE TABLE dates (d DATE);
INSERT INTO dates (d)
VALUES('2014-07-26'),('2014-07-27'),('2014-07-28'),
('2014-07-29'),('2014-07-30'),('2014-07-31'),
('2014-08-01'),('2014-08-02');

SELECT dates.d, COUNT(driver_log.trav_date) AS count
FROM dates LEFT JOIN driver_log ON dates.d = driver_log.trav_date
GROUP BY d ORDER BY d;

# Now use the reference table to find holes in the date category
# list (dates on which no driver was active).

SELECT dates.d AS d, COUNT(driver_log.trav_date) AS count
FROM dates LEFT JOIN driver_log ON dates.d = driver_log.trav_date
GROUP BY d
HAVING count = 0;

# A simpler approach: Recognize that it's necessary only to look for
# reference table rows not matched by any driver_log table rows.  It's
# not necessary to actually summarize the driver_log records.

SELECT dates.d
FROM dates LEFT JOIN driver_log ON dates.d = driver_log.trav_date
WHERE driver_log.trav_date IS NULL;
