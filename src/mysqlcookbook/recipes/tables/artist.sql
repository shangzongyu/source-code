# artist.sql

# artist/painting tables for master-detail join examples

DROP TABLE IF EXISTS artist;
#@ _CREATE_TABLE_ARTIST_
CREATE TABLE artist
(
  a_id  INT UNSIGNED NOT NULL AUTO_INCREMENT, # artist ID
  name  VARCHAR(30) NOT NULL,                 # artist name
  PRIMARY KEY (a_id),
  UNIQUE (name)
);
#@ _CREATE_TABLE_ARTIST_

INSERT INTO artist (name) VALUES
  ('Da Vinci'),
  ('Monet'),
  ('Van Gogh'),
  ('Renoir')
;

SELECT * FROM artist;

DROP TABLE IF EXISTS painting;
#@ _CREATE_TABLE_PAINTING_
CREATE TABLE painting
(
  a_id  INT UNSIGNED NOT NULL,                # artist ID
  p_id  INT UNSIGNED NOT NULL AUTO_INCREMENT, # painting ID
  title VARCHAR(100) NOT NULL,                # title of painting
  state VARCHAR(2) NOT NULL,                  # state where purchased
  price INT UNSIGNED,                         # purchase price (dollars)
  INDEX (a_id),
  PRIMARY KEY (p_id)
);
#@ _CREATE_TABLE_PAINTING_

# Use INSERT INTO ... SELECT form to get proper artist ID corresponding
# to artist name

INSERT INTO painting (a_id,title,state,price)
  SELECT a_id, 'The Last Supper', 'IN', 34
  FROM artist WHERE name = 'Da Vinci';
INSERT INTO painting (a_id,title,state,price)
  SELECT a_id, 'Mona Lisa', 'MI', 87
  FROM artist WHERE name = 'Da Vinci';

INSERT INTO painting (a_id,title,state,price)
  SELECT a_id, 'Starry Night', 'KY', 48
  FROM artist WHERE name = 'Van Gogh';
INSERT INTO painting (a_id,title,state,price)
  SELECT a_id, 'The Potato Eaters', 'KY', 67
  FROM artist WHERE name = 'Van Gogh';

INSERT INTO painting (a_id,title,state,price)
  SELECT a_id, 'Les Deux Soeurs', 'NE', 64
  FROM artist WHERE name = 'Renoir';

SELECT * FROM painting;
