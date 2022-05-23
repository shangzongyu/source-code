# poi.sql

# Create a table with all fields

DROP TABLE IF EXISTS poi;
#@ _CREATE_TABLE_
CREATE TABLE `poi` (
  `poi_id` int unsigned NOT NULL AUTO_INCREMENT,
  `position` point NOT NULL /*!80003 SRID 4326 */,
  `name` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`poi_id`),
  SPATIAL KEY `position` (`position`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

# Load data
INSERT INTO poi VALUES (1, ST_GeomFromText('POINT(41.0211 29.0041)', 4326), 'Maiden\'s Tower');

INSERT INTO poi VALUES (2, ST_GeomFromText('POINT(41.0256 28.9742)', 4326), 'Galata Tower');
