# cust_invoice.sql

# Use BEFORE INSERT trigger to provide nonconstant (dynamic) default value
# for a column.


DROP TABLE IF EXISTS cust_invoice;
#@ _CREATE_TABLE_1_
CREATE TABLE cust_invoice
(
  id       INT NOT NULL AUTO_INCREMENT,
  state    CHAR(2),       # customer state of residence
  amount   DECIMAL(10,2), # sale amount
  tax_rate DECIMAL(3,2),  # sales tax rate at time of purchase
#@ _CREATE_TABLE_1_
#@ _CREATE_TABLE_2_
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_2_

# Set up a BEFORE INSERT trigger that calculates the tax rate for
# the sale and stores it in the tax_rate column.

#@ _BEFORE_INSERT_TRIGGER_1_
CREATE TRIGGER bi_cust_invoice BEFORE INSERT ON cust_invoice
FOR EACH ROW SET NEW.tax_rate = sales_tax_rate(NEW.state);
#@ _BEFORE_INSERT_TRIGGER_1_

# Create a new row

INSERT INTO cust_invoice (state,amount) VALUES('NY',100);
SELECT * FROM cust_invoice WHERE id = LAST_INSERT_ID();
