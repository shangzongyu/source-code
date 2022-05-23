#!/usr/bin/perl
# error1.pl: demonstrate MySQL error handling

# Use default settings: PrintError enabled, RaiseError disabled.
# Check for error, but let DBI print error message itself.

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

#@ _PRINTERROR_ONLY_1_
my $conn_attrs = {AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "baduser", "badpass", $conn_attrs);
#@ _PRINTERROR_ONLY_1_
$dbh->disconnect () if $dbh;
