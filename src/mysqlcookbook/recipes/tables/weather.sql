# weather.sql

DROP TABLE IF EXISTS weatherdata;
#@ _CREATE_TABLE_
CREATE TABLE weatherdata
(
  station INT UNSIGNED NOT NULL,
  type    ENUM('precip','temp','cloudiness','humidity','barometer') NOT NULL,
  value   FLOAT,
  PRIMARY KEY (station, type)
);
#@ _CREATE_TABLE_
