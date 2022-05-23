# passtbl.sql

DROP TABLE IF EXISTS `passtbl`;
#@ _CREATE_TABLE_
CREATE TABLE `passtbl` (
  `email` varchar(60) NOT NULL,
  `password` varbinary(60) NOT NULL,
  PRIMARY KEY (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

SELECT * FROM passtbl;
