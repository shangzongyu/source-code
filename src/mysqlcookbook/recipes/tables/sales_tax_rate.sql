# sales_tax_rate.sql

DROP TABLE IF EXISTS sales_tax_rate;
#@ _CREATE_TABLE_
CREATE TABLE sales_tax_rate
(
  state    CHAR(2) NOT NULL,     # 2-letter abbreviation
  tax_rate DECIMAL(3,2),         # Tax rate (0.00 .. 1.00)
  PRIMARY KEY (state)
);
#@ _CREATE_TABLE_

# Read in tax rates.
# NOTE: These are fake values.

SELECT 'Loading sales_tax_rate_table...' As Message;
SELECT 'Note: These tax rates are fictitious' As Message;
LOAD DATA LOCAL INFILE 'sales_tax_rate.txt' INTO TABLE sales_tax_rate;
