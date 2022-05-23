# person_index.sql

# Ways to index a person table for various kinds of dup-value prevention

# Table that includes no index; duplicate values are permitted

DROP TABLE IF EXISTS person;
#@ _DUPS_ALLOWED_
CREATE TABLE person
(
  last_name   CHAR(20),
  first_name  CHAR(20),
  address     CHAR(40)
);
#@ _DUPS_ALLOWED_

# Table that includes a PRIMARY KEY on the name columns; no duplicate names
# are permitted

DROP TABLE IF EXISTS person;
#@ _NO_DUPS_PK_
CREATE TABLE person
(
  last_name   CHAR(20) NOT NULL,
  first_name  CHAR(20) NOT NULL,
  address     CHAR(40),
  PRIMARY KEY (last_name, first_name)
);
#@ _NO_DUPS_PK_

# Table that includes a UNIQUE index on the name columns; no duplicate names
# are permitted

DROP TABLE IF EXISTS person;
#@ _NO_DUPS_UNIQUE_1_
CREATE TABLE person
(
  last_name   CHAR(20) NOT NULL,
  first_name  CHAR(20) NOT NULL,
  address     CHAR(40),
  UNIQUE (last_name, first_name)
);
#@ _NO_DUPS_UNIQUE_1_

# Table that includes a UNIQUE index on the name columns, but first_name
# is permitted to be NULL, so it's possible for multiple records with the
# same last name and a NULL first name to be present in the table.  (For
# records with non-NULL values in the first_name and last_name columns,
# the name must be unique.)

DROP TABLE IF EXISTS person;
CREATE TABLE person
(
  last_name   CHAR(20) NOT NULL,
  first_name  CHAR(20),
  address     CHAR(40),
  UNIQUE (last_name, first_name)
);

# Table that permits duplicate records with the same name but uses an
# AUTO_INCREMENT column for the unique key.  (id values are assigned
# automatically by MySQL.)

DROP TABLE IF EXISTS person;
#@ _NO_DUPS_AUTO_INCREMENT_
CREATE TABLE person
(
  id          INT UNSIGNED NOT NULL AUTO_INCREMENT,
  last_name   CHAR(20),
  first_name  CHAR(20),
  address     CHAR(40),
  PRIMARY KEY (id)
);
#@ _NO_DUPS_AUTO_INCREMENT_

# Table that permits duplicate records with the same name but uses a
# taxpayer ID column for the unique key.  (tax_id values must be
# assigned externally.)

DROP TABLE IF EXISTS person;
#@ _NO_DUPS_TAX_ID_
CREATE TABLE person
(
  tax_id      INT UNSIGNED NOT NULL,
  last_name   CHAR(20),
  first_name  CHAR(20),
  address     CHAR(40),
  PRIMARY KEY (tax_id)
);
#@ _NO_DUPS_TAX_ID_
