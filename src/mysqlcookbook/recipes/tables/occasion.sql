# occasion.sql

# day-in-history occasions


DROP TABLE IF EXISTS occasion;
CREATE TABLE occasion
(
  date        DATE,
  description VARCHAR(255),
  PRIMARY KEY(date)
)
;

INSERT INTO occasion (date,description)
  VALUES
    ('1789-07-04','US Independence Day'),
    ('1776-07-14','Bastille Day'),
    ('1957-10-04','Sputnik launch date'),
    ('1919-06-28','Signing of the Treaty of Versailles'),
    ('1732-02-22','George Washington\'s birthday'),
    ('1989-11-09','Opening of the Berlin Wall'),
    ('1944-06-06','D-Day at Normandy Beaches'),
    ('1215-06-15','Signing of the Magna Carta'),
    ('1809-02-12','Abraham Lincoln\'s birthday')
;

SELECT * FROM occasion;
;
