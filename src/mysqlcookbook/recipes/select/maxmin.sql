# maxmin.sql

# Queries that use MAX() or MIN()

# Largest message size

SELECT MAX(size) FROM mail;

# Information about the largest message

SELECT @max := MAX(size) FROM mail;
SELECT * FROM mail WHERE size = @max;

# Alternatively...

SELECT * FROM mail ORDER BY size DESC LIMIT 1;

# Largest message per sender

SELECT srcuser, MAX(size) FROM mail GROUP BY srcuser;

# Largest message between each sender/recipient pair

SELECT srcuser, dstuser, MAX(size)
FROM mail
GROUP BY srcuser, dstuser;

# Largest message per day (you can group by expression result)

SELECT DATE_FORMAT(t,'%Y-%m-%d') AS day, MAX(size)
FROM mail
GROUP BY day;
