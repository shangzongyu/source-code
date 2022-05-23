# movies-actors.sql

# Tables to illustrate many-to-many relationship

# movies_actors - the nonnormal table that contains movie/actor information
# movies - normalized table of movies
# actors - normalized table of actors
# movies_actors_link - table that links movies and actors

DROP TABLE IF EXISTS movies_actors;
#@ _CREATE_MOVIE_ACTOR_TABLE_
CREATE TABLE movies_actors
(
  year  YEAR NOT NULL,        # year movie was released
  movie VARCHAR(80) NOT NULL, # movie name
  actor VARCHAR(60) NOT NULL  # actor name
);
#@ _CREATE_MOVIE_ACTOR_TABLE_

INSERT INTO movies_actors (year,movie,actor)
  VALUES
 (2005,'Kingdom of Heaven','Liam Neeson')
,(2005,'Kingdom of Heaven','Orlando Bloom')
,(1997,'The Fifth Element','Bruce Willis')
,(1997,'The Fifth Element','Gary Oldman')
,(1997,'The Fifth Element','Ian Holm')
,(1999,'The Phantom Menace','Ewan McGregor')
,(1999,'The Phantom Menace','Liam Neeson')
,(2001,'The Fellowship of the Ring','Ian McKellen')
,(2001,'The Fellowship of the Ring','Ian Holm')
,(2001,'The Fellowship of the Ring','Orlando Bloom')
,(2001,'The Fellowship of the Ring','Elijah Wood')
,(2010,'Red','Helen Mirren')
,(2010,'Red','Bruce Willis')
,(2011,'Unknown','Diane Kruger')
,(2011,'Unknown','Liam Neeson')
#,(1995,'Twelve Monkeys','Brad Pitt')
#,(1995,'Twelve Monkeys','Bruce Willis')
#,(1995,'Rob Roy','Brian Cox')
#,(1995,'Rob Roy','Liam Neeson')
#,(2005,'Batman Begins','Liam Neeson')
#,(2005,'Batman Begins','Christian Bale')
#,(2000,'X-Men 2','Halle Berry')
#,(2000,'X-Men 2','Hugh Jackman')
#,(2000,'X-Men 2','Ian McKellen')
#,(2000,'X-Men 2','Brian Cox')
#,(2004,'Troy','Brad Pitt')
#,(2004,'Troy','Brian Cox')
#,(2004,'Troy','Diane Kruger')
#,(2004,'Troy','Eric Bana')
#,(2004,'Troy','Orlando Bloom')
#,(2004,'Troy','Sean Bean')
#,(2001,'Swordfish','Halle Berry')
#,(2001,'Swordfish','Hugh Jackman')
#,(2011,'Hanna','Cate Blanchett')
#,(2011,'Hanna','Eric Bana')
#,(2005,'The Island','Ewan McGregor')
#,(2005,'The Island','Michael Clarke Duncan')
#,(2005,'The Island','Sean Bean')
;

SELECT * FROM movies_actors ORDER BY year, movie, actor;

DROP TABLE IF EXISTS movies;
#@ _CREATE_MOVIE_TABLE_
CREATE TABLE movies
(
  id      INT UNSIGNED NOT NULL AUTO_INCREMENT,
  year  YEAR NOT NULL,        # year when movie was released
  movie VARCHAR(80) NOT NULL, # movie name
  PRIMARY KEY (id)
);
#@ _CREATE_MOVIE_TABLE_

DROP TABLE IF EXISTS actors;
#@ _CREATE_ACTOR_TABLE_
CREATE TABLE actors
(
  id    INT UNSIGNED NOT NULL AUTO_INCREMENT,
  actor VARCHAR(60) NOT NULL, # actor name
  PRIMARY KEY (id)
);
#@ _CREATE_ACTOR_TABLE_

# Populate the normalized tables from the nonnormal table

INSERT INTO movies (year,movie)
SELECT DISTINCT year, movie FROM movies_actors ORDER BY year, movie;

SELECT * FROM movies;

INSERT INTO actors (actor)
SELECT DISTINCT actor FROM movies_actors ORDER BY actor;

SELECT * FROM actors;

DROP TABLE IF EXISTS movies_actors_link;
#@ _CREATE_MOVIE_ACTOR_LINK_TABLE_
CREATE TABLE movies_actors_link
(
  movie_id INT UNSIGNED NOT NULL,
  actor_id INT UNSIGNED NOT NULL,
  UNIQUE (movie_id, actor_id)
);
#@ _CREATE_MOVIE_ACTOR_LINK_TABLE_

# Populate the link table using the nonnormal table, combined with
# the normalized table to determine the link IDs

INSERT INTO movies_actors_link
SELECT movies.id, actors.id
FROM movies_actors INNER JOIN movies INNER JOIN actors
WHERE movies_actors.movie = movies.movie
AND movies_actors.actor = actors.actor;

SELECT * FROM movies_actors_link;

# Some queries that use the link table to relate the primary tables

# Demononstrate that the information originally in the nonnormal table
# can be generated from the normalized tables

SELECT m.year, m.movie, a.actor
FROM movies AS m INNER JOIN movies_actors_link AS l INNER JOIN actors AS a
ON m.id = l.movie_id AND a.id = l.actor_id
ORDER BY m.year, m.movie, a.actor;

# Actors in a particular movie

SELECT a.actor
FROM movies AS m INNER JOIN movies_actors_link AS l INNER JOIN actors AS a
ON m.id = l.movie_id AND a.id = l.actor_id
WHERE m.movie = 'The Fellowship of the Ring'
ORDER BY a.actor;

# Movies that a given actor appeared in

SELECT m.year, m.movie
FROM movies AS m INNER JOIN movies_actors_link AS l INNER JOIN actors AS a
ON m.id = l.movie_id AND a.id = l.actor_id 
WHERE a.actor = 'Liam Neeson'
ORDER BY m.year, m.movie;

# How many actors are listed for each movie?

SELECT m.movie, COUNT(*)
FROM movies AS m INNER JOIN movies_actors_link AS l INNER JOIN actors AS a
ON m.id = l.movie_id AND a.id = l.actor_id 
GROUP BY m.movie
ORDER BY COUNT(*) DESC;

# For how many movies is each actor listed?

SELECT a.actor, COUNT(*)
FROM movies AS m INNER JOIN movies_actors_link AS l INNER JOIN actors AS a
ON m.id = l.movie_id AND a.id = l.actor_id 
GROUP BY a.actor
ORDER BY COUNT(*) DESC;
