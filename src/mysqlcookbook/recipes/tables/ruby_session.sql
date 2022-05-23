# ruby_session.sql

DROP TABLE IF EXISTS ruby_session;
#@ _CREATE_TABLE_
CREATE TABLE ruby_session
(
  session_id    VARCHAR(255) NOT NULL,
  session_value LONGBLOB NOT NULL,
  update_time   DATETIME NOT NULL,
  PRIMARY KEY (session_id)
) CHARACTER SET latin1;
#@ _CREATE_TABLE_

# index the update_time column

#@ _ALTER_TABLE_
ALTER TABLE ruby_session ADD INDEX (update_time);
#@ _ALTER_TABLE_
