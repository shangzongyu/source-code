# drawing.sql

DROP TABLE IF EXISTS drawing;
#@ _CREATE_TABLE_
CREATE TABLE drawing (
  entry int unsigned NOT NULL,
  PRIMARY KEY(entry)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#@ _CREATE_TABLE_

INSERT INTO `drawing` VALUES 
  (14557),
  (15865),
  (20009),
  (7597),
  (18811),
  (16586),
  (6782),
  (23553),
  (18954),
  (29795),
  (13551),
  (16376),
  (25382),
  (21556),
  (14916),
  (18218),
  (10879),
  (133),
  (14971),
  (32183),
  (32617),
  (19858),
  (16985),
  (30496),
  (3079),
  (14767),
  (13573),
  (25064),
  (1006),
  (3713),
  (21562),
  (21642),
  (15155),
  (7369),
  (25875),
  (22304)
;

SELECT * FROM drawing;
