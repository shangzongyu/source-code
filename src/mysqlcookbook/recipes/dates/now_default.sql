# now_default.sql

# demonstrate that NOW() doesn't work as a default value

DROP TABLE IF EXISTS testtbl;
CREATE TABLE testtbl (dt DATETIME DEFAULT NOW())
;

SHOW COLUMNS FROM testtbl;
