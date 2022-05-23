# weekday.sql

# Create a table with days of the week as an ENUM column

DROP TABLE IF EXISTS weekday;
#@ _CREATE_TABLE_
CREATE TABLE weekday
(
  day ENUM('Sunday','Monday','Tuesday','Wednesday',
           'Thursday','Friday','Saturday')
);
#@ _CREATE_TABLE_

# insert one record for each day of the week (insert in random order)

INSERT INTO weekday (day) VALUES('Monday'),('Friday'),
('Tuesday'),('Sunday'),('Thursday'),('Saturday'),('Wednesday');

SELECT * FROM weekday;
