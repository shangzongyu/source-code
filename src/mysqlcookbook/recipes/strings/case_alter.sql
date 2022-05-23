# case_alter.sql

# Illustrate use of ALTER TABLE for changing data type

DROP TABLE IF EXISTS news;
#@ _CREATE_TABLE_
CREATE TABLE news
(
  id      INT UNSIGNED NOT NULL AUTO_INCREMENT,
  article BLOB,
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_

SHOW CREATE TABLE news\G

#@ _ALTER_1_
ALTER TABLE news
  MODIFY article TEXT CHARACTER SET utf8 COLLATE utf8_general_ci;
#@ _ALTER_1_

SHOW CREATE TABLE news\G
