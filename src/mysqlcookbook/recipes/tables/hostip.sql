# hostip.sql

# Sorting IP numbers (leftmost segment most significant)
# This is based on pulling apart the numbers into four segments and
# converting each to a number so that the sort occurs in numeric order


DROP TABLE IF EXISTS hostip;
CREATE TABLE hostip
(
  ip  VARCHAR(64),
  PRIMARY KEY(ip)
);

INSERT INTO hostip (ip)
  VALUES
    ('127.0.0.1'),
    ('192.168.0.2'),
    ('192.168.0.10'),
    ('192.168.1.2'),
    ('192.168.1.10'),
    ('255.255.255.255'),
    ('21.0.0.1')
;

SELECT * FROM hostip ORDER BY ip;
