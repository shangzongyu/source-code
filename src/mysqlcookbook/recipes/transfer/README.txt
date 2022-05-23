This directory contains scripts related to data transfer -- importing
information from MySQL or exporting information from MySQL.

To install any of these utilities, see comments in the README.txt file in
the main recipes distribution directory.

monddyyyy_to_iso.pl: converts dates like Dec. 18, 1787 to ISO format.
Try it with the statehood.txt file.

The test_date.php script demonstrates how PHP's .Cw strtotime() works.
This function can be useful for converting dates, because it tries to
interpret strings written in a variety of formats in a sensible manner.

somedata.csv: the CSV file referenced in the initial scenario described
in the transfer chapter, and in its Epilog.

XML utilities:
- mysql_to_xml.pl: export query result as XML
- xml_to_mysql.pl: import XML into MySQL
- xmlformatter.rb: Demonstrates Ruby DBI::Utils::XMLFormatter.table method
