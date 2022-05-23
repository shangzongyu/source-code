# load-passwd.sql

DELETE FROM passwd;
#@ _FRAG_
LOAD DATA LOCAL INFILE 'passwd.txt' INTO TABLE passwd
FIELDS TERMINATED BY ':';
#@ _FRAG_

SELECT * FROM passwd;
