# hitrate.sql: Show InnoDB and MyISAM key cache hit rate statistics
USE performance_schema;
SET @reads = (SELECT VARIABLE_VALUE FROM global_status
              WHERE VARIABLE_NAME = 'INNODB_BUFFER_POOL_READS');
SET @requests = (SELECT VARIABLE_VALUE FROM global_status
                 WHERE VARIABLE_NAME = 'INNODB_BUFFER_POOL_READ_REQUESTS');
SET @hit_rate = TRUNCATE(IFNULL(1 - (@reads/@requests), 0), 4);
SELECT 'InnoDB key cache hit rate' AS Message,
       @reads, @requests, @hit_rate;
SET @reads = (SELECT VARIABLE_VALUE FROM global_status
              WHERE VARIABLE_NAME = 'KEY_READS');
SET @requests = (SELECT VARIABLE_VALUE FROM global_status
                 WHERE VARIABLE_NAME = 'KEY_READ_REQUESTS');
SET @hit_rate = TRUNCATE(IFNULL(1 - (@reads/@requests), 0), 4);
SELECT 'MyISAM key cache hit rate' AS Message,
       @reads, @requests, @hit_rate;
