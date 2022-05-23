#!/usr/bin/perl

use strict;
use warnings;
use Cookbook;

@ARGV >= 3 or die "Usage: $0 db_name tbl_name col_name ...\n";

my $dbh = Cookbook::connect ();

delete_dups ($dbh, @ARGV);

$dbh->disconnect ();

# ----------------------------------------------------------------------

# Given database and  table names and a set of one or more column
# names, return a query that can be executed to count duplicate values
# for those columns.

# NOTE: Assumes that identifiers are quoted properly.

sub make_dup_count_query
{
my ($db_name, $tbl_name, @col_name) = @_;

  return "SELECT COUNT(*)," . join (",", @col_name)
         . "\nFROM $db_name.$tbl_name"
         . "\nGROUP BY " . join (",", @col_name)
         . "\nHAVING COUNT(*) > 1";
}

# Given a database handle, database and table names, and a set of one
# or more column names, delete all but one instance of each set of
# records that are duplicates on the given columns.

#@ _DELETE_DUPS_
sub delete_dups
{
my ($dbh, $db_name, $tbl_name, @col_name) = @_;

  $db_name = $dbh->quote_identifier ($db_name);
  $tbl_name = $dbh->quote_identifier ($tbl_name);
  @col_name = map { $dbh->quote_identifier ($_) } @col_name;

  # Construct and run a query that finds duplicated values

  my $dup_info = $dbh->selectall_arrayref (
                    make_dup_count_query ($db_name, $tbl_name, @col_name)
                  );
  return unless defined ($dup_info);

  # For each duplicated set of values, delete all but one instance
  # of the rows containing those values

  foreach my $row_ref (@{$dup_info})
  {
    my ($count, @col_val) = @{$row_ref};
    # Construct condition string to match values, being
    # careful to match NULL with IS NULL
    my $str;
    for (my $i = 0; $i < @col_name; $i++)
    {
      $str .= " AND " if $str;
      $str .= defined ($col_val[$i])
            ? "$col_name[$i] = " . $dbh->quote ($col_val[$i])
            : "$col_name[$i] IS NULL";
    }
    $str = "DELETE FROM $db_name.$tbl_name WHERE $str LIMIT " . ($count - 1);
    $dbh->do ($str);
  }
}
#@ _DELETE_DUPS_
