# city.sql

# Create table listing capital and largest city per US state

DROP TABLE IF EXISTS city;
CREATE TABLE city
(
  state   VARCHAR(40) NOT NULL,
  capital VARCHAR(30) NOT NULL,
  largest VARCHAR(30) NOT NULL,
  PRIMARY KEY(state)
);

LOAD DATA LOCAL INFILE 'city.txt' INTO TABLE city;
