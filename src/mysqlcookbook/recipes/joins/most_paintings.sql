# most_paintings.sql

# Which artist is represented by the most paintings?

# This is a matter of finding the artist for whom the COUNT(a_id) value
# in the painting table is highest.

# Various aspects of the problem are dealt with below

# Find the count for each artist

SELECT artist.name, painting.a_id, COUNT(painting.a_id) AS count
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id
GROUP BY painting.a_id
ORDER BY count DESC
;

# Same, but use LIMIT 1 to find the most popular artist

SELECT artist.name, painting.a_id, COUNT(painting.a_id) AS count
FROM artist INNER JOIN painting
WHERE artist.a_id = painting.a_id
GROUP BY painting.a_id
ORDER BY count DESC
LIMIT 1
;

# The preceding query won't really be correct if there is a "tie".
# If more than one artist has the max count and you want all of
# them, do this:

# Get the counts per artist

CREATE TEMPORARY TABLE tmp
SELECT a_id, COUNT(*) AS count
FROM painting
GROUP BY a_id;

SELECT * FROM tmp;

# Get the maximum of those values

CREATE TEMPORARY TABLE tmp2
SELECT MAX(count) AS max_count FROM tmp;

SELECT * FROM tmp2;

# Join the max count with painting and artist to display
# info for artists with the given count

SELECT artist.name, tmp.count
FROM artist INNER JOIN tmp INNER JOIN tmp2
WHERE artist.a_id = tmp.a_id
AND tmp.count = tmp2.max_count
;
