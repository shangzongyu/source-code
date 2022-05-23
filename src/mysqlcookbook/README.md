# mysqlcookbook

This is a companion GitHub repository for the book "MySQL Cookbook 4th Edition". 

All companion code is located in the `recipes` direcotory also called as "recipes distribution".

To initialize database create it first with the command

```
CREATE DATABASE cookbook;
```

Then import data from `cookbook.sql`:

```
mysql cookbook < cookbook.sql
```

You can also import individual tables using scripts, located in the `tables` directory.

To import individual collections use scripts in the `collections` directory.

We used few public datasets which are located in the `datasets` directory together with their licences.

"MySQL Cookbook 3th Edition" was written by Paul DuBois and many scripts in this repository are based on his work. Original scripts for the "MySQL Cookbook 3th Edition" are available at [MySQL Cookbook, Third Edition - Downloads](http://www.kitebird.com/mysql-cookbook/downloads-3ed.php)
