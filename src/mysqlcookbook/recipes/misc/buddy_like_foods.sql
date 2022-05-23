# buddy_like_foods.sql

# Find buddies in the profile table that share a common favorite food.

# The query compares the table to itself to find all combinations
# of buddies.

# This operates on the principle that the table joined to itself forms
# a square matrix, and that the unique pairs are those matrix elements
# below the diagonal, or above the diagonal.  Because the profile table
# rows contain an id column, it's easy to select elements above or below
# the diagonal using id1 < id2 or id1 > id2 comparisons.

# The foods column is stored as a SET; the query adds 0 to the foods
# value to convert the SET value to an integer, then does a bit AND
# to find nonzero intersection between set values.

SELECT b1.id, b1.name, b2.id, b2.name, b1.foods, b2.foods
FROM profile AS b1, profile AS b2
WHERE b1.id < b2.id
AND (b1.foods+0) & (b2.foods+0)
;
