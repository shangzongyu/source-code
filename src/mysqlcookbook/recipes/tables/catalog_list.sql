# catalog_list.sql

# Table of people who have signed up to received periodic product catalog
# mailings

DROP TABLE IF EXISTS catalog_list;
#@ _CREATE_TABLE_
CREATE TABLE catalog_list
(
  last_name   CHAR(40) NOT NULL,
  first_name  CHAR(40) NOT NULL,
  street      CHAR(40) NOT NULL
);
#@ _CREATE_TABLE_

INSERT INTO catalog_list (first_name, last_name, street)
  VALUES
    ('Jim','Isaacson','515 Fordam St., Apt. 917'),
    ('Wallace','Baxter','57 3rd Ave.'),
    ('Taylor','McTavish','432 River Run'),
    ('Marlene','Pinter','9 Sunset Trail'),
    ('WALLACE','BAXTER','57 3rd Ave.'),
    ('Bartholomew','Brown','432 River Run'),
    ('Marlene','Pinter','9 Sunset Trail'),
    ('Wallace','Baxter','57 3rd Ave., Apt 102')
;

SELECT * FROM catalog_list;
