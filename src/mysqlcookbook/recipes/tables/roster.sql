# roster.sql

# Team roster table, used to show problem of trying to all 0 and 00 as
# player numbers (store as strings), but still get the the column values
# to sort properly (numerically)

DROP TABLE IF EXISTS roster;
#@ _CREATE_TABLE_
CREATE TABLE roster
(
  name        CHAR(30),   # player name
  jersey_num  CHAR(3),     # jersey number
  PRIMARY KEY(name)
);
#@ _CREATE_TABLE_

INSERT INTO roster (name, jersey_num)
  VALUES
    ('Lynne','29'),
    ('Ella','0'),
    ('Elizabeth','100'),
    ('Nancy','00'),
    ('Jean','8'),
    ('Sherry','47')
;

# unsorted selection
SELECT * FROM roster;
# sorting by jersey number, lexically
SELECT * FROM roster ORDER BY jersey_num;
# sorting by jersey number, numerically
SELECT * FROM roster ORDER BY jersey_num+0;
