# doremi.sql

DROP TABLE IF EXISTS doremi;
#@ _CREATE_TABLE_
CREATE TABLE doremi
(
  id        TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id),
  note      CHAR(2),
  mnemonic  CHAR(30)
);
#@ _CREATE_TABLE_

INSERT INTO doremi (note,mnemonic)
VALUES
  ('do', 'A deer, a female deer'),
  ('re', 'A drop of golden sun'),
  ('mi', 'A name I call myself'),
  ('fa', 'A long, long way to run'),
  ('so', 'A needle pulling thread'),
  ('la', 'A note to follow so'),
  ('ti', 'A drink with jam and bread')
;

SELECT * FROM doremi;
