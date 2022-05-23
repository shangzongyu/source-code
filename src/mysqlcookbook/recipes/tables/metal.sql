# metal.sql

# This script creates the initial version of the metal table used in
# the strings chapter.

DROP TABLE IF EXISTS metal;
#@ _CREATE_TABLE_
CREATE TABLE metal (
  name VARCHAR(20),
  PRIMARY KEY(name));
#@ _CREATE_TABLE_

# populate table

INSERT INTO metal (name)
  VALUES
    ('gold'),
    ('iron'),
    ('lead'),
    ('mercury'),
    ('platinum'),
    ('tin')
;

SELECT * FROM metal;
