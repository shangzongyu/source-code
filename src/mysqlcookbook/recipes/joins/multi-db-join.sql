# multi-db-join.sql

# Performing a join between tables in different databases. This requires
# that the db1 and db2 databases exist and contain copies of the artist
# and painting tables, respectively. If that's not true, then, assuming
# that artist and painting exist in the cookbook database, you can set
# up like this:

# CREATE DATABASE IF NOT EXISTS db1;
# CREATE DATABASE IF NOT EXISTS db2;
# DROP TABLE IF EXISTS db1.artist, db2.painting;
# CREATE TABLE db1.artist LIKE cookbook.artist;
# INSERT INTO db1.artist SELECT * FROM cookbook.artist;
# CREATE TABLE db2.painting LIKE cookbook.painting;
# INSERT INTO db2.painting SELECT * FROM cookbook.painting;

# Without aliases

SELECT db1.artist.name, db2.painting.title
  FROM db1.artist INNER JOIN db2.painting
  ON db1.artist.a_id = db2.painting.a_id;

# With aliases

SELECT a.name, p.title
  FROM db1.artist AS a INNER JOIN db2.painting AS p
  ON a.a_id = p.a_id;

# If default database is db1, no qualifiers necessary for db1

USE db1;
SELECT artist.name, db2.painting.title
  FROM artist INNER JOIN db2.painting
  ON artist.a_id = db2.painting.a_id;

# If default database is db2, no qualifiers necessary for db2

USE db2;
SELECT db1.artist.name, painting.title
  FROM db1.artist INNER JOIN painting
  ON db1.artist.a_id = painting.a_id;
