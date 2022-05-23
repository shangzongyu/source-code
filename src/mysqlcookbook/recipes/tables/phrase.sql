# phrase.sql

DROP TABLE IF EXISTS phrase;
#@ _CREATE_TABLE_
CREATE TABLE phrase
(
  phrase_val  VARCHAR(255) PRIMARY KEY
);
#@ _CREATE_TABLE_

INSERT INTO phrase (phrase_val)
  VALUES
    ('rhinoceros'),
    ('cats & dogs'),
    ('are we "there" yet?'),
    ('whole > sum of parts')
;

SELECT * FROM phrase;
