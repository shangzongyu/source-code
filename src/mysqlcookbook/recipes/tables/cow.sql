# cow.sql

# Tables for online contruct-a-cow ordering scenario

DROP TABLE IF EXISTS cow_order;
#@ _CREATE_COW_ORDER_TABLE_
CREATE TABLE cow_order
(
  id          INT UNSIGNED NOT NULL AUTO_INCREMENT,
  # cow color, figurine size, and accessory items
  color       VARCHAR(20),
  size        ENUM('small','medium','large') DEFAULT 'medium',
  accessories SET('cow bell','horns','nose ring','tail ribbon')
                  DEFAULT 'cow bell,horns',
  # customer name, street, city, and state (abbreviation)
  cust_name   VARCHAR(40),
  cust_street VARCHAR(40),
  cust_city   VARCHAR(40),
  cust_state  CHAR(2),
  PRIMARY KEY (id)
);
#@ _CREATE_COW_ORDER_TABLE_

# Add some orders to the table

INSERT INTO cow_order (color, size, accessories,
                       cust_name, cust_street, cust_city, cust_state)
VALUES
  ('Black & White','large','cow bell,nose ring',
    'Farmer Brown','123 Elm St.','Bald Knob','AR')
;

SELECT * FROM cow_order\G

DROP TABLE IF EXISTS cow_color;
#@ _CREATE_COW_COLOR_TABLE_
CREATE TABLE cow_color (
  color CHAR(20),
  PRIMARY KEY(color)
);
#@ _CREATE_COW_COLOR_TABLE_

INSERT INTO cow_color (color)
VALUES
  ('Black'),
  ('Brown'),
  ('Cream'),
  ('Black & White'),
  ('Red & White'),
  ('Red'),
  ('See-Through')
;

SELECT * FROM cow_color;
