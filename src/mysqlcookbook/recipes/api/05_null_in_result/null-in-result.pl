#!/usr/bin/perl
# null-in-result.pl: print undef values as "NULL"

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

{ # begin scope

#@ _FETCHLOOP_1_
my $sth = $dbh->prepare ("SELECT name, birth, foods FROM profile");
$sth->execute ();
while (my $ref = $sth->fetchrow_hashref ())
{
  printf "name: %s, birth: %s, foods: %s\n",
         defined ($ref->{name}) ? $ref->{name} : "NULL",
         defined ($ref->{birth}) ? $ref->{birth} : "NULL",
         defined ($ref->{foods}) ? $ref->{foods} : "NULL";
}
#@ _FETCHLOOP_1_

} # end scope

{ # begin scope

#@ _FETCHLOOP_2_
my $sth = $dbh->prepare ("SELECT name, birth, foods FROM profile");
$sth->execute ();
while (my $ref = $sth->fetchrow_hashref ())
{
  foreach my $key (keys (%{$ref}))
  {
    $ref->{$key} = "NULL" unless defined ($ref->{$key});
  }
  printf "name: %s, birth: %s, foods: %s\n",
         $ref->{name}, $ref->{birth}, $ref->{foods};
}
#@ _FETCHLOOP_2_

} # end scope

{ # begin scope

#@ _FETCHLOOP_3_
my $sth = $dbh->prepare ("SELECT name, birth, foods FROM profile");
$sth->execute ();
while (my $ref = $sth->fetchrow_hashref ())
{
  map { $ref->{$_} = "NULL" unless defined ($ref->{$_}); } keys (%{$ref});
  printf "name: %s, birth: %s, foods: %s\n",
         $ref->{name}, $ref->{birth}, $ref->{foods};
}
#@ _FETCHLOOP_3_

} # end scope

{ # begin scope

#@ _FETCHLOOP_4_
my $sth = $dbh->prepare ("SELECT name, birth, foods FROM profile");
$sth->execute ();
while (my @val = $sth->fetchrow_array ())
{
  @val = map { defined ($_) ? $_ : "NULL" } @val;
  printf "name: %s, birth: %s, foods: %s\n",
         $val[0], $val[1], $val[2];
}
#@ _FETCHLOOP_4_

} # end scope

$dbh->disconnect ();
