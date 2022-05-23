# invoice.sql

DROP TABLE IF EXISTS invoice;
#@ _CREATE_TABLE_INVOICE_
CREATE TABLE invoice
(
  inv_id  INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (inv_id),
  date    DATE NOT NULL
  # ... other columns could go here
  # ... (customer ID, shipping address, etc.)
);
#@ _CREATE_TABLE_INVOICE_

DROP TABLE IF EXISTS inv_item;
#@ _CREATE_TABLE_INV_ITEM_A_
CREATE TABLE inv_item
(
  inv_id    INT UNSIGNED NOT NULL,  # invoice ID (from invoice table)
  INDEX (inv_id),
  qty       INT,                    # quantity
  description VARCHAR(40)           # description
);
#@ _CREATE_TABLE_INV_ITEM_A_

#@ _INSERT_A1_
INSERT INTO invoice (inv_id,date)
  VALUES(NULL,CURDATE());
#@ _INSERT_A1_
#@ _INSERT_A2_
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(LAST_INSERT_ID(),1,'hammer');
#@ _INSERT_A2_
#@ _INSERT_A3_
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(LAST_INSERT_ID(),3,'nails, box');
#@ _INSERT_A3_
#@ _INSERT_A4_
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(LAST_INSERT_ID(),12,'bandage');
#@ _INSERT_A4_

SELECT * FROM invoice;
SELECT * FROM inv_item;

DROP TABLE IF EXISTS inv_item;
#@ _CREATE_TABLE_INV_ITEM_B_
CREATE TABLE inv_item
(
  inv_id  INT UNSIGNED NOT NULL,  # invoice ID (from invoice table)
  item_id INT UNSIGNED NOT NULL AUTO_INCREMENT, # item ID
  PRIMARY KEY (item_id),
  qty     INT,                                  # quantity
  description VARCHAR(40)                       # description
);
#@ _CREATE_TABLE_INV_ITEM_B_

DELETE FROM invoice;

# The wrong way to do it (queries are same as before, but table
# structure is different so it doesn't work correctly):

INSERT INTO invoice (inv_id,date)
  VALUES(NULL,CURDATE());
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(LAST_INSERT_ID(),1,'hammer');
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(LAST_INSERT_ID(),3,'nails, box');
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(LAST_INSERT_ID(),12,'bandage');

SELECT * FROM invoice;
SELECT * FROM inv_item;

DELETE FROM invoice;
DELETE FROM inv_item;

# One right way to do it:

#@ _INSERT_B1_
INSERT INTO invoice (inv_id,date)
  VALUES(NULL,CURDATE());
#@ _INSERT_B1_
#@ _INSERT_B2_
INSERT INTO inv_item (inv_id,qty,description) VALUES
  (LAST_INSERT_ID(),1,'hammer'),
  (LAST_INSERT_ID(),3,'nails, box'),
  (LAST_INSERT_ID(),12,'bandage');
#@ _INSERT_B2_

SELECT * FROM invoice;
SELECT * FROM inv_item;

DELETE FROM invoice;
DELETE FROM inv_item;

# Aother right way to do it:

#@ _INSERT_C1_
INSERT INTO invoice (inv_id,date)
  VALUES(NULL,CURDATE());
#@ _INSERT_C1_
#@ _INSERT_C2_
SET @inv_id = LAST_INSERT_ID();
#@ _INSERT_C2_
#@ _INSERT_C3_
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(@inv_id,1,'hammer');
#@ _INSERT_C3_
#@ _INSERT_C4_
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(@inv_id,3,'nails, box');
#@ _INSERT_C4_
#@ _INSERT_C5_
INSERT INTO inv_item (inv_id,qty,description)
  VALUES(@inv_id,12,'bandage');
#@ _INSERT_C5_

SELECT * FROM invoice;
SELECT * FROM inv_item;
