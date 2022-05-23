# book_vendor.sql

DROP TABLE IF EXISTS book_vendor;
#@ _CREATE_TABLE_
CREATE TABLE book_vendor
(
  name    VARCHAR(40),
  website VARCHAR(80),
  PRIMARY KEY(name)
);
#@ _CREATE_TABLE_

INSERT INTO book_vendor (name,website)
  VALUES
    ('Barnes & Noble','www.barnesandnoble.com'),
    ('O\'Reilly Media','www.oreilly.com'),
    ('Amazon.com','www.amazon.com')
;
