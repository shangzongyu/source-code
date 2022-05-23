#!/usr/bin/perl
# table_exists.pl

# Test for table existence.  Name a database and one or more
# tables on the command line.

use strict;
use warnings;
use Cookbook;

# Test whether a table exists.

# Caveat: table_exists() returns false if the table exists but you
# don't have privileges for accessing it.

#@ _TABLE_EXISTS_
sub table_exists
{
my ($dbh, $db_name, $tbl_name) = @_;

  return $dbh->selectrow_array (
                "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES
                WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?",
                undef, $db_name, $tbl_name);
}
#@ _TABLE_EXISTS_

@ARGV < 2 and die "Usage: $0 db_name tbl_name ...\n";
my $db_name = shift @ARGV;

my $dbh = Cookbook::connect ();

foreach my $tbl_name (@ARGV)
{
  printf "$tbl_name: %s\n",
         table_exists ($dbh, $db_name, $tbl_name)
           ? "exists"
           : "does not exist";
}

$dbh->disconnect ();
