# mailday.sql

# Select mail table records, but show day of week


# Sort lexically by day-of-week name

SELECT DISTINCT DAYNAME(t)
FROM mail
ORDER BY DAYNAME(t)
;

# Sort by day-of-week order (Sunday first, Saturday last)

SELECT DISTINCT DAYNAME FROM
(
  SELECT DAYNAME(t) DAYNAME
  FROM mail
  ORDER BY DAYOFWEEK(t)
) tmp
;

# Like previous, but with Tuesday first, Monday last.  Uses a MOD
# trick to map 3,4,5,6,7,1,2 to 1..7

SELECT DAYNAME FROM
(
  SELECT DAYNAME(t) DAYNAME, AVG(MOD(DAYOFWEEK(t) + 4, 7)) wd
  FROM mail
  GROUP BY DAYNAME
) tmp
ORDER BY wd
;
