# rand_names.sql

DROP TABLE IF EXISTS `rand_names`;
#@ _CREATE_TABLE_
CREATE TABLE `rand_names` (
  `name` varchar(100) NOT NULL,
  PRIMARY KEY(name)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `rand_names` VALUES 
  ('Patrick'),
  ('Penelope'),
  ('Pertinax'),
  ('Polly');

SELECT * FROM rand_names;
