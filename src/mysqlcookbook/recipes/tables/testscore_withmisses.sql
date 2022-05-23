# testscore_withmisses.sql

DROP TABLE IF EXISTS `testscore_withmisses`;
#@ _CREATE_TABLE_
CREATE TABLE `testscore_withmisses` (
  `subject` int unsigned NOT NULL AUTO_INCREMENT,
  `score` int DEFAULT NULL,
  PRIMARY KEY (`subject`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `testscore_withmisses` VALUES 
  (1,38),
  (2,NULL),
  (3,47),
  (4,NULL),
  (5,37),
  (6,45),
  (7,54),
  (8,NULL),
  (9,40),
  (10,49);

SELECT * FROM testscore_withmisses;
