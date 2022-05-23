# booksales.sql

DROP TABLE IF EXISTS booksales;
#@ _CREATE_TABLE_
CREATE TABLE booksales
(
  title   VARCHAR(60) NOT NULL,   # book title
  copies  INT UNSIGNED NOT NULL,  # number of copies sold
  PRIMARY KEY (title)
);
#@ _CREATE_TABLE_
