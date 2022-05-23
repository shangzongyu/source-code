# drop-create-table.sql: Create unique name and create table with that
# name (dropping it if it exists first).

#@ _DROP_CREATE_
SET @tbl_name = CONCAT('tmp_tbl_', CONNECTION_ID());
SET @stmt = CONCAT('DROP TABLE IF EXISTS ', @tbl_name);
PREPARE stmt FROM @stmt;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
SET @stmt = CONCAT('CREATE TABLE ', @tbl_name, ' (i INT)');
PREPARE stmt FROM @stmt;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
#@ _DROP_CREATE_

# drop the table again to clean it up
SET @stmt = CONCAT('DROP TABLE IF EXISTS ', @tbl_name);
PREPARE stmt FROM @stmt;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
