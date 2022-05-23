# rainfall.sql

# rainfall table: each record indicates date of measurement and amount
# of precipitation on that day.

# This file sets up the table and runs a self join to calculate
# running totals and averages for amount of precipitation each
# day, assuming no missing days.  rainfall2.sql shows the calculations
# if missing days are permitted.

DROP TABLE IF EXISTS rainfall;
#@ _CREATE_TABLE_
CREATE TABLE rainfall
(
  date    DATE NOT NULL,
  precip  FLOAT(10,2) NOT NULL,
  PRIMARY KEY(date)
);
#@ _CREATE_TABLE_

INSERT INTO rainfall (date, precip)
  VALUES
    ('2014-06-01', 1.5),
    ('2014-06-02', 0),
    ('2014-06-03', 0.5),
    ('2014-06-04', 0),
    ('2014-06-05', 1.0)
;

SELECT * FROM rainfall;

# calculate cumulative precipation per day, assuming no missing days

SELECT t1.date, t1.precip AS 'daily precip',
SUM(t2.precip) AS 'cum. precip'
FROM rainfall AS t1, rainfall AS t2
WHERE t1.date >= t2.date
GROUP BY t1.date, t1.precip;

# Add columns to show elapsed days and running average of amount of
# precipitation, assuming no missing days

SELECT t1.date, t1.precip AS 'daily precip',
SUM(t2.precip) AS 'cum. precip',
COUNT(t2.precip) AS days,
AVG(t2.precip) AS 'avg. precip'
FROM rainfall AS t1, rainfall AS t2
WHERE t1.date >= t2.date
GROUP BY t1.date, t1.precip;
