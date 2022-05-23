# resequence.sql

# Demonstrate method for resequencing a table in a particular order.

# First create a table containing sequence and time values which
# are in the same order, but such that the table doesn't
# deliberately doesn't have the rows in order

DROP TABLE IF EXISTS seqtbl;
CREATE TABLE seqtbl
(
  id  INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  t   TIME NOT NULL
);

INSERT INTO seqtbl (id, t)
  VALUES
    (10, '10:00:00'),
    (50, '50:00:00'),
    (30, '30:00:00'),
    (20, '20:00:00'),
    (40, '40:00:00')
;

SELECT * FROM seqtbl;

# Resequence, letting MySQL pick the rows in whatever order it wants

ALTER TABLE seqtbl
DROP id,
ADD id INT UNSIGNED NOT NULL AUTO_INCREMENT FIRST,
AUTO_INCREMENT = 1;

# Display table - the time values probably won't correspond to the id
# order any more

SELECT * FROM seqtbl;

# Now resequence in such a way that the id values are assigned in time
# order:
# - Create an empty clone of the original table.
# - Select rows from the original into the clone, except for the
#   AUTO_INCREMENT column, using ORDER BY to specify the order.  This
#   resequences in retrieval order.
# - Drop the original table and rename to the clone to the original name.

DROP TABLE IF EXISTS seqtbl2;
CREATE TABLE seqtbl2
(
  id  INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  t   TIME NOT NULL
);
INSERT INTO seqtbl2 (t) SELECT t FROM seqtbl ORDER BY t;

DROP TABLE seqtbl;
ALTER TABLE seqtbl2 RENAME TO seqtbl;

SELECT * FROM seqtbl;
