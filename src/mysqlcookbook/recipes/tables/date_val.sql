# date_val.sql

# table of test date_val

DROP TABLE IF EXISTS date_val;
CREATE TABLE date_val
(
  d DATE
);

# Do not change the 1900 or 2000 dates. They're needed to illustrate
# points about leap-year testing.

INSERT INTO date_val (d) VALUES('1864-02-28');
INSERT INTO date_val (d) VALUES('1900-01-15');
INSERT INTO date_val (d) VALUES('1999-12-31');
INSERT INTO date_val (d) VALUES('2000-06-04');
INSERT INTO date_val (d) VALUES('2017-03-16');


# Select

SELECT d, DAYNAME(d), DATE_FORMAT(d, '%a') FROM date_val;
