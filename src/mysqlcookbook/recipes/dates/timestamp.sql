# timestamp.sql

SET @ts = '19970702123742';
SELECT
@ts,
DATE_FORMAT(@ts,'%Y-%m-%d %h:%s')
;
