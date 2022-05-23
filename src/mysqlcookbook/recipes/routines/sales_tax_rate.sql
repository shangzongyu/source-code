# sales_tax_rate.sql

# sales_tax_rate(): Given state abbreviation, look up tax rate from
# sales_tax_rate table.

# sales_tax(): Given sale amount and state abbreviation, compute
# sales tax by looking up appropriate tax rate in sales_tax_rate
# table.

DROP FUNCTION IF EXISTS sales_tax_rate;
delimiter $$
#@ _SALES_TAX_RATE_FUNC_
CREATE FUNCTION sales_tax_rate(state_code CHAR(2))
RETURNS DECIMAL(3,2) READS SQL DATA
BEGIN
  DECLARE rate DECIMAL(3,2);
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET rate = 0;
  SELECT tax_rate INTO rate FROM sales_tax_rate WHERE state = state_code;
  RETURN rate;
END;
#@ _SALES_TAX_RATE_FUNC_
$$
delimiter ;

SELECT sales_tax_rate('NY'), sales_tax_rate('VT');
# Rate for nonexistent state
SELECT sales_tax_rate('ZZ');

DROP FUNCTION IF EXISTS sales_tax;
#@ _SALES_TAX_FUNC_
CREATE FUNCTION sales_tax(state_code CHAR(2), sales_amount DECIMAL(10,2))
RETURNS DECIMAL(10,2) READS SQL DATA
RETURN sales_amount * sales_tax_rate(state_code);
#@ _SALES_TAX_FUNC_

SELECT sales_tax('NY',150.00), sales_tax('VT',150.00);
# Tax for nonexistent state
SELECT sales_tax('ZZ',150.00);
