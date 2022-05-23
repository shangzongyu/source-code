# event_sort.sql

# day-in-history event sorting


# Sort by day of week

SELECT DAYNAME(date), date, description
FROM occasion
ORDER BY DAYOFWEEK(date);
