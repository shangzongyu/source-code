#!/usr/bin/perl
# database_exists.pl

# Test for database existence.  Name one or more db's on the command line.

use strict;
use warnings;
use Cookbook;

# Test whether a database exists.

# Caveat: database_exists() returns false if the database exists
# but you don't have privileges for accessing it.

#@ _DATABASE_EXISTS_
sub database_exists
{
my ($dbh, $db_name) = @_;

  return $dbh->selectrow_array ("SELECT SCHEMA_NAME
                                 FROM INFORMATION_SCHEMA.SCHEMATA
                                 WHERE SCHEMA_NAME = ?",
                                undef, $db_name);
}
#@ _DATABASE_EXISTS_

@ARGV == 0 and die "You should name a database on the command line\n";

my $dbh = Cookbook::connect ();

foreach my $db_name (@ARGV)
{
  printf "$db_name: %s\n",
    database_exists ($dbh, $db_name) ? "exists" : "does not exist";
}

$dbh->disconnect ();
