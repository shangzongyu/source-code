# distinct_col.sql

# Queries that produce the same set of rows, but so using different column
# names

# Join with columns that have duplicate names

#@ _NONDISTINCT_NAMES_
SELECT artist.name, painting.title, states.name, painting.price
FROM artist INNER JOIN painting INNER JOIN states
ON artist.a_id = painting.a_id AND painting.state = states.abbrev;
#@ _NONDISTINCT_NAMES_

# Join with columns that have unique names

#@ _DISTINCT_NAMES_
SELECT artist.name AS painter, painting.title,
  states.name AS state, painting.price
FROM artist INNER JOIN painting INNER JOIN states
ON artist.a_id = painting.a_id AND painting.state = states.abbrev;
#@ _DISTINCT_NAMES_
