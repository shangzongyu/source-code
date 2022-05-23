# sum_expt.sql

# expt table summary queries

# number of records, and non-NULL scores
SELECT COUNT(*), COUNT(score) FROM expt;
# number of NULL scores
SELECT COUNT(*) - COUNT(score) FROM expt;
# number of records per subject
SELECT subject, COUNT(*) FROM expt GROUP BY subject;
# number of records per test
SELECT test, COUNT(*) FROM expt GROUP BY test;
# number of missing score per test
SELECT test, COUNT(*) - COUNT(score) FROM expt GROUP BY test;

SELECT subject, COUNT(score), SUM(score), AVG(score)
FROM expt GROUP BY subject;
SELECT test, COUNT(score), SUM(score), AVG(score)
FROM expt GROUP BY test;
