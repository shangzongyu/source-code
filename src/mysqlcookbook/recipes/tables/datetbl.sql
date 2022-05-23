# datetbl.sql

# create test table with date columns

DROP TABLE IF EXISTS datetbl;
#@ _CREATE_TABLE_
CREATE TABLE datetbl
(
  i   INT,
  c   CHAR(10),
  d   DATE,
  dt  DATETIME,
  ts  TIMESTAMP,
  PRIMARY KEY(i)
);
#@ _CREATE_TABLE_
;

INSERT INTO datetbl (i, c, d, dt, ts)
  VALUES
  (3, 'abc', DATE_SUB(CURDATE(),INTERVAL 1 MONTH),
        DATE_SUB(NOW(),INTERVAL 1 MONTH),
        DATE_SUB(NOW(),INTERVAL 1 MONTH)),
  (4, 'xyz', CURDATE(), NOW(), NOW());
