# Demo: Using triggers to simulate functional indexes.
# (Note that this is little different from my document content/MD5 example,
# except I have no index on the hash value. Probably should, though, which
# makes this example even less distinct. Hmm...)

# Note: Have to choose query type properly to illustrate index use/nonuse.
# Without name column, it makes a difference whether the table
# uses MyISAM or InnoDB. It appears that InnoDB takes advantage of
# extended indexes? With name, InnoDB is prevented from using extended
# indexes?
# Using BETWEEN in the WHERE clause turns out to be a bad idea for
# demonstrating of EXPLAIN. Use < instead. Then either engine shows the
# difference.

# Create initial table w/o functional column or triggers
DROP TABLE IF EXISTS expdata;
#@ _CREATE_TABLE_
CREATE TABLE expdata
(
  id          INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
  value       FLOAT,  # original values
  log10_value FLOAT,  # LOG10() function of original values
  INDEX (value),      # index on original values
  INDEX (log10_value) # index on function-based values
);
#@ _CREATE_TABLE_
INSERT INTO expdata (value) VALUES (.01),(.1),(1),(10),(100);
SELECT *, LOG10(value) FROM expdata;
SELECT * FROM expdata WHERE LOG10(value) BETWEEN 0 AND 2;
# Try EXPLAIN with and without an indexed functional column
#EXPLAIN SELECT * FROM expdata WHERE LOG10(value) BETWEEN 0 AND 2\G
EXPLAIN SELECT * FROM expdata WHERE LOG10(value) < 1\G
SHOW WARNINGS\G
#ALTER TABLE expdata ADD COLUMN log10_value FLOAT, ADD INDEX (log10_value);
#SHOW CREATE TABLE t\G
UPDATE expdata SET log10_value = LOG10(value);
SELECT * FROM expdata;
SELECT * FROM expdata WHERE log10_value BETWEEN 0 AND 2;
#EXPLAIN SELECT * FROM expdata WHERE log10_value BETWEEN 0 AND 2\G
EXPLAIN SELECT * FROM expdata WHERE log10_value < 1\G
SHOW WARNINGS\G

# Set up a BEFORE INSERT trigger that calculates the LOG10() value
# of new data.

#@ _BEFORE_INSERT_TRIGGER_
CREATE TRIGGER bi_expdata BEFORE INSERT ON expdata
FOR EACH ROW SET NEW.log10_value = LOG10(NEW.value);
#@ _BEFORE_INSERT_TRIGGER_

# Set up a BEFORE UPDATE trigger that updates the LOG10() value for
# of updated data.

#@ _BEFORE_UPDATE_TRIGGER_
CREATE TRIGGER bu_expdata BEFORE UPDATE ON expdata
FOR EACH ROW SET NEW.log10_value = LOG10(NEW.value);
#@ _BEFORE_UPDATE_TRIGGER_

# Clear the table, then insert and update data
TRUNCATE TABLE expdata;
#@ _INSERT_DATA_
INSERT INTO expdata (value) VALUES (.01),(.1),(1),(10),(100);
SELECT * FROM expdata;
#@ _INSERT_DATA_
# Multiply all values by 10; should increase the LOG10 value by 1
#@ _UPDATE_DATA_
UPDATE expdata SET value = value * 10;
SELECT * FROM expdata;
#@ _UPDATE_DATA_
