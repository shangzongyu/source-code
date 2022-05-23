# testscore_withmisses2.sql

DROP TABLE IF EXISTS `testscore_withmisses2`;
#@ _CREATE_TABLE_
CREATE TABLE `testscore_withmisses2` (
  `subject` int unsigned NOT NULL AUTO_INCREMENT,
  `A` tinyint DEFAULT NULL,
  `B` tinyint DEFAULT NULL,
  `score` int DEFAULT NULL,
  PRIMARY KEY (`subject`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `testscore_withmisses2` VALUES 
  (1,1,1,18),
  (2,1,1,NULL),
  (3,1,1,23),
  (4,1,1,24),
  (5,1,2,17),
  (6,1,2,23),
  (7,1,2,29),
  (8,1,2,32),
  (9,2,1,17),
  (10,2,1,NULL),
  (11,2,1,NULL),
  (12,2,1,25),
  (13,2,2,NULL),
  (14,2,2,33),
  (15,2,2,34),
  (16,2,2,37);

SELECT * FROM testscore_withmisses2;
