# sundays.sql 

# Table to demonstrate finding number of Sundays in a month. 

DROP TABLE IF EXISTS `sundays`;
#@ _CREATE_TABLE_
CREATE TABLE `sundays` (
    year YEAR(4), 
    month INT(2) UNSIGNED ZEROFILL,
    day INT(2) UNSIGNED ZEROFILL
);
#@ _CREATE_TABLE_

# Load data by inserting all Sundays in November 2021

INSERT INTO sundays VALUES(2021,11,7),
                            (2021,11,14),
                            (2021,11,21),
                            (2021,11,28);

# Select the number of Sundays 
SELECT year, month, BIT_COUNT(BIT_OR(1<<day)) AS days FROM sundays
       GROUP BY year,month;
