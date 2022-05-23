SET @s = BINARY 'aAbBcC';
SELECT @s, LOWER(@s), UPPER(@s);

# convert using explicit character set and collation

SET @s = CONVERT(@s USING latin1) COLLATE latin1_spanish_ci;
SELECT CHARSET(@s), COLLATION(@s);
SELECT @s, LOWER(@s), UPPER(@s);

# convert using character set only (collation becomes the default
# for the character set)

SET @s = CONVERT(@s USING latin1);
SELECT CHARSET(@s), COLLATION(@s);
SELECT @s, LOWER(@s), UPPER(@s);
