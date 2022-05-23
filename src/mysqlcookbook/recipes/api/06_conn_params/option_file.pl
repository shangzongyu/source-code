#!/usr/bin/perl
# option_file.pl: demonstrate DSN options for reading MySQL option files

use strict;
use warnings;
use DBI;

{ # begin scope

#@ _FRAG1_
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
# basic DSN
my $dsn = "DBI:mysql:database=cookbook";
# look in user-specific option file owned by the current user
$dsn .= ";mysql_read_default_file=$ENV{HOME}/.my.cnf";
my $dbh = DBI->connect ($dsn, undef, undef, $conn_attrs);
#@ _FRAG1_
print "Connected\n";
$dbh->disconnect ();
print "Disconnected\n";

} # end scope

{ # begin scope

#@ _FRAG2_
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
# basic DSN
my $dsn = "DBI:mysql:database=cookbook";
# look in standard option files; use [cookbook] and [client] groups
$dsn .= ";mysql_read_default_group=cookbook";
my $dbh = DBI->connect ($dsn, undef, undef, $conn_attrs);
#@ _FRAG2_
print "Connected\n";
$dbh->disconnect ();
print "Disconnected\n";

} # end scope
