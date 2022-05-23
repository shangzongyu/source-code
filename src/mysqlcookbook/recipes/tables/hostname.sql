# hostname.sql

# sorting host names in domain order (rightmost segment most significant)

DROP TABLE IF EXISTS hostname;
CREATE TABLE hostname
(
  name  VARCHAR(64),
  PRIMARY KEY(name)
);

INSERT INTO hostname (name)
  VALUES
    ('svn.php.net'),
    ('dbi.perl.org'),
    ('lists.mysql.com'),
    ('mysql.com'),
    ('jakarta.apache.org'),
    ('www.kitebird.com')
;

SELECT * FROM hostname;
