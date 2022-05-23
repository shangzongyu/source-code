# detail_count.sql

# Show two ways of counting detail records per master record

DROP TABLE IF EXISTS parent;
DROP TABLE IF EXISTS child;
CREATE TABLE parent
(
  p_id  INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (p_id)
)
;

CREATE TABLE child
(
  p_id  INT UNSIGNED NOT NULL,
  c_id  INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (c_id)
)
;

INSERT INTO parent (p_id) VALUES(NULL);
INSERT INTO child (p_id, c_id)
VALUES(LAST_INSERT_ID(),NULL), (LAST_INSERT_ID(),NULL);
INSERT INTO parent (p_id) VALUES(NULL);
INSERT INTO parent (p_id) VALUES(NULL);
INSERT INTO child (p_id, c_id)
VALUES(LAST_INSERT_ID(),NULL),
(LAST_INSERT_ID(),NULL),
(LAST_INSERT_ID(),NULL);

SELECT * FROM parent;
SELECT * FROM child;

# Counting with regular join, which produces no records for no-child parents

SELECT parent.p_id, COUNT(child.c_id)
FROM parent INNER JOIN child
WHERE parent.p_id = child.p_id
GROUP BY parent.p_id
;

# Counting with LEFT JOIN and COUNT(*), which produces the incorrect result

SELECT parent.p_id, COUNT(*)
FROM parent LEFT JOIN child ON parent.p_id = child.p_id
GROUP BY parent.p_id
;

# Counting with LEFT JOIN and COUNT(c_id), which produces the correct result

SELECT parent.p_id, COUNT(child.c_id)
FROM parent LEFT JOIN child ON parent.p_id = child.p_id
GROUP BY parent.p_id
;
