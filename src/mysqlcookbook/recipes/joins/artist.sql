# artist.sql

# For which artist do you have the most paintings?

# This query shows the counts for each artist:

SELECT artist.name, COUNT(*) AS count
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id
GROUP BY artist.a_id;

# This query does the same, but sorts and takes the first record
# to find the one with the maximum count:

SELECT artist.name, COUNT(*) AS count
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id
GROUP BY artist.a_id
ORDER BY count DESC LIMIT 1;

# This does the same, using a variable to hold the maximum, then
# selecting against the variable value

SELECT @count := COUNT(*) AS count
FROM painting GROUP BY a_id
ORDER BY count DESC LIMIT 1;

SELECT artist.name, COUNT(*) AS count
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id
GROUP BY artist.a_id
HAVING count = @count;


# This method uses a temporary table to hold the counts and joins
# that to the artist table

CREATE TEMPORARY TABLE artist_count
SELECT artist.a_id, COUNT(*) AS count
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id
GROUP BY artist.a_id;

# List of all artist IDs and names, whether represented in paintings.

#@ _SELECT_ALL_ARTISTS_
SELECT a_id, name FROM artist;
#@ _SELECT_ALL_ARTISTS_

# List of all artist IDs and names, for only those artists represented
# in paintings.

#@ _SELECT_REPRESENTED_ARTISTS_
SELECT DISTINCT artist.a_id, artist.name
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id;
#@ _SELECT_REPRESENTED_ARTISTS_

# [need to finish this...]
