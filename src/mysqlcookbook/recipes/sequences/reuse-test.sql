# Test what happens for a given storage engine when AUTO_INCREMENT values are
# deleted from the top of the sequence.
# Edit the ENGINE clause to change the engine.

DROP TABLE IF EXISTS t;
CREATE TABLE t (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id)
) ENGINE = InnoDB;
INSERT INTO t () VALUES(),(),(),();
SELECT 'initial table contents' AS 'action';
SELECT * FROM t;
DELETE FROM t WHERE id > 2;
SELECT 'contents after deleting rows from top' AS 'action';
SELECT * FROM t;
INSERT INTO t () VALUES(),(),(),();
SELECT 'contents after adding new rows' AS 'action';
SELECT * FROM t;
