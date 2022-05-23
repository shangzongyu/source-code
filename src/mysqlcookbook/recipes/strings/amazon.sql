# amazon.sql

# To find out what those products those had “excellent” keyword in reviews

SELECT JSON_EXTRACT(appliences_review, "$.reviewerID") as ReviwerID,
JSON_EXTRACT(appliences_review, "$.asin") as ProductID,
JSON_EXTRACT(appliences_review, "$.overall") as Rating
from reviews WHERE MATCH(reviews_virtual) AGAINST('excellent') \G

# Occurances of "good" keyword 

SELECT count(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('good');

SELECT count(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('good')
AND reviews_virtual_vote > 5;

SELECT COUNT(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('good')
AND reviews_virtual_overall = 5;

# Additional search counts for different words

SELECT COUNT(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('good')
AND reviews_virtual_overall = 5 AND reviews_virtual_verified = "True";

SELECT COUNT(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('excellent');

SELECT COUNT(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('excellent product');

SELECT COUNT(*) from reviews
WHERE MATCH(reviews_virtual) AGAINST('excellent product for home');

SELECT count(*) from reviews WHERE MATCH(reviews_virtual) AGAINST('amazing');

SELECT count(*) from reviews WHERE MATCH(reviews_virtual) AGAINST('ok');

# Count samples continued

SELECT COUNT(*) AS Total_Reviews,
COUNT(IF(reviews_virtual LIKE '%good%',1,NULL)) AS Good_Reviews,
COUNT(IF(reviews_virtual LIKE '%great%',1,NULL)) AS Great_Reviews,
COUNT(IF(reviews_virtual LIKE '%excellent%',1,NULL)) AS Excellent_Reviews
FROM reviews;

SELECT COUNT(*) FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('good great');

SELECT COUNT(*) FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('good')
AND MATCH(reviews_virtual) AGAINST('great');

SELECT COUNT(*) FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('+good +great' IN BOOLEAN MODE);

SELECT COUNT(*) FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('great product');

SELECT COUNT(*) FROM reviews
WHERE MATCH(reviews_virtual) AGAINST('"great product"' IN BOOLEAN MODE);


