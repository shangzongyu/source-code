# book_authors.sql

DROP TABLE IF EXISTS book_authors;
#@ _CREATE_TABLE_
CREATE TABLE `book_authors` (
  id     INT NOT NULL AUTO_INCREMENT,
  author JSON NOT NULL,
  PRIMARY KEY (id)
);
#@ _CREATE_TABLE_

INSERT INTO `book_authors` VALUES 
  (1,'{"id": 1, "name": "Paul", 
      "books": ["Software Portability with imake: Practical Software Engineering",
                "Mysql: The Definitive Guide to Using, Programming, and Administering Mysql 4 (Developer\'s Library)", 
                "MySQL Certification Study Guide", 
                "MySQL (OTHER NEW RIDERS)", 
                "MySQL Cookbook", 
                "MySQL 5.0 Certification Study Guide", 
                "Using csh & tcsh: Type Less, Accomplish More (Nutshell Handbooks)", 
                "MySQL (Developer\'s Library)"], 
      "lastname": "DuBois"}'),
  (2,'{"id": 2, "name": "Alkin", 
       "books": ["MySQL Cookbook"], 
       "lastname": "Tezuysal"}'),
  (3,'{"id": 3, "name": "Sveta", 
       "books": ["MySQL Troubleshooting", "MySQL Cookbook"], 
       "lastname": "Smirnova"}');

SELECT * FROM book_authors;
