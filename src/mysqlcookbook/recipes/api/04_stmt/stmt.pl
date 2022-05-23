#!/usr/bin/perl
# stmt.pl: demonstrate statement processing in Perl
# (without placeholders)

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

{ # begin scope

# NOTE: THIS EXAMPLE MUST INCLUDE finish() (it's discussed in the text)

print "Fetch rows with fetchrow_array()\n";
#@ _FETCHLOOP_1_
my $sth = $dbh->prepare ("SELECT id, name, cats FROM profile");
$sth->execute ();
my $count = 0;
while (my @val = $sth->fetchrow_array ())
{
  print "id: $val[0], name: $val[1], cats: $val[2]\n";
  ++$count;
}
$sth->finish ();
print "Number of rows returned: $count\n";
#@ _FETCHLOOP_1_

} # end scope

{ # begin scope

print "Fetch rows with fetchrow_arrayref()\n";
my $sth = $dbh->prepare ("SELECT id, name, cats FROM profile");
$sth->execute ();
#@ _FETCHLOOP_2_
while (my $ref = $sth->fetchrow_arrayref ())
{
  print "id: $ref->[0], name: $ref->[1], cats: $ref->[2]\n";
}
#@ _FETCHLOOP_2_

} # end scope

{ # begin scope

print "Fetch rows with fetchrow_hashref()\n";
my $sth = $dbh->prepare ("SELECT id, name, cats FROM profile");
$sth->execute ();
#@ _FETCHLOOP_3_
while (my $ref = $sth->fetchrow_hashref ())
{
  print "id: $ref->{id}, name: $ref->{name}, cats: $ref->{cats}\n";
}
#@ _FETCHLOOP_3_

} # end scope

{ # begin scope

print "Fetch rows with selectrow_array()\n";
#@ _SELECTROW_ARRAY_1_
my @val = $dbh->selectrow_array ("SELECT name, birth, foods FROM profile
                                  WHERE id = 3");
#@ _SELECTROW_ARRAY_1_
#@ _SELECTROW_ARRAY_2_
my $buddy_count = $dbh->selectrow_array ("SELECT COUNT(*) FROM profile");
#@ _SELECTROW_ARRAY_2_
print "buddy row: @val\n";
print "buddy count: $buddy_count\n";

} # end scope

{ # begin scope

print "Update rows\n";
#@ _DO_1_
my $count = $dbh->do ("UPDATE profile SET cats = cats+1
                       WHERE name = 'Sybil'");
if ($count)   # print row count if no error occurred
{
  $count += 0;
  print "Number of rows updated: $count\n";
}
#@ _DO_1_

} # end scope

{ # begin scope

my $count = $dbh->do ("UPDATE profile SET cats = cats+1
                       WHERE name = 'Sybil'");
#@ _DO_2_
if ($count)   # print row count if no error occurred
{
  printf "Number of rows updated: %d\n", $count;
}
#@ _DO_2_

} # end scope

{ # begin scope

#@ _DO_3_
my $count = $dbh->do ("UPDATE profile SET cats = cats+1
                       WHERE name = 'Sybil'");
printf "Number of rows updated: %d\n", $count;
#@ _DO_3_

} # end scope

$dbh->disconnect ();
