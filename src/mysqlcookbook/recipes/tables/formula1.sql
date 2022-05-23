# formula1.sql 

# Table to demonstrate finding number of Sundays in a month. 

DROP TABLE IF EXISTS `formula1`;
#@ _CREATE_TABLE_
CREATE TABLE `formula1` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    position INT UNSIGNED,
    no       INT UNSIGNED,
    driver   VARCHAR(25),
    car      VARCHAR(25),
    laps     SMALLINT,
    time     TIMESTAMP(3),
    points   SMALLINT
);
#@ _CREATE_TABLE_

# Load data by inserting all positions

INSERT INTO formula1 VALUES(0,1,77,"Valtteri Bottas","MERCEDES",58,"2021-10-08 1:31:04.103",26);
INSERT INTO formula1 VALUES(0,2,33,"Max Verstappen","RED BULL RACING HONDA",58,"2021-10-08 1:45:58.243",18);
INSERT INTO formula1 VALUES(0,3,11,"Sergio Perez","RED BULL RACING HONDA",58,"2021-10-08 1:46:10.342",15);


# With CTE

SELECT MIN(time) from formula1 into @fastest;
# Select the race standings
WITH time_gap AS (
  SELECT
    position,
    car,
    driver,
    time,
    TIMESTAMPDIFF(SECOND, time , @fastest) AS seconds
  FROM formula1
),
 
differences AS (
  SELECT
    position as pos,
    driver,
    car,
    time,
    seconds,
    MOD(seconds, 60) AS seconds_part,
    MOD(seconds, 3600) AS minutes_part
  FROM time_gap
)
 
SELECT
  pos,
  driver,
  time,
  CONCAT(
    FLOOR(minutes_part / 60), ' min ',
    SUBSTRING_INDEX(SUBSTRING_INDEX(seconds_part,'-',2),'-',-1),' secs'
  ) AS difference
FROM differences;
# Formatted select

select position as pos,
        no,
        driver,
        car,
        laps,
        date_format(time,'%H:%i:%s:%f') as time,
         points as pts
   from formula1 ORDER BY time;
