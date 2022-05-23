# sales.sql

# Sales-volume data (used to demonstrate imperfectly-related
# datasets in joins chapter)

# Sales region table

DROP TABLE IF EXISTS sales_region;
#@ _CREATE_TABLE_
CREATE TABLE sales_region
(
  region_id INT UNSIGNED NOT NULL,
  name      VARCHAR(30) NOT NULL,
  PRIMARY KEY(region_id)
);
#@ _CREATE_TABLE_

# Sales volume table

DROP TABLE IF EXISTS sales_volume;
#@ _CREATE_TABLE_
CREATE TABLE sales_volume
(
  id         INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  region_id  INT UNSIGNED NOT NULL,
  year       INT NOT NULL,
  quarter    INT NOT NULL,
  volume     INT NOT NULL
);
#@ _CREATE_TABLE_

INSERT INTO sales_region (region_id, name) VALUES
(1, 'London, United Kingdom'),
(2, 'Madrid, Spain'),
(3, 'Berlin, Germany'),
(4, 'Athens, Greece');

INSERT INTO sales_volume (region_id, year, quarter, volume) VALUES
(1, 2014, 1, 100400),
(1, 2014, 2, 120000),
(3, 2014, 1, 280000),
(3, 2014, 2, 250000),
(5, 2014, 1, 18000),
(5, 2014, 2, 32000);


SELECT * FROM sales_region ORDER BY region_id;;
SELECT * FROM sales_volume ORDER BY region_id, year, quarter;

SELECT 'sales regions not reporting in sales volume data';
SELECT sales_region.*
FROM sales_region LEFT JOIN sales_volume
  ON sales_region.region_id = sales_volume.region_id
WHERE sales_volume.region_id IS NULL
ORDER BY sales_region.region_id;

SELECT 'sales volume rows with unknown sales region';
SELECT sales_volume.*
FROM sales_volume LEFT JOIN sales_region
  ON sales_volume.region_id = sales_region.region_id
WHERE sales_region.region_id IS NULL
ORDER BY sales_volume.region_id;
