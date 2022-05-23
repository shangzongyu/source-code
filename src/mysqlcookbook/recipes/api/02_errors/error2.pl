#!/usr/bin/perl
# error2.pl: demonstrate MySQL error handling

# Use default settings: PrintError enabled, RaiseError disabled.
# Check for error and exit if one occurred, but let DBI print error
# message itself.

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

#@ _PRINTERROR_ONLY_2_
my $conn_attrs = {AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "baduser", "badpass", $conn_attrs)
            or exit;
#@ _PRINTERROR_ONLY_2_
$dbh->disconnect ();
