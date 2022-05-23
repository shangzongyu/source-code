# php_session.sql

DROP TABLE IF EXISTS php_session;
#@ _CREATE_TABLE_
CREATE TABLE php_session
(
  id          CHAR(32) NOT NULL,
  data        LONGBLOB,
  update_time TIMESTAMP NOT NULL,
  PRIMARY KEY (id),
  INDEX (update_time)
);
#@ _CREATE_TABLE_
