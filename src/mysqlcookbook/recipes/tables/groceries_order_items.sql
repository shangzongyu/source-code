# groceries_order_items.sql

DROP TABLE IF EXISTS groceries_order_items;
#@ _CREATE_TABLE_
CREATE TABLE groceries_order_items
(
  order_id INT NOT NULL,
  groceries_id INT NOT NULL,
  quantity INT DEFAULT 0,
  PRIMARY KEY (order_id,groceries_id)
);
#@ _CREATE_TABLE_

