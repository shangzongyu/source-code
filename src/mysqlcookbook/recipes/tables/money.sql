# money.sql

DROP TABLE IF EXISTS `money`;
#@ _CREATE_TABLE_
CREATE TABLE `money` (
  `name` char(5)  NOT NULL,
  `amt` int DEFAULT NULL,
  PRIMARY KEY(name)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `money` VALUES 
  ('Eve',10),
  ('Ida',0)
;

SELECT * FROM money;
