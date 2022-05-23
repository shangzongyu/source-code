# dtdiff.sql: calculating time differences between date+time values

#@ _CALC_DIFFERENCE_
SELECT val1, val2,
UNIX_TIMESTAMP(val2) - UNIX_TIMESTAMP(val1) AS 'seconds diff',
SEC_TO_TIME(UNIX_TIMESTAMP(val2) - UNIX_TIMESTAMP(val1)) AS 'TIME diff'
FROM dtdiff;
#@ _CALC_DIFFERENCE_
