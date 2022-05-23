# housewares_sort.sql

# housewares catalogs:
# housewares: fixed-length id substrings
# housewares3: like housewares, but serial number part of id
#   has no leading zeros (variable-length id substrings)
# housewares4: id in n-n-n-n format

SELECT id, LEFT(id,3), MID(id,4,5), RIGHT(id,2) FROM housewares;

SELECT id, LEFT(id,3), SUBSTRING(id,4) + 0, RIGHT(id,2) FROM housewares3;

# Seek from the left, then yank the rightmost segment

SELECT
  id,
#@ _SEG_1_1_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',1),'-',-1)
#@ _SEG_1_1_
  AS seg1,
#@ _SEG_2_1_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',2),'-',-1)
#@ _SEG_2_1_
  AS seg2,
#@ _SEG_3_1_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',3),'-',-1)
#@ _SEG_3_1_
  AS seg3,
#@ _SEG_4_1_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',4),'-',-1)
#@ _SEG_4_1_
  AS seg4
FROM housewares4
;

# Seek from the right, then yank the leftmost segment

SELECT
  id,
#@ _SEG_1_2_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',-4),'-',1)
#@ _SEG_1_2_
  AS seg1,
#@ _SEG_2_2_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',-3),'-',1)
#@ _SEG_2_2_
  AS seg2,
#@ _SEG_3_2_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',-2),'-',1)
#@ _SEG_3_2_
  AS seg3,
#@ _SEG_4_2_
  SUBSTRING_INDEX(SUBSTRING_INDEX(id,'-',-1),'-',1)
#@ _SEG_4_2_
  AS seg4
FROM housewares4
;

# Optimized forms for leftmost, rightmost segments

SELECT
  id,
#@ _SEG_1_OPT_
  SUBSTRING_INDEX(id,'-',1)
#@ _SEG_1_OPT_
  AS seg1,
#@ _SEG_4_OPT_
  SUBSTRING_INDEX(id,'-',-1)
#@ _SEG_4_OPT_
  AS seg4
FROM housewares4
;

# A join based on a partial column in one table with a column in another table

SELECT hw_category.name, housewares.*
FROM housewares INNER JOIN hw_category
WHERE LEFT(housewares.id,3) = hw_category.abbrev
;
