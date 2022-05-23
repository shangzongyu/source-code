# domain_sort.sql

# sorting host names in domain order (rightmost segment most significant)

SELECT
  name,
#@ _SEG_1_
  SUBSTRING_INDEX(SUBSTRING_INDEX(name,'.',-3),'.',1)
#@ _SEG_1_
  AS leftmost,
#@ _SEG_2_
  SUBSTRING_INDEX(SUBSTRING_INDEX(name,'.',-2),'.',1)
#@ _SEG_2_
  AS middle,
#@ _SEG_3_
  SUBSTRING_INDEX(name,'.',-1)
#@ _SEG_3_
  AS rightmost
FROM hostname;

SELECT
  name,
  SUBSTRING_INDEX(SUBSTRING_INDEX(CONCAT('..',name),'.',-3),'.',1)
  AS leftmost,
  SUBSTRING_INDEX(SUBSTRING_INDEX(CONCAT('..',name),'.',-2),'.',1)
  AS middle,
  SUBSTRING_INDEX(CONCAT('..',name),'.',-1)
  AS rightmost
FROM hostname
ORDER BY
  SUBSTRING_INDEX(CONCAT('..',name),'.',-1),
  SUBSTRING_INDEX(SUBSTRING_INDEX(CONCAT('..',name),'.',-2),'.',1),
  SUBSTRING_INDEX(SUBSTRING_INDEX(CONCAT('..',name),'.',-3),'.',1)
;
