# weekday_sort.sql

# Sorting a table with days of the week as an ENUM column

# unordered select; they'll be retrieved in insertion order

SELECT day FROM weekday;

# order by day; they'll be retrieved in the order listed in the
# ENUM definition

SELECT day FROM weekday ORDER BY day;

# Force numeric sort (result is same as previous because ENUM values are
# stored numerically)

SELECT day FROM weekday ORDER BY day+0;

# Force lexical sort by converting to string with CONCAT()

SELECT day FROM weekday ORDER BY CONCAT(day);
