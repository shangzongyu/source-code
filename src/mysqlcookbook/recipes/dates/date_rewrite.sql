# date_rewrite.sql

SET @d = '1956-03-07'
;
SELECT DATE_FORMAT(@d,'%m-%d-%Y')
;
SELECT DATE_FORMAT(@d,'%c-%e-%y')
;
SELECT DATE_FORMAT(@d,'%M %e, %Y')
;

SET @t = '13:47:53'
;
SELECT TIME_FORMAT(@t,'%h-%H-%s')
;
