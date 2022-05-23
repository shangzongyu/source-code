#!/usr/bin/perl
# error4.pl: demonstrate MySQL error handling

# PrintError disabled, RaiseError enabled.
# Script connects and lets DBI terminate if an error occurs, but avoids having
# both PrintError and RaiseError generate the same message.

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

#@ _RAISEERROR_ONLY_
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "baduser", "badpass", $conn_attrs);
#@ _RAISEERROR_ONLY_
$dbh->disconnect ();
