# interval.sql

SET @d1 = '1999-01-01';
SET @d2 = '2000-01-01';

SELECT TO_DAYS(@d1);
SELECT TO_DAYS(@d2);
SELECT TO_DAYS(@d2) - TO_DAYS(@d1);

# Timestamp interval

SET @ts1 = '19991201101112';
SET @ts2 = '19991202101112';
#SET @ts2 = '19991202081112';

SELECT
  @ts1, @ts2,
  UNIX_TIMESTAMP(@ts1) AS secs_ts1,
  UNIX_TIMESTAMP(@ts2) AS secs_ts2,
  UNIX_TIMESTAMP(@ts2) - UNIX_TIMESTAMP(@ts1) AS secs_diff,
  (UNIX_TIMESTAMP(@ts2) - UNIX_TIMESTAMP(@ts1)) / 60 AS mins_diff;

# interval between times

SET @t1 = '08:00:00';
SET @t2 = '15:00:00';

SELECT
  @t1, @t2,
  TIME_TO_SEC(@t1) AS secs_t1,
  TIME_TO_SEC(@t2) AS secs_t2,
  # interval in seconds
  TIME_TO_SEC(@t2) - TIME_TO_SEC(@t1) AS secs_diff,
  # interval as a TIME value
  SEC_TO_TIME(TIME_TO_SEC(@t2) - TIME_TO_SEC(@t1)) AS time_diff;
