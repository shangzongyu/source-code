# mark_log.sql

# Create simple table to contain "marker" rows, and an event that
# writes a row to the table periodically.

DROP TABLE IF EXISTS mark_log;
#@ _CREATE_TABLE_
CREATE TABLE mark_log
(
  ts      TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  message VARCHAR(100)
);
#@ _CREATE_TABLE_

DROP EVENT IF EXISTS mark_insert;
#@ _CREATE_MARK_INSERT_EVENT_
CREATE EVENT mark_insert
ON SCHEDULE EVERY 5 MINUTE
DO INSERT INTO mark_log (message) VALUES('-- MARK --');
#@ _CREATE_MARK_INSERT_EVENT_

# Create an event that expires old mark_log records (older than two
# days) once a day.

DROP EVENT IF EXISTS mark_expire;
#@ _CREATE_MARK_EXPIRE_EVENT_
CREATE EVENT mark_expire
ON SCHEDULE EVERY 1 DAY
DO DELETE FROM mark_log WHERE ts < NOW() - INTERVAL 2 DAY;
#@ _CREATE_MARK_EXPIRE_EVENT_
