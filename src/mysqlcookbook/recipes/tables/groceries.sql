# groceries.sql

DROP TABLE IF EXISTS `groceries`;
#@ _CREATE_TABLE_
CREATE TABLE `groceries` (
  `id` int NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `forbidden_after` time DEFAULT NULL,
  `forbidden_before` time DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `groceries` VALUES 
  (1,'bread',NULL,NULL),
  (2,'cucumber',NULL,NULL),
  (3,'cheese',NULL,NULL),
  (4,'pasta',NULL,NULL),
  (5,'oil',NULL,NULL),
  (6,'wine','22:00:00','06:00:00'),
  (7,'beer','22:00:00','06:00:00'),
  (8,'water',NULL,NULL);

SELECT * FROM groceries;
