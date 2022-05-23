# self.sql

# Various self-join things...

# Select pairs of paintings by same artist (nonunique output column names)

SELECT artist.name, p1.title, p2.title
FROM artist INNER JOIN painting AS p1 INNER JOIN painting AS p2
WHERE p1.a_id = p2.a_id AND p1.title <> p2.title
  AND p1.a_id = artist.a_id
;

# Select pairs of paintings by same artist (unique output column names)

SELECT artist.name, p1.title, p2.title AS title2
FROM artist INNER JOIN painting AS p1 INNER JOIN painting AS p2
WHERE p1.a_id = p2.a_id AND p1.title <> p2.title
  AND p1.a_id = artist.a_id
;

SELECT name, statehood from states WHERE name = 'New York';

# without the "eliminate reference state" test
#@ _WITHOUT_REF_STATE_
SELECT states.name, states.statehood
FROM states INNER JOIN states AS ref
WHERE
  ref.name = 'New York'
  AND YEAR(states.statehood) = YEAR(ref.statehood)
ORDER BY states.name
#@ _WITHOUT_REF_STATE_
;

# with the test
#@ _WITH_REF_STATE_
SELECT states.name, states.statehood
FROM states INNER JOIN states AS ref
WHERE
  ref.name = 'New York'
  AND states.name <> ref.name
  AND YEAR(states.statehood) = YEAR(ref.statehood)
ORDER BY states.name
#@ _WITH_REF_STATE_
;

# with the test, within a year on either side of statehood date
#@ _WITHIN_A_YEAR_
SELECT states.name, states.statehood, ref.name, ref.statehood
FROM states INNER JOIN states AS ref
WHERE
  ref.name = 'Maryland'
  AND states.name <> ref.name
  AND DATE_SUB(states.statehood,INTERVAL 1 YEAR) <= ref.statehood
  AND DATE_ADD(states.statehood,INTERVAL 1 YEAR) >= ref.statehood
ORDER BY states.statehood
#@ _WITHIN_A_YEAR_
;


# Find those people who sent a message to themselves
# (no self-join needed for this part)

SELECT * FROM mail WHERE srcuser = dstuser;

# Now, find those people who did NOT send a message to themselves

SELECT DISTINCT m1.srcuser
FROM mail AS m1 LEFT JOIN mail AS m2
ON m1.srcuser = m2.srcuser AND m2.srcuser = m2.dstuser
WHERE m2.dstuser IS NULL
;

