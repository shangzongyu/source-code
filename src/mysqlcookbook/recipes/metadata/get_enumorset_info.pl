#!/usr/bin/perl
# get_enumorset_info.pl: wrapper to demonstrate get_enumorset_info()
# utility routine.

# Usage: get_enumorset_info.pl db_name tbl_name col_name

use strict;
use warnings;
use Cookbook;
use Cookbook_Utils;

@ARGV == 3 or die "Usage: $0 db_name tbl_name col_name\n";

my $dbh = Cookbook::connect ();

my $info = get_enumorset_info ($dbh, $ARGV[0], $ARGV[1], $ARGV[2]);
print "Information for $ARGV[0].$ARGV[1].$ARGV[2]:\n";
if (!$info)
{
  print "No information available (not an ENUM or SET column?)\n";
}
else
{
  print "Name: $info->{name}\n";
  print "Type: $info->{type}\n";
  print "Legal values: " . join (",", @{$info->{values}}), "\n";
  print "Nullable: ", ($info->{nullable} ? "yes" : "no") , "\n";
  printf "Default value: %s\n",
         (defined ($info->{default}) ? $info->{default} : "NULL");
}

$dbh->disconnect ();
