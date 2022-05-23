# cd.sql

# example cd table for the eponymy example

DROP TABLE IF EXISTS cd;
#@ _CREATE_TABLE_
CREATE TABLE cd
(
  id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  year    INT UNSIGNED, # year of issue
  artist  VARCHAR(50),  # artist or group name
  title   VARCHAR(50)   # album title
);
#@ _CREATE_TABLE_

INSERT INTO cd (year,artist,title) VALUES
(1990,'Iona','Iona'),
(1999,'Charlie Peacock','Kingdom Come'),
(2011,'Iona','Another Realm'),
(2002,'Aradhna','Marga Darshan'),
(2004,'Dave Bainbridge','Veil of Gossamer'),
(2005,'Neal Morse','?'),
(2013,'Red','Release the Panic'),
(1982,'Undercover','Undercover'),
(2008,'Children 18:3','Children 18:3')
;

# select all rows

SELECT year, artist, title FROM cd;

# select eponymous rows (where the title is the same as the artist)

SELECT year, artist, title FROM cd WHERE artist = title;
