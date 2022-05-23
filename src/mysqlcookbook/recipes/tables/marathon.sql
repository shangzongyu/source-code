# marathon.sql

# marathon table: each record indicates distance and time-to-run for
# each stage of marathon for a hypothetical runner

DROP TABLE IF EXISTS marathon;
#@ _CREATE_TABLE_
CREATE TABLE marathon
(
  stage INT UNSIGNED NOT NULL AUTO_INCREMENT,
  km    INT UNSIGNED NOT NULL,  # length of stage, in km
  t     TIME NOT NULL,          # elapsed time for stage
  PRIMARY KEY (stage)
);
#@ _CREATE_TABLE_

INSERT INTO marathon (km, t)
VALUES
  (5,'00:15:00'),
  (7,'00:19:30'),
  (9,'00:29:20'),
  (5,'00:17:50')
;

SELECT stage, km, t, km/(TIME_TO_SEC(t)/(60*60)) AS 'km/hour'
FROM marathon ORDER BY stage;

# Compute cumulative distance at each stage

SELECT t1.stage, t1.km, SUM(t2.km) AS 'cum. km'
FROM marathon AS t1, marathon AS t2
WHERE t1.stage >= t2.stage
GROUP BY t1.stage;

# Compute cumulative distance and time at each stage, as well as
# running speed average

SELECT t1.stage, t1.km, t1.t,
  SUM(t2.km) AS 'cum. km',
  SEC_TO_TIME(SUM(TIME_TO_SEC(t2.t))) AS 'cum. t',
  SUM(t2.km)/(SUM(TIME_TO_SEC(t2.t))/(60*60)) AS 'avg. km/hour'
FROM marathon AS t1, marathon AS t2
WHERE t1.stage >= t2.stage
GROUP BY t1.stage;

