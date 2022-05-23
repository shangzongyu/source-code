# ranks.sql

DROP TABLE IF EXISTS `ranks`;
#@ _CREATE_TABLE_
CREATE TABLE `ranks` (
  `score` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `ranks` VALUES (5),(4),(4),(3),(2),(2),(2),(1);

SELECT * FROM ranks;

# Assign ranks to the values in a table

# Method one just assigns successive ranks to each successive distinct
# value.

# Show the values in order, highest values first

SELECT score FROM ranks ORDER BY score DESC;

# Assign ranks to each of the distinct values

DROP TABLE IF EXISTS tmp;
CREATE TABLE tmp (`rank` INT NOT NULL AUTO_INCREMENT, PRIMARY KEY (`rank`))
SELECT DISTINCT score FROM ranks ORDER BY score DESC;

SELECT tmp.`rank`, ranks.score
FROM tmp INNER JOIN ranks
WHERE tmp.score = ranks.score
ORDER BY tmp.`rank`, ranks.score DESC;

# Assign ranks using position (row number) within the set of values,
# except that tied values all get the rank accorded the first of them.

SET @rownum := 0;
SET @rank := 0;
SET @prev_score := NULL;
SELECT
  @rownum := @rownum + 1 AS `row`,
  @rank := IF(@prev_score!=score,@rownum,@rank) AS `rank`,
  @prev_score := score AS score
FROM ranks ORDER BY score DESC;

# Do the same thing with some joins

DROP TABLE IF EXISTS tmp;
CREATE TABLE tmp (`rank` INT NOT NULL AUTO_INCREMENT, PRIMARY KEY (`rank`))
SELECT DISTINCT score, COUNT(score) AS count
FROM ranks GROUP BY score ORDER BY score DESC;

SELECT * FROM tmp;

DROP TABLE IF EXISTS `rank`;
CREATE TABLE `rank`
SELECT
  t1.`rank`,
  SUM(t2.count) AS sum,
  SUM(t2.count) - t1.count + 1 AS adjsum
FROM tmp AS t1 INNER JOIN tmp AS t2
WHERE t1.`rank` >= t2.`rank`
GROUP BY t1.`rank`
ORDER BY t1.rank;


SELECT `rank`.`rank`, `rank`.adjsum, ranks.score
FROM `rank` INNER JOIN tmp INNER JOIN ranks
WHERE `rank`.`rank` = tmp.`rank` and tmp.score = ranks.score
ORDER BY `rank`.`rank`, ranks.score DESC;

