# mmddyyyy_to_iso.sql

# Show how to load date values that don't follow the ISO (YYYY-MM-DD)
# format and convert them to ISO format.  You can use this approach
# to handle non-ISO input dates that you want to store in a DATE column.

# - Create a table with CHAR and DATE columns
# - Load some mm/dd/yyyy data into the CHAR column
# - Reformat the CHAR column into the DATE column
# - Drop the CHAR column

DROP TABLE IF exists datecvt;
CREATE TABLE datecvt
(
  c_date  CHAR(10),   # date as CHAR column
  d_date  DATE      # date as DATE column
);

LOAD DATA LOCAL INFILE 'mmddyyyy_to_iso.txt' INTO TABLE datecvt (c_date);

SELECT c_date AS 'original CHAR string' FROM datecvt;

UPDATE datecvt SET d_date =
    CONCAT(
      SUBSTRING_INDEX(c_date,'/',-1), # year part
      '-',
      SUBSTRING_INDEX(c_date,'/',1),  # month part
      '-',
      SUBSTRING_INDEX(SUBSTRING_INDEX(c_date,'/',2),'/',-1) #day part
    );

ALTER TABLE datecvt DROP c_date;

SELECT d_date AS 'CHAR reformatted to DATE' FROM datecvt;
