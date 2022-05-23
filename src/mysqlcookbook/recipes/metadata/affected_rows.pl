#!/usr/bin/perl
# affected_rows.pl

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

my $stmt = "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'";

{ # scope begin

# execute statement using do()
#@ _FRAG_1_
my $count = $dbh->do ($stmt);
# report 0 rows if an error occurred
printf "Number of rows affected: %d\n", (defined ($count) ? $count : 0);
#@ _FRAG_1_

} # scope end

{ # scope begin

# execute statement using prepare() plus execute()
#@ _FRAG_2_
my $sth = $dbh->prepare ($stmt);
my $count = $sth->execute ();
printf "Number of rows affected: %d\n", (defined ($count) ? $count : 0);
#@ _FRAG_2_

} # scope end

$dbh->disconnect ();

{ # scope begin

# illustrate use of mysql_client_found_rows
#@ _MYSQL_CLIENT_FOUND_ROWS_
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dsn = "DBI:mysql:cookbook:localhost;mysql_client_found_rows=1";
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass", $conn_attrs);
#@ _MYSQL_CLIENT_FOUND_ROWS_

# this statement changes no rows, but the row count should still
# be nonzero due to the use of mysql_client_found_rows
my $stmt = "UPDATE limbs SET arms = 0 WHERE arms = 0";
my $count = $dbh->do ($stmt);
# report 0 rows if an error occurred
printf "Number of rows affected: %d\n", (defined ($count) ? $count : 0);

} # scope end
