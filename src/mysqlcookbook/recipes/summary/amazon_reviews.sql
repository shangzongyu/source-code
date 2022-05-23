# amazon_reviews.sql

# Various ways of counting reviews in Amazon Reviews 

# Shortest reviews from product sample

SELECT MIN(CHAR_LENGTH(reviews_virtual)) FROM reviews;

# Shortest views matching product details

SELECT JSON_EXTRACT(appliences_review, "$. reviewTime") as ReviewTime,
       JSON_EXTRACT(appliences_review, "$.reviewerID") as ReviwerID, 
       JSON_EXTRACT(appliences_review, "$.asin") as ProductID,
       JSON_EXTRACT(appliences_review, "$.overall") as Rating FROM reviews WHERE CHAR_LENGTH(reviews_virtual) = (SELECT MIN(CHAR_LENGTH(reviews_virtual)) FROM reviews);


