#!/usr/bin/perl
# get_table_names.pl

use strict;
use warnings;
use Cookbook;

# SHOULD IT RETURN AN EMPTY LIST?
# Or should it return a reference/undef?
# The latter course is less ambiguous about whether an error occurs

# Return list of tables in given database, or in default database if
# no database is named.

sub get_table_names
{
my ($dbh, $db_name) = @_;
my ($ref);

  $ref = $dbh->selectcol_arrayref (
                "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES
                WHERE TABLE_SCHEMA = ? ORDER BY TABLE_NAME",
                undef, $db_name);
  return $ref ? @{$ref} : undef;
}

@ARGV < 1 and die "Usage: $0 db_name\n";
my $db_name = shift @ARGV;

my @names;

my $dbh = Cookbook::connect ();
@names = get_table_names ($dbh, "test");
print "Tables in 'test' database:\n";
print join ("\n", @names), "\n";
@names = get_table_names ($dbh, $db_name);
print "Tables in '$db_name' database:\n";
print join ("\n", @names), "\n";
$dbh->disconnect ();
