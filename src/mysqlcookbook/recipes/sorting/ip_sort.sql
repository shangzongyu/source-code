# ip_sort.sql

# Sorting IP numbers (leftmost segment most significant)
# This is based on pulling apart the numbers into four segments and
# converting each to a number so that the sort occurs in numeric order


# lexical sort

SELECT ip FROM hostip ORDER BY ip;

# numeric sort: extract each segment, convert to number, sort left to right

SELECT
  ip,
#@ _SEG_1_
  SUBSTRING_INDEX(SUBSTRING_INDEX(ip,'.',-4),'.',1)
#@ _SEG_1_
  AS seg1,
#@ _SEG_2_
  SUBSTRING_INDEX(SUBSTRING_INDEX(ip,'.',-3),'.',1)
#@ _SEG_2_
  AS seg2,
#@ _SEG_3_
  SUBSTRING_INDEX(SUBSTRING_INDEX(ip,'.',-2),'.',1)
#@ _SEG_3_
  AS seg3,
#@ _SEG_4_
  SUBSTRING_INDEX(ip,'.',-1)
#@ _SEG_4_
  AS seg4
FROM hostip
ORDER BY
  SUBSTRING_INDEX(SUBSTRING_INDEX(ip,'.',-4),'.',1)+0,
  SUBSTRING_INDEX(SUBSTRING_INDEX(ip,'.',-3),'.',1)+0,
  SUBSTRING_INDEX(SUBSTRING_INDEX(ip,'.',-2),'.',1)+0,
  SUBSTRING_INDEX(ip,'.',-1)+0
;
