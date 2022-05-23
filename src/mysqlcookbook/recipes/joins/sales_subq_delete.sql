# sales_subq_delete.sql

# This script illustrates how to use subqueries to identify mismatches
# between the parent (sales_region) and child (sales_volume) tables.
# These records represent unattached records in each table.  Then it
# uses similar DELETE statements to remove the unattached records.

# Note: Before running this script, you should make sure that the tables
# are loaded with their original rows.  Do this by running the script in
# the tables/sales.sql file.

# Show original tables

SELECT * FROM sales_region;
SELECT * FROM sales_volume;

# Identify those records that have no match

#@ _IDENTIFY_CHILDLESS_PARENTS_
SELECT region_id AS 'unmatched region row IDs'
FROM sales_region
WHERE region_id NOT IN (SELECT region_id FROM sales_volume);
#@ _IDENTIFY_CHILDLESS_PARENTS_

#@ _IDENTIFY_PARENTLESS_CHILDREN_
SELECT region_id AS 'unmatched volume row IDs'
FROM sales_volume
WHERE region_id NOT IN (SELECT region_id FROM sales_region);
#@ _IDENTIFY_PARENTLESS_CHILDREN_

# Delete those records that have no match

#@ _DELETE_CHILDLESS_PARENTS_
DELETE FROM sales_region
WHERE region_id NOT IN (SELECT region_id FROM sales_volume);
#@ _DELETE_CHILDLESS_PARENTS_

#@ _DELETE_PARENTLESS_CHILDREN_
DELETE FROM sales_volume
WHERE region_id NOT IN (SELECT region_id FROM sales_region);
#@ _DELETE_PARENTLESS_CHILDREN_

# Show resulting tables

SELECT * FROM sales_region;
SELECT * FROM sales_volume;

