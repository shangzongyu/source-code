# correlation.sql

# Compute correllation coefficient r

# Use age and score in the testscore table; X = age, Y = score

# Calculate terms needed

SELECT
  @n := COUNT(score) AS N,
  @sumX := SUM(age) AS 'X sum',
  @sumXX := SUM(age*age) AS 'X sum of squares',
  @sumY := SUM(score) AS 'Y sum',
  @sumYY := SUM(score*score) AS 'Y sum of squares',
  @sumXY := SUM(age*score) AS 'X*Y sum'
FROM testscore\G

# Compute regression slope b

SELECT @r :=
  (@n*@sumXY - @sumX*@sumY)
  / SQRT((@n*@sumXX - @sumX*@sumX) * (@n*@sumYY - @sumY*@sumY))
  AS correlation;
