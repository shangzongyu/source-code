# add_cities_cols.sql

# Add capital and largest city columns to states table

#@ _ALTER_TABLE_
ALTER TABLE states ADD capital VARCHAR(30), ADD largest VARCHAR(30);
#@ _ALTER_TABLE_
