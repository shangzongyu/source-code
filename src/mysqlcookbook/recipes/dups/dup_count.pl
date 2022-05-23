#!/usr/bin/perl
# dup_count.pl: generate query to identify and count duplicate values

use strict;
use warnings;

@ARGV >= 3 or die "Usage: $0 db_name tbl_name col_name ...\n";

my $str = make_dup_count_query (@ARGV);
print "$str\n";

# ----------------------------------------------------------------------

# Given database and table name and a list of one or more column
# names, return a query that can be executed to count duplicate values
# for those columns.

# NOTE: Assumes that identifiers are quoted properly.

#@ _MAKE_DUP_COUNT_QUERY_
sub make_dup_count_query
{
my ($db_name, $tbl_name, @col_name) = @_;

  return "SELECT COUNT(*)," . join (",", @col_name)
         . "\nFROM $db_name.$tbl_name"
         . "\nGROUP BY " . join (",", @col_name)
         . "\nHAVING COUNT(*) > 1";
}
#@ _MAKE_DUP_COUNT_QUERY_
