#!/usr/bin/perl
# get_column_info.pl: wrapper to demonstrate get_column_info()
# utility routine

# Assumes that you've created the "image" table!

use strict;
use warnings;
use Cookbook;
use Cookbook_Utils;

my $db_name = "cookbook";
my $tbl_name = "image";

my @names;

my $dbh = Cookbook::connect ();

print "Using get_column_info()\n";
print "Column information for $db_name.$tbl_name table:\n";
my $info_ref = get_column_info ($dbh, $db_name, $tbl_name);
foreach my $col_name (keys %{$info_ref})
{
  my $col_ref = $info_ref->{$col_name};
  print "  Column: $col_name:\n";
  foreach my $col_info_key (keys %{$col_ref})
  {
    my $col_info_val = $col_ref->{$col_info_key};
    $col_info_val = "NULL" unless defined ($col_info_val);
    print "    $col_info_key: $col_info_val:\n";
  }
}

$dbh->disconnect ();
