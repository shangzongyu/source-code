# color_sort.sql

# sorting example showing how an ENUM column can replace the need
# to use FIELD() for category-name sorting

# This will sort color names in lexical order

SELECT name FROM color ORDER BY name;

# Sort color names in "rainbow" (or "Roy G. Biv") order using FIELD():

SELECT name FROM color
ORDER BY
FIELD(name,'red','orange','yellow','green','blue','indigo','violet')
;

# Convert color column to an ENUM with the color listed in rainbow order

ALTER TABLE color
MODIFY name ENUM('red','orange','yellow','green','blue','indigo','violet')
;

# This will sort color names in ENUM (roygbiv) order

SELECT name FROM color ORDER BY name;
