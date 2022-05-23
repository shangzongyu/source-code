# mailsort.sql

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

# using an alias ...

SELECT DISTINCT DAYNAME(t), DAYOFWEEK(t) AS daynum
FROM mail
ORDER BY daynum
;

# Like previous, but with Monday first, Sunday last.  Uses a MOD
# trick to map 2..7,1 to 1..7

SELECT DAYNAME FROM
(
  SELECT DAYNAME(t) DAYNAME, AVG((DAYOFWEEK(t) + 5) % 7) wd
  FROM mail
  GROUP BY DAYNAME
) tmp
ORDER BY wd
;

# Order by size, display size as strings of the form nnnKB

SELECT CONCAT(FLOOR(size/1024),'K') AS size_in_K
FROM mail
ORDER BY size
;
