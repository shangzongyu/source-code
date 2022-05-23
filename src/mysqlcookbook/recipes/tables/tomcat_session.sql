# tomcat_session.sql
# Table for Tomcat session management

DROP TABLE IF EXISTS tomcat_session;
#@ _CREATE_SESSION_TABLE_
CREATE TABLE tomcat_session
(
  id            VARCHAR(32) NOT NULL,
  app           VARCHAR(255),
  data          LONGBLOB,
  valid_session CHAR(1) NOT NULL,
  max_inactive  INT NOT NULL,
  update_time   BIGINT NOT NULL,
  PRIMARY KEY (id),
  INDEX (app)
) CHARACTER SET latin1;
#@ _CREATE_SESSION_TABLE_
