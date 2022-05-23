#!/usr/bin/perl
# error5.pl: demonstrate MySQL error handling

# PrintError and RaiseError both enabled. With these settings, DBI may call
# both warn() and die(), resulting in double error messages. (So normally
# you would avoid these settings.)

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

# connect and let DBI terminate if an error occurs
#@ _RAISEERROR_PRINTERROR_BOTH_
my $conn_attrs = {RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "baduser", "badpass", $conn_attrs);
#@ _RAISEERROR_PRINTERROR_BOTH_
$dbh->disconnect ();
