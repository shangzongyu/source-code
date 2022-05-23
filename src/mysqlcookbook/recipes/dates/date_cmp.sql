# date_cmp.sql

# Show how to rewrite conditions to avoid placing date-valued columns
# within expressions. (Using the column in an expression nullifies the
# value of any index on the column)

# two ways to find dates occurring within the last month

# date column not used in an expression (good)

SELECT
d, DATE_SUB(CURDATE(),INTERVAL 1 MONTH)
FROM date_val
#@ _LAST_MONTH_GOOD_
WHERE d >= DATE_SUB(CURDATE(),INTERVAL 1 MONTH);
#@ _LAST_MONTH_GOOD_

# date column used in an expression (bad)

SELECT
DATE_ADD(d,INTERVAL 1 MONTH), CURDATE()
FROM date_val
#@ _LAST_MONTH_BAD_
WHERE DATE_ADD(d,INTERVAL 1 MONTH) >= CURDATE();
#@ _LAST_MONTH_BAD_


# two ways to find dates between 1987 and 1991 (inclusive)

# date column not used in an expression (good)

# date column used in an expression (bad)

SELECT * FROM date_val
#@ _YEAR_BAD_
WHERE YEAR(d) >= 1987 AND YEAR(d) <= 1991;
#@ _YEAR_BAD_

SELECT * FROM date_val
#@ _YEAR_HALF_GOOD_
WHERE d >= '1987-01-01' AND YEAR(d) <= 1991;
#@ _YEAR_HALF_GOOD_

SELECT * FROM date_val
#@ _YEAR_HALF_INCORRECT_
WHERE d >= '1987-01-01' AND d <= '1991-01-01';
#@ _YEAR_HALF_INCORRECT_

SELECT * FROM date_val
#@ _YEAR_GOOD_1_
WHERE d >= '1987-01-01' AND d <= '1991-12-31';
#@ _YEAR_GOOD_1_

SELECT * FROM date_val
#@ _YEAR_GOOD_2_
WHERE d >= '1987-01-01' AND d < '1992-01-01';
#@ _YEAR_GOOD_2_

SELECT * FROM date_val
#@ _BIRTHDAY_TODAY_
WHERE MONTH(d) = MONTH(CURDATE()) AND DAYOFMONTH(d) = DAYOFMONTH(CURDATE());
#@ _BIRTHDAY_TODAY_

SELECT * FROM date_val
#@ _BIRTHDAY_THIS_MONTH_
WHERE MONTH(d) = MONTH(CURDATE());
#@ _BIRTHDAY_THIS_MONTH_

SELECT * FROM date_val
#@ _BIRTHDAY_NEXT_MONTH_1_
WHERE MONTH(d) = MONTH(DATE_ADD(CURDATE(),INTERVAL 1 MONTH));
#@ _BIRTHDAY_NEXT_MONTH_1_

SELECT * FROM date_val
#@ _BIRTHDAY_NEXT_MONTH_2_
WHERE MONTH(d) = MOD(MONTH(CURDATE()),12)+1;
#@ _BIRTHDAY_NEXT_MONTH_2_

SELECT * FROM date_val
#@ _BORN_20TH_CENTURY_1_
WHERE YEAR(d) BETWEEN 1900 AND 1999;
#@ _BORN_20TH_CENTURY_1_

SELECT * FROM date_val
#@ _BORN_20TH_CENTURY_2_
WHERE d BETWEEN '1900-01-01' AND '1999-12-31';
#@ _BORN_20TH_CENTURY_2_

SELECT * FROM date_val
#@ _BORN_20TH_CENTURY_3_
WHERE FLOOR((d+0)/10000) BETWEEN 1900 AND 1999;
#@ _BORN_20TH_CENTURY_3_

SELECT * FROM date_val
#@ _BORN_50PLUS_YEARS_AGO_
WHERE d < DATE_SUB(CURDATE(),INTERVAL 50 YEAR);
#@ _BORN_50PLUS_YEARS_AGO_

SELECT * FROM date_val
#@ _OLDER_THAN_50_
WHERE d <= DATE_SUB(CURDATE(),INTERVAL 51 YEAR);
#@ _OLDER_THAN_50_

