#!/usr/bin/perl
# error3.pl: demonstrate MySQL error handling

# PrintError and RaiseError both disabled (suppress DBI message-printing).
# Script connects and checks for error, printing message itself if one occurs.

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

#@ _RAISEERROR_PRINTERROR_NEITHER_
my $conn_attrs = {PrintError => 0, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "baduser", "badpass", $conn_attrs)
            or die "Connection error: "
                   . "$DBI::errstr ($DBI::err/$DBI::state)\n";
#@ _RAISEERROR_PRINTERROR_NEITHER_
$dbh->disconnect ();
