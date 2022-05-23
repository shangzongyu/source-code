#!/usr/bin/perl
# harness2.pl: test harness for Cookbook.pm library

# Does not catch exceptions, so this script simply dies if
# a connect error occurs.

use strict;
use warnings;
use Cookbook;

#@ _FRAG_
my $dbh = Cookbook::connect ();
print "Connected\n";
$dbh->disconnect ();
print "Disconnected\n";
#@ _FRAG_
