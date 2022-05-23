# adcount.sql

DROP TABLE IF EXISTS adcount;
#@ _CREATE_TABLE_
CREATE TABLE adcount
(
  id          INT NOT NULL,
  impressions INT NOT NULL,
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_

INSERT INTO adcount (id, impressions) VALUES
  (1,0),
  (2,0),
  (3,0),
  (4,0),
  (5,0)
;

SELECT * FROM adcount;
