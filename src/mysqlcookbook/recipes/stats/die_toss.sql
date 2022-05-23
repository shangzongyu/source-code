# die_toss.sql

# Toss dice (nonunique output column names)

SELECT d1.num, d2.num FROM die AS d1, die AS d2
ORDER BY RAND() LIMIT 1;

# Toss dice (unique output column names)

SELECT d1.num AS n1, d2.num AS n2 FROM die AS d1, die AS d2
ORDER BY RAND() LIMIT 1;
