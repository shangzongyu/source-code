# trip.sql

# Trip log tables

DROP TABLE IF EXISTS trip_log;
#@ _CREATE_TABLE_
CREATE TABLE trip_log
(
  seq   INT UNSIGNED NOT NULL AUTO_INCREMENT,
  city  VARCHAR(30) NOT NULL,   # location of stop
  t     DATETIME NOT NULL,      # time of stop
  miles INT UNSIGNED NOT NULL,  # miles traveled so far
  fuel  DECIMAL(6,3),           # gas used between citees
  PRIMARY KEY (seq)
);
#@ _CREATE_TABLE_

INSERT INTO trip_log (t, city, miles, fuel)
VALUES
  ('2013-10-23 05:00:00', 'San Antonio, TX', 0, 0),
  ('2013-10-23 09:10:00', 'Dallas, TX', 263, 11.375),
  ('2013-10-23 13:40:00', 'Benton, AR', 566, 12.398),
  ('2013-10-23 16:51:00', 'Memphis, TN', 745, 6.820),
  ('2013-10-23 19:06:00', 'Portageville, MO', 745+133, 7.007),
  ('2013-10-23 23:16:00', 'Champaign, IL', 745+419, 11.354),
  ('2013-10-24 03:27:00', 'Madison, WI', 745+667, 13.016)
;

SELECT * FROM trip_log;

# Show matched-up rows needed for computing intervals (just for distance)
SELECT t1.seq AS seq1,  t2.seq AS seq2,
  t1.city AS city1, t2.city AS city2,
  t1.miles AS miles1, t2.miles AS miles2,
  t2.miles-t1.miles AS dist
FROM trip_log AS t1, trip_log AS t2
WHERE t1.seq+1 = t2.seq
ORDER BY t1.seq
;

# Compute the intervals, saving result in another table

DROP TABLE IF EXISTS trip_leg;
CREATE TABLE trip_leg
(
  seq INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (seq)
)
SELECT
  t2.city,
  SEC_TO_TIME(UNIX_TIMESTAMP(t2.t)-UNIX_TIMESTAMP(t1.t)) AS t,
  t2.miles-t1.miles AS distance,
  t2.fuel
FROM trip_log AS t1, trip_log AS t2
WHERE t1.seq+1 = t2.seq
;

SELECT * FROM trip_leg;

# Compute cumulative distance and fuel used, as well as running MPG average

SELECT t1.seq, t1.city,
  SEC_TO_TIME(SUM(TIME_TO_SEC(t2.t))) AS t,
  SUM(t2.distance) AS distance,
  SUM(t2.fuel) AS fuel,
  SUM(t2.distance)/SUM(t2.fuel) AS MPG
FROM trip_leg AS t1, trip_leg AS t2
WHERE t1.seq >= t2.seq
GROUP BY t1.seq
;

