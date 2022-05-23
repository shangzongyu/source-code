# ingredient.sql

DROP TABLE IF EXISTS ingredient;
#@ _CREATE_TABLE_
CREATE TABLE ingredient
(
  id    INT UNSIGNED NOT NULL AUTO_INCREMENT,
  item  CHAR(40),
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_

INSERT INTO ingredient (item)
  VALUES
    ('3 cups flour'),
    ('1/2 cup raw ("unrefined") sugar'),
    ('3 eggs'),
    ('pinch (< 1/16 teaspoon) salt')
;

SELECT * FROM ingredient;
