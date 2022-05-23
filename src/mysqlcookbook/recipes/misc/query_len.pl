#!/usr/bin/perl
# query_len.pl: find out how long a query a client can send to the server

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

my ($junk, $max_allowed_packet) =
  $dbh->selectrow_array("SHOW VARIABLES LIKE 'max_allowed_packet'");
print "max_allowed_packet $max_allowed_packet\n";

$dbh->{RaiseError} = 0;   # don't want automatic script termination

my $val = "";   # initial value
my $last_ok_len = 0;

# Issue the statement.  If it works, make it longer and try again.
# Continue until failure

while (1)
{
  my $n = $dbh->selectrow_array ("SELECT ?", undef, $val);
  if (!defined ($n))
  {
    print "Query fails at approx. length: " . length ($val) . "\n";
    print "Error is: $DBI::errstr\n";
    print "Last okay length: $last_ok_len\n";
    last;
  }
  $last_ok_len = length ($val);
  $val .= "x" x 10000;
}

$dbh->disconnect ();
