# dup_info.sql

# Count rows in a table.  Indicate how many unique rows there are and
# how many duplicates.

DROP TABLE IF EXISTS t, tmp;

CREATE TEMPORARY TABLE t (size CHAR(10), color CHAR(10));

INSERT INTO t (size,color) VALUES
('S','red'),('S','blue'),('S','blue'),('M','green'),
('M','red'),('M','green'),('L','blue'),('L','green'),
('L','red'),('L','green'),('L','red'),('L','green')
;

SELECT * FROM t ORDER BY size, color;
CREATE TEMPORARY TABLE tmp
SELECT COUNT(*) AS count, size, color FROM t GROUP BY size, color
;
SELECT * FROM tmp ORDER BY size, color;
SELECT COUNT(*) AS 'unique', SUM(count) AS 'total',
SUM(count-1) AS 'dups', SUM(count) - COUNT(*) AS 'dups'
FROM tmp;
