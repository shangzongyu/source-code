# boolmode.sql

SELECT COUNT(*) AS 'good' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('good');
SELECT COUNT(*) AS 'great' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('great');
SELECT COUNT(*) AS 'good or great' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('good great');
SELECT COUNT(*) AS 'good' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('+good' IN BOOLEAN MODE);
SELECT COUNT(*) AS 'great' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('+great' IN BOOLEAN MODE);

# The number of verses above containing either good or great
# should be equal to the sum of the next three statements, which
# count the number of verses containing both names, just one name,
# or just the other name.

SELECT COUNT(*) AS 'good and great' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('+good +great' IN BOOLEAN MODE);
SELECT COUNT(*) AS 'good, not great' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('+good -great' IN BOOLEAN MODE);
SELECT COUNT(*) AS 'great, not good' FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('-good +great' IN BOOLEAN MODE);
