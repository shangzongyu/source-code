# age.sql: demonstrate age-in-years and age-in-months calculations

# age in years

SELECT
  name, birth, CURDATE() AS today,
#@ _AGE_IN_YEARS_1_
  (YEAR(CURDATE()) - YEAR(birth)) - (RIGHT(CURDATE(),5) < RIGHT(birth,5))
#@ _AGE_IN_YEARS_1_
  AS 'age in years',
#@ _AGE_IN_YEARS_2_
  (YEAR(CURDATE()) - YEAR(birth)) - IF(RIGHT(CURDATE(),5) < RIGHT(birth,5),1,0)
#@ _AGE_IN_YEARS_2_
  AS 'age in years 2'
FROM siblings
;

# age in months, first by extending the technique used in the previous
# statement, and then by extracting the month and day directly rather than
# by using a string comparison

SELECT
  name, birth, CURDATE() AS today,
  (YEAR(CURDATE()) - YEAR(birth)) * 12
  + (MONTH(CURDATE()) - MONTH(birth))
    - IF(RIGHT(CURDATE(),2) < RIGHT(birth,2),1,0)
  AS 'age in months'
FROM siblings
;

SELECT
  name, birth, CURDATE() AS today,
  (YEAR(CURDATE()) - YEAR(birth)) * 12
  + (MONTH(CURDATE()) - MONTH(birth))
    - IF(DAYOFMONTH(CURDATE()) < DAYOFMONTH(birth),1,0)
  AS 'age in months'
FROM siblings
;
