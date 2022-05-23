# states.sql

# US states table:
# full name, abbreviation, date of statehood (entry into the Union),
# populations from 2021 census
# Population values were taken from US Census Bureau:
# http://www.census.gov/

DROP TABLE IF EXISTS states;
#@ _CREATE_TABLE_
CREATE TABLE states
(
  name      VARCHAR(30) NOT NULL, # state name
  abbrev    CHAR(2) NOT NULL,     # 2-letter abbreviation
  statehood DATE,                 # date of entry into the Union
  pop       BIGINT,               # population from 2010 census
  PRIMARY KEY (abbrev)
);
#@ _CREATE_TABLE_

LOAD DATA LOCAL INFILE 'states.txt' INTO TABLE states;
