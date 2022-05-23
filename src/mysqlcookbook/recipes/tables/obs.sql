# obs.sql

# Table with some sample observation values

DROP TABLE IF EXISTS obs;
#@ _CREATE_TABLE_
CREATE TABLE obs
(
  val INT
);
#@ _CREATE_TABLE_

INSERT INTO obs (val)
  VALUES
    (99),(98),(98),(95),(93),(93),(93),(92),(90),(87)
;

SELECT * FROM obs;
