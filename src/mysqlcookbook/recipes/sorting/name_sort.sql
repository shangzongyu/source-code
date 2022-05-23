# name_sort.sql

# display names with last name first

SELECT last_name, first_name FROM name
ORDER BY last_name, first_name;

# display names as single string, first name first, but sorted by last
# name first

SELECT CONCAT(first_name,' ',last_name) AS full_name
FROM name
ORDER BY last_name, first_name;

# display names as single string, first name first, but sorted to put
# longest names first

SELECT CONCAT(first_name,' ',last_name) AS full_name
FROM name
ORDER BY LENGTH(CONCAT(first_name,' ',last_name)) DESC;
