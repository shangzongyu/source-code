# housewares.sql

# housewares catalogs:
# housewares: fixed-length id substrings
# housewares2: id represented by separate category, serial, country columns
# housewares3: like housewares, but serial number part of id
#   has no leading zeros (variable-length id substrings)
# housewares4: id in n-n-n-n format

DROP TABLE IF EXISTS housewares;
CREATE TABLE housewares
(
  id      VARCHAR(20),
  description VARCHAR(255),
  PRIMARY KEY(id)
);

INSERT INTO housewares (id,description)
  VALUES
    ('DIN40672US', 'dining table'),
    ('KIT00372UK', 'garbage disposal'),
    ('KIT01729JP', 'microwave oven'),
    ('BED00038SG', 'bedside lamp'),
    ('BTH00485US', 'shower stall'),
    ('BTH00415JP', 'lavatory')
;

SELECT * FROM housewares;

# Alternate representation of the housewares table.  It has the id
# column represented by three columns

DROP TABLE IF EXISTS housewares2;
#@ _CREATE_TABLE_HOUSEWARES2__
CREATE TABLE housewares2
(
  id          VARCHAR(20) NOT NULL,
  category    VARCHAR(3) GENERATED ALWAYS AS (left(`id`,3)) STORED,
  serial      CHAR(5) GENERATED ALWAYS AS (substr(`id`,4,5)) STORED,
  country     VARCHAR(2) GENERATED ALWAYS AS (right(`id`,2)) STORED,
  description VARCHAR(255),
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_HOUSEWARES2__

INSERT INTO housewares2 (id,description)
  VALUES
    ('DIN40672US', 'dining table'),
    ('KIT00372UK', 'garbage disposal'),
    ('KIT01729JP', 'microwave oven'),
    ('BED00038SG', 'bedside lamp'),
    ('BTH00485US', 'shower stall'),
    ('BTH00415JP', 'lavatory')
;

SELECT * FROM housewares2;

DROP TABLE IF EXISTS housewares3;
CREATE TABLE housewares3
(
  id      VARCHAR(20),
  description VARCHAR(255),
  PRIMARY KEY(id)
);

INSERT INTO housewares3 (id,description)
  VALUES
    ('DIN40672US', 'dining table'),
    ('KIT372UK', 'garbage disposal'),
    ('KIT1729JP', 'microwave oven'),
    ('BED38SG', 'bedside lamp'),
    ('BTH485US', 'shower stall'),
    ('BTH415JP', 'lavatory')
;

SELECT * FROM housewares3;

# housewares4 table
# NEED BETTER NAME


DROP TABLE IF EXISTS housewares4;
CREATE TABLE housewares4
(
  id      VARCHAR(20),
  description VARCHAR(255),
  PRIMARY KEY(id)
);

INSERT INTO housewares4 (id,description)
  VALUES
    ('13-478-92-2', 'dining table'),
    ('873-48-649-63', 'garbage disposal'),
    ('8-4-2-1', 'microwave oven'),
    ('97-681-37-66', 'bedside lamp'),
    ('27-48-534-2', 'shower stall'),
    ('5764-56-89-72', 'lavatory')
;

SELECT * FROM housewares4;

DROP TABLE IF EXISTS hw_category;
CREATE TABLE hw_category
(
  abbrev  VARCHAR(3),
  name  VARCHAR(20),
  PRIMARY KEY(abbrev)
);

INSERT INTO hw_category (abbrev,name)
  VALUES
    ('DIN', 'dining'),
    ('KIT', 'kitchen'),
    ('BTH', 'bathroom'),
    ('BED', 'bedroom')
;

SELECT * FROM hw_category;
