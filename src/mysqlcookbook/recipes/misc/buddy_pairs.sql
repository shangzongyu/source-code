# buddy_pairs.sql

# Find all buddy pairs in the profile table.

# The query compares the table to itself to find all combinations
# of buddies.

# This operates on the principle that the table joined to itself forms
# a square matrix, and that the unique pairs are those matrix elements
# below the diagonal, or above the diagonal.  Because the profile table
# rows contain an id column, it's easy to select elements above or below
# the diagonal using id1 < id2 or id1 > id2 comparisons.

# Select below-diagonal elements
# (assuming b1 down the side, b2 across the top)

SELECT b1.id, b1.name, b2.id, b2.name
FROM profile AS b1, profile AS b2
WHERE b1.id > b2.id
ORDER by b2.id, b1.id
;

# Select above-diagonal elements
# (assuming b1 down the side, b2 across the top)

SELECT b1.id, b1.name, b2.id, b2.name
FROM profile AS b1, profile AS b2
WHERE b1.id < b2.id
ORDER by b1.id, b2.id
;
