# httpdlog2.sql

# Apache logging table with vhost column

DROP TABLE IF EXISTS httpdlog2;
#@ _CREATE_TABLE_
CREATE TABLE httpdlog2
(
  id      INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  dt      DATETIME NOT NULL,            # request date
  vhost   VARCHAR(255) NOT NULL,        # destination virtual host
  host    VARCHAR(255) NOT NULL,        # client host
  method  VARCHAR(4) NOT NULL,          # request method (GET, PUT, etc.)
  url     VARCHAR(255)                  # URL path
          CHARACTER SET latin1 COLLATE latin1_general_cs NOT NULL,
  status  INT NOT NULL,                 # request status
  size    INT,                          # number of bytes transferred
  referer VARCHAR(255),                 # referring page
  agent   VARCHAR(255)                  # user agent
);
#@ _CREATE_TABLE_
