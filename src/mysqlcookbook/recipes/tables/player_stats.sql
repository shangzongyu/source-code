# player_stats.sql

# player monthly hitting statistics over the course of a season

DROP TABLE IF EXISTS player_stats;
#@ _CREATE_TABLE_
CREATE TABLE player_stats
(
  id    INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id),
  date  DATE NOT NULL,          # date of cumulative stats
  ab    INT UNSIGNED NOT NULL,  # total at-bats as of date
  h     INT UNSIGNED NOT NULL   # total hits as of date
);
#@ _CREATE_TABLE_

INSERT INTO player_stats (date, ab, h)
VALUES
  ('2013-04-30', 0, 0),
  ('2013-05-31', 38, 13),
  ('2013-06-30', 109, 31),
  ('2013-07-31', 196, 49),
  ('2013-08-31', 304, 98)
;

SELECT id, date, ab, h, TRUNCATE(IFNULL(h/ab,0),3) AS ba
FROM player_stats ORDER BY id;

# Match up successive rows and compute differences for ab, h,
# and monthly ba

SELECT t1.id AS id1, t2.id AS id2,
  t1.ab AS ab1, t2.ab AS ab2,
  t1.h AS h1, t2.h AS h2,
  t2.ab-t1.ab AS abdiff,
  t2.h-t1.h AS hdiff,
  TRUNCATE(IFNULL((t2.h-t1.h)/(t2.ab-t1.ab),0),3) AS ba
FROM player_stats AS t1, player_stats AS t2
WHERE t1.id+1 = t2.id
ORDER BY t1.id
;

# Save the difference values in another table, then use a self-join
# to produce cumulative values as a check.  This should result in
# values that are the same as those in the original table.

# Make sure to select rows in proper order so that the new id values
# are assigned in date order.

DROP TABLE IF EXISTS player_stats2;
CREATE TABLE player_stats2
(
  id  INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id)
)
SELECT
  t2.date,
  t2.ab-t1.ab AS ab,
  t2.h-t1.h AS h
FROM player_stats AS t1, player_stats AS t2
WHERE t1.id+1 = t2.id
ORDER BY t1.id
;

# Compute cumulative values

SELECT t1.id, t1.date,
  SUM(t2.ab) AS ab,
  SUM(t2.h) AS h
FROM player_stats2 AS t1, player_stats2 AS t2
WHERE t1.id >= t2.id
GROUP BY t1.id
;

# Compute cumulative values, but ordering by date to illustrate
# that cumulative values calculation don't need a sequence column,
# they need only a column that can be used to place the records in
# the proper order.

SELECT t1.id, t1.date,
  SUM(t2.ab) AS ab,
  SUM(t2.h) AS h
FROM player_stats2 AS t1, player_stats2 AS t2
WHERE t1.id >= t2.id
GROUP BY t1.id, t1.date
;

