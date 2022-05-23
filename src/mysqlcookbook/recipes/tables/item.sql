# item.sql

DROP TABLE IF EXISTS item;
#@ _CREATE_TABLE_
CREATE TABLE item
(
  id      INT UNSIGNED NOT NULL AUTO_INCREMENT,
  name    CHAR(20),
  colors  ENUM('chartreuse','mauve','lime green','puce') DEFAULT 'puce',
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_
