# image.sql

# create a table to hold images

DROP TABLE IF EXISTS image;
#@ _CREATE_TABLE_
CREATE TABLE image
(
  id    INT UNSIGNED NOT NULL AUTO_INCREMENT, # image ID number
  name  VARCHAR(30) NOT NULL,                 # image name
  type  VARCHAR(20) NOT NULL,                 # image MIME type
  data  LONGBLOB NOT NULL,                    # image data
  PRIMARY KEY (id),                           # id and name are unique
  UNIQUE (name)
);
#@ _CREATE_TABLE_
