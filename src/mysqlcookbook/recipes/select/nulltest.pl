#!/usr/bin/perl
# nulltest.pl: show correct/incorrect way to write comparisons for
# values that might represent NULL.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();
my $sth;
my $score;
my $operator;

print "This program displays expt table rows with NULL scores\n";

# This example uses = for the comparison operator, which fails if
# $score is undef.

$score = undef;

#@ _INCORRECT_
$sth = $dbh->prepare ("SELECT * FROM expt WHERE score = ?");
$sth->execute ($score);
#@ _INCORRECT_
print "Method 1 (incorrect)\n";
while (my $ref = $sth->fetchrow_hashref ())
{
  printf "subject: %s; test: %s\n", $ref->{subject}, $ref->{test};
}

# This example chooses the comparison operator appropriately depending
# on whether or not $score is undef.

#@ _CORRECT_
$operator = defined ($score) ? "=" : "IS";
$sth = $dbh->prepare ("SELECT * FROM expt WHERE score $operator ?");
$sth->execute ($score);
#@ _CORRECT_
print "Method 2 (correct)\n";
while (my $ref = $sth->fetchrow_hashref ())
{
  printf "subject: %s; test: %s\n", $ref->{subject}, $ref->{test};
}

# This is how you'd construct the operator for a not-equal test

#@ _NOT_EQUAL_
$operator = defined ($score) ? "<>" : "IS NOT";
#@ _NOT_EQUAL_

$dbh->disconnect ();
