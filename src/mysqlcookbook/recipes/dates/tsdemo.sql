# tsdemo.sql

# Demonstrating behaviour of TIMESTAMP and DATETIME

# Create demo  table

DROP TABLE IF EXISTS `tsdemo`;
CREATE TABLE `tsdemo` (
  `val` int UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `ts_both` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `ts_create` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ts_update` timestamp DEFAULT NOW() ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci

# Insert sample data

INSERT INTO tsdemo_v2 (val,ts_both,ts_create,ts_update) VALUES(0,NULL,NULL,NULL);

INSERT INTO tsdemo (val) VALUES(5);

INSERT INTO tsdemo (val,ts_both,ts_create,ts_update)
  VALUES(10,NULL,NULL,NULL);

# Query new rows

SELECT * FROM tsdemo;

# Update table to show timestamp changes

UPDATE tsdemo SET val = 11 WHERE val = 10;
# Query new rows

SELECT * FROM tsdemo;

UPDATE tsdemo SET val = val + 1;
# Query new rows

SELECT * FROM tsdemo;

UPDATE tsdemo SET val = val;
# Query new rows

SELECT * FROM tsdemo;
