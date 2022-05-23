#!/usr/bin/perl
# get_database_names.pl

use strict;
use warnings;
use Cookbook;

# SHOULD IT RETURN AN EMPTY LIST?
# Or should it return a reference/undef?
# The latter course is less ambiguous about whether an error occurs

sub get_database_names
{
my $dbh = shift;
my $ref;

  $ref = $dbh->selectcol_arrayref ("SELECT SCHEMA_NAME
                                    FROM INFORMATION_SCHEMA.SCHEMATA
                                    ORDER BY SCHEMA_NAME");
  return $ref ? @{$ref} : undef;
}

my @names;
my $dbh = Cookbook::connect ();
@names = get_database_names ($dbh);
print "Databases:\n";
print join ("\n", @names), "\n";
$dbh->disconnect ();
