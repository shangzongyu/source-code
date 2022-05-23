# datetime_val.sql

# table of test date-and-time values (same values as timestamps table,
# but as DATETIME values)

DROP TABLE IF EXISTS datetime_val;
CREATE TABLE datetime_val
(
  dt  DATETIME
);

# These values are the same for datetime_val and timestamp_val.
# Don't change one without changing the other.

INSERT INTO datetime_val (dt) VALUES('1970-01-01 00:00:00');
INSERT INTO datetime_val (dt) VALUES('1999-12-31 09:00:00');
INSERT INTO datetime_val (dt) VALUES('2000-06-04 15:45:30');
INSERT INTO datetime_val (dt) VALUES('2017-03-16 12:30:15');

SELECT * FROM datetime_val;
