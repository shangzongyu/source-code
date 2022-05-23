# is_leap_year.sql

# is_leap_year(year) returns true/false to indicate whether year is a leap
# year. Requires 4-digit year value (e.g., "1993", not "93").

DROP FUNCTION IF EXISTS is_leap_year;
CREATE FUNCTION is_leap_year(year INT)
RETURNS BOOLEAN DETERMINISTIC
RETURN (year % 4 = 0) AND (year % 100 <> 0 OR year % 400 = 0);

SELECT is_leap_year(1899); -- should return 0
SELECT is_leap_year(1900); -- should return 0
SELECT is_leap_year(1999); -- should return 0
SELECT is_leap_year(2000); -- should return 1
SELECT is_leap_year(1963); -- should return 0
SELECT is_leap_year(1964); -- should return 1

