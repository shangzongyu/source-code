#!/usr/bin/perl
use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

#@ QUOTE
print $dbh->quote (3), "\n";
print $dbh->quote (qq{ab'cd"ef\\gh}), "\n";
print $dbh->quote (undef), "\n";
#@ QUOTE
$dbh->disconnect ();
