# tsdemo.sql

# Using a TIMESTAMP column to:
# * Record time of row creation and most recent row modification
# * Record time of row creation only
# * Record time of most recent row modification only

# SET @dummy = SLEEP(5) serves to introduce a pause into
# the script so that time passes between statements.

DROP TABLE IF EXISTS tsdemo;
#@ _CREATE_TABLE_
CREATE TABLE `tsdemo` (
`val` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
`ts_both` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
`ts_create` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
`ts_update` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB ;
#@ _CREATE_TABLE_

# Demonstrate that inserting no explicit value inserts the current
# timestamp into the TIMESTAMP and DATETIME columns. Also demonstrate
# that inserting NULL inserts current timestamp into TIMESTAMP columns.

INSERT INTO tsdemo (val) VALUES(5);
SET @dummy = SLEEP(5);
INSERT INTO tsdemo (val,ts_both,ts_create,ts_update)
VALUES(10,NULL,NULL,NULL);

SELECT * FROM tsdemo;

# Change one row; TIMESTAMP columns that auto-update in that row will update

SET @dummy = SLEEP(4);
UPDATE tsdemo SET val = 11 WHERE val = 10;
SELECT * FROM tsdemo;

# Change all rows; TIMESTAMP columns that auto-update in all rows will update

SET @dummy = SLEEP(6);
UPDATE tsdemo SET val = val + 1;
SELECT * FROM tsdemo;

# An update that changes no rows (doesn't change any TIMESTAMP columns)

SET @dummy = SLEEP(2);
UPDATE tsdemo SET val = val;
SELECT * FROM tsdemo;
