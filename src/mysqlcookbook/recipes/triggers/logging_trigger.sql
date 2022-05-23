# logging_trigger.sql

# Use triggers to cause changes to one table to be logged to another table.
# Table 1: Current info for a given key
# Table 2: History of changes to the row containing each key

DROP TABLE IF EXISTS auction, auction_log;
#@ _CREATE_TABLE_1_
CREATE TABLE auction
(
  id   INT UNSIGNED NOT NULL AUTO_INCREMENT,
  ts   TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  item VARCHAR(30) NOT NULL,
  bid  DECIMAL(10,2) NOT NULL,
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_1_

#@ _CREATE_TABLE_2_
CREATE TABLE auction_log
(
  action ENUM('create','update','delete'),
  id    INT UNSIGNED NOT NULL,
  ts    TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  item  VARCHAR(30) NOT NULL,
  bid   DECIMAL(10,2) NOT NULL,
  INDEX (id)
);
#@ _CREATE_TABLE_2_

delimiter $$

# Set up AFTER INSERT trigger that logs row-creation info to the
# log table.
# (AFTER, assuming that nothing is logged if an error occurs)
# Use NEW.col_name to log the values being inserted.

#@ _AFTER_INSERT_TRIGGER_
CREATE TRIGGER ai_auction AFTER INSERT ON auction
FOR EACH ROW
INSERT INTO auction_log (action,id,ts,item,bid)
VALUES('create',NEW.id,NOW(),NEW.item,NEW.bid);
#@ _AFTER_INSERT_TRIGGER_
$$

# Set up AFTER UPDATE trigger that logs row-change info to the
# log table.
# (AFTER, assuming that nothing is logged if an error occurs)
# Use NEW.col_name to log the new values used for the update.

#@ _AFTER_UPDATE_TRIGGER_
CREATE TRIGGER au_auction AFTER UPDATE ON auction
FOR EACH ROW
INSERT INTO auction_log (action,id,ts,item,bid)
VALUES('update',NEW.id,NOW(),NEW.item,NEW.bid);
#@ _AFTER_UPDATE_TRIGGER_
$$

# Set up AFTER DELETE trigger that logs row-removal info to the
# log table.
# (AFTER, assuming that nothing is logged if an error occurs)
# Use OLD.col_name to log the new values in the deleted row.

#@ _AFTER_DELETE_TRIGGER_
CREATE TRIGGER ad_auction AFTER DELETE ON auction
FOR EACH ROW
INSERT INTO auction_log (action,id,ts,item,bid)
VALUES('delete',OLD.id,OLD.ts,OLD.item,OLD.bid);
#@ _AFTER_DELETE_TRIGGER_
$$

delimiter ;

# Create a couple of new auctions

INSERT INTO auction (item,bid) VALUES('chintz pillows', 5.00);
SET @dummy = SLEEP(2);
INSERT INTO auction (item,bid) VALUES('rabbit food', 2.50);
SELECT * FROM auction;
SELECT * FROM auction_log;

# Issue some bids

SET @dummy = SLEEP(3);
UPDATE auction SET bid = 3.00 WHERE item = 'rabbit food';
SET @dummy = SLEEP(2);
UPDATE auction SET bid = 7.50 WHERE item = 'chintz pillows';
SET @dummy = SLEEP(4);
UPDATE auction SET bid = 3.75 WHERE item = 'rabbit food';

# Finish an auction (remove its row)

SET @dummy = SLEEP(3);
DELETE FROM auction WHERE item = 'rabbit food';

SELECT * FROM auction ORDER BY id;
SELECT * FROM auction_log ORDER BY id, ts;

# Try an insert that fails to make sure that the trigger doesn't
# execute.

SELECT 'Next INSERT should fail' AS Message;
INSERT INTO auction (item,bid) VALUES('business casual slacks', NULL);
SELECT * FROM auction ORDER BY id;
SELECT * FROM auction_log ORDER BY id, ts;
