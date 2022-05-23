# seq_generator.sql

DROP TABLE IF EXISTS seqnum;
# create the table
CREATE TABLE seqnum (num INT UNSIGNED NOT NULL);
# initialize sequence number value
INSERT INTO seqnum SET num = 0;
# Generate a new sequence number
UPDATE seqnum SET num = LAST_INSERT_ID(num+1);
# see what it was
SELECT LAST_INSERT_ID();
# Generate a new sequence number
UPDATE seqnum SET num = LAST_INSERT_ID(num+1);
# see what it was
SELECT LAST_INSERT_ID();
# Generate a new sequence number
UPDATE seqnum SET num = LAST_INSERT_ID(num+1);
# see what it was
SELECT LAST_INSERT_ID();
# etc
