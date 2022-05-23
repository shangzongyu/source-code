# driver_summary.sql: summarize number of drivers per day
# using the driver_log table.

# To generate the reference table (ref) used here, run the following
# command first:
#   make_date_list.pl cookbook ref d 2014-08-26 2014-09-02

# Summary that doesn't include days not present in driver_log

SELECT trav_date, COUNT(trav_date) AS drivers
FROM driver_log GROUP BY trav_date;

# Summary that does include days not present in driver_log

#@ _PER_DAY_COUNTS_
SELECT ref.d, COUNT(driver_log.trav_date) AS drivers
FROM ref LEFT JOIN driver_log ON ref.d = driver_log.trav_date
GROUP BY d;
#@ _PER_DAY_COUNTS_

# Days on which no drivers were active

#@ _NO_ONE_DRIVING_
SELECT ref.d
FROM ref LEFT JOIN driver_log ON ref.d = driver_log.trav_date
WHERE driver_log.trav_date IS NULL
ORDER BY d;
#@ _NO_ONE_DRIVING_

