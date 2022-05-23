# regression.sql

# Compute least-squares regression line Y = bX + a

# Use age and score in the testscore table; X = age, Y = score

# Calculate terms needed

SELECT
  @n := COUNT(score) AS N,
  @meanX := AVG(age) AS 'X mean',
  @sumX := SUM(age) AS 'X sum',
  @sumXX := SUM(age*age) AS 'X sum of squares',
  @meanY := AVG(score) AS 'Y mean',
  @sumY := SUM(score) AS 'Y sum',
  @sumYY := SUM(score*score) AS 'Y sum of squares',
  @sumXY := SUM(age*score) AS 'X*Y sum'
FROM testscore\G

# Compute regression slope b

SELECT @b :=
  (@n*@sumXY - @sumX*@sumY) / (@n*@sumXX - @sumX*@sumX)
  AS slope;

# Compute regression intercept a

SELECT @a :=
  (@meanY - @b*@meanX)
  AS intercept;

# Display regression equation

SELECT CONCAT('Y = ',@b,'X + ',@a) AS 'least-squares regression';
