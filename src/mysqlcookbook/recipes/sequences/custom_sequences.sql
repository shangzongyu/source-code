# custom_sequences.sql

CREATE TABLE `sequences` (
  `sequence_name` varchar(64) NOT NULL,
  `maximum_value` bigint NOT NULL DEFAULT '9223372036854775807',
  `minimum_value` bigint NOT NULL DEFAULT '-9223372036854775808',
  `increment` bigint NOT NULL DEFAULT '1',
  `start_value` bigint NOT NULL DEFAULT '-9223372036854775808',
  `current_base_value` bigint NOT NULL DEFAULT '-9223372036854775808',
  `cycle_option` enum('yes','no') NOT NULL DEFAULT 'no',
  PRIMARY KEY (`sequence_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

delimiter $$

CREATE PROCEDURE create_sequence( 
    sequence_name VARCHAR(64), start_value BIGINT, increment BIGINT, 
    cycle_option ENUM('yes','no'), maximum_value BIGINT, minimum_value BIGINT) 
BEGIN 
    INSERT INTO sequences 
        (sequence_name, maximum_value, minimum_value, increment, start_value, current_base_value, cycle_option) 
        VALUES(
            sequence_name, 
            COALESCE(maximum_value, 9223372036854775807), 
            COALESCE(minimum_value, -9223372036854775808), 
            COALESCE(increment, 1), 
            COALESCE(start_value, -9223372036854775808), 
            COALESCE(start_value, -9223372036854775808), 
            COALESCE(cycle_option, 'no'));
END
$$

CREATE FUNCTION sequence_next_value(name varchar(64)) RETURNS BIGINT 
BEGIN 
    DECLARE retval BIGINT; 
    SELECT current_base_value INTO retval FROM sequences WHERE sequence_name=name FOR UPDATE; 
    UPDATE sequences SET current_base_value=
        IF((current_base_value+increment <= maximum_value AND current_base_value+increment >= minimum_value), 
            current_base_value+increment, 
            IF('yes' = cycle_option, start_value, NULL)
        ) WHERE sequence_name=name;
    RETURN retval; 
END
$$

CREATE PROCEDURE delete_sequence(name VARCHAR(64)) 
DELETE FROM sequences WHERE sequence_name=name
$$

delimiter ;
