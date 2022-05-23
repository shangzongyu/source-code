#!/usr/bin/perl
# distinct_col.pl: resolve ambiguous join output column names using aliases

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

my ($stmt, $sth, $ref, $count1, $count2);

# First demonstrate the problem using a query that returns nonunique
# column names.

#@ _FRAG_1_
$stmt = qq{
  SELECT artist.name, painting.title, states.name, painting.price
  FROM artist INNER JOIN painting INNER JOIN states
  ON artist.a_id = painting.a_id AND painting.state = states.abbrev
};
$sth = $dbh->prepare ($stmt);
$sth->execute ();
# Determine the number of columns in result set rows two ways:
# - Check the NUM_OF_FIELDS statement handle attribute
# - Fetch a row into a hash and see how many keys the hash contains
$count1 = $sth->{NUM_OF_FIELDS};
$ref = $sth->fetchrow_hashref ();
$count2 = keys (%{$ref});
print "The statement is: $stmt\n";
print "According to NUM_OF_FIELDS, the result set has $count1 columns\n";
print "The column names are: " . join (",", sort (@{$sth->{NAME}})) . "\n";
print "According to the row hash size, the result set has $count2 columns\n";
print "The column names are: " . join (",", sort (keys (%{$ref}))) . "\n";
#@ _FRAG_1_
print "The counts DO NOT match!\n" if $count1 != $count2;
$sth->finish ();

print "\n";

# Assign column aliases to provide distinct names

#@ _FRAG_2_
$stmt = qq{
  SELECT artist.name AS painter, painting.title,
    states.name AS state, painting.price
  FROM artist INNER JOIN painting INNER JOIN states
  ON artist.a_id = painting.a_id AND painting.state = states.abbrev
};
$sth = $dbh->prepare ($stmt);
$sth->execute ();
# Determine the number of columns in result set rows two ways:
# - Check the NUM_OF_FIELDS statement handle attribute
# - Fetch a row into a hash and see how many keys the hash contains
$count1 = $sth->{NUM_OF_FIELDS};
$ref = $sth->fetchrow_hashref ();
$count2 = keys (%{$ref});
print "The statement is: $stmt\n";
print "According to NUM_OF_FIELDS, the result set has $count1 columns\n";
print "The column names are: " . join (",", sort (@{$sth->{NAME}})) . "\n";
print "According to the row hash size, the result set has $count2 columns\n";
print "The column names are: " . join (",", sort (keys (%{$ref}))) . "\n";
#@ _FRAG_2_
print "The counts DO NOT match!\n" if $count1 != $count2;
$sth->finish ();

$sth = $dbh->prepare ($stmt);
$sth->execute ();
print "\nFetching using fetchrow_hashref\n";
#@ _FETCH_HASH_
while (my $ref = $sth->fetchrow_hashref ())
{
  print "painter: $ref->{painter}, title: $ref->{title}, "
        . "state: $ref->{state}, price: $ref->{price}\n";
}
#@ _FETCH_HASH_

$sth = $dbh->prepare ($stmt);
$sth->execute ();
print "\nFetching using fetchrow_array\n";
#@ _FETCH_ARRAY_
while (my @val = $sth->fetchrow_array ())
{
  print "painter: $val[0], title: $val[1], "
        . "state: $val[2], price: $val[3]\n";
}
#@ _FETCH_ARRAY_

$dbh->disconnect ();
