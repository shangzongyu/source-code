# reviews.sql 

# Table to hold Amazon Reviews Data - Appliences 

DROP TABLE IF EXISTS`reviews`;
#@ _CREATE_TABLE_
CREATE TABLE `reviews` (  
   `id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT, #id of the review entry
   `appliences_review` JSON NOT NULL, # json data imported 
     PRIMARY KEY (`id`)
);
#@ _CREATE_TABLE_

# Load data with python_json_load.py

ALTER TABLE `reviews` 
  ADD COLUMN `reviews_virtual` TEXT 
    GENERATED ALWAYS AS (`appliences_review` ->> '$.reviewText') STORED NOT NULL;
ALTER TABLE `reviews` ADD FULLTEXT idx_ft_json(reviews_virtual);
ALTER TABLE `reviews` 
  ADD COLUMN `reviews_virtual_vote` VARCHAR(10) 
    GENERATED ALWAYS AS (`appliences_review` ->> '$.vote') STORED;
ALTER TABLE `reviews`
  ADD COLUMN `reviews_virtual_overall` VARCHAR(10)
    GENERATED ALWAYS AS (`appliences_review` ->> '$.overall') STORED;
ALTER TABLE `reviews`
  ADD COLUMN `reviews_virtual_verified` VARCHAR(10)
    GENERATED ALWAYS AS (`appliences_review` ->> '$.verified') STORED;

# Add other indexes to reviews table. 

ALTER TABLE reviews 
  ADD INDEX idx_vote (reviews_virtual_vote), 
  ADD INDEX idx_overall(reviews_virtual_overall), 
  ADD INDEX idx_verified(reviews_virtual_verified)
;
