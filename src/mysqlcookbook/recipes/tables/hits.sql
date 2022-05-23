# hits.sql

# Web page hit-counter and hit-logging tables
# These should both be created at the same time so that the hits columns
# of each remain in sync when the tables are accessed by the
# hits.{pl,php,py,rb,jsp} scripts.

DROP TABLE IF EXISTS hitcount;
#@ _CREATE_HITCOUNT_TABLE_
CREATE TABLE hitcount
(
  path  VARCHAR(255)
          CHARACTER SET latin1 COLLATE latin1_general_cs NOT NULL,
  hits  BIGINT UNSIGNED NOT NULL,
  PRIMARY KEY (path)
);
#@ _CREATE_HITCOUNT_TABLE_

DROP TABLE IF EXISTS hitlog;
#@ _CREATE_HITLOG_TABLE_
CREATE TABLE hitlog
(
  id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  path  VARCHAR(255)
          CHARACTER SET latin1 COLLATE latin1_general_cs NOT NULL,
  t     TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  host  VARCHAR(255),
  INDEX (path)
);
#@ _CREATE_HITLOG_TABLE_
