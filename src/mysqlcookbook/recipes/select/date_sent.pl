#!/usr/bin/perl
# date_sent.pl: fetch rows into hash, refer to columns by name

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();
my $sth;
my $stmt;

#@ _FRAG_
$sth = $dbh->prepare ("SELECT srcuser,
                       DATE_FORMAT(t,'%M %e, %Y') AS date_sent
                       FROM mail");
$sth->execute ();
while (my $ref = $sth->fetchrow_hashref ())
{
  printf "user: %s, date sent: %s\n", $ref->{srcuser}, $ref->{date_sent};
}
#@ _FRAG_

$dbh->disconnect ();
