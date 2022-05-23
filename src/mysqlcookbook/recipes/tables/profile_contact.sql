# profile_contact.sql

DROP TABLE IF EXISTS profile_contact;
#@ _CREATE_TABLE_
CREATE TABLE profile_contact
(
  id           INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  profile_id   INT UNSIGNED NOT NULL, # ID from profile table
  service      VARCHAR(20) NOT NULL,  # social media service name
  contact_name VARCHAR(25) NOT NULL,  # name to use for contacting person
  INDEX (profile_id)
);
#@ _CREATE_TABLE_



INSERT INTO profile_contact
    (profile_id, service, contact_name)
  VALUES
    (1, 'Twitter', 'user1-twtrid'),
    (1, 'Facebook', 'user1-fbid'),
    (2, 'Twitter', 'user2-fbrid'),
    (2, 'Facebook', 'user2-msnid'),
    (2, 'LinkedIn', 'user2-lnkdid'),
    (4, 'LinkedIn', 'user4-lnkdid')
;

SELECT * FROM profile_contact;
