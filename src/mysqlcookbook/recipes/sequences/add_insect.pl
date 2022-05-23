#!/usr/bin/perl
# add_insect.pl: demonstrate client-side mysql_insertid attribute
# for getting the most recent AUTO_INCREMENT value.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

# Show how to generate an AUTO_INCREMENT value and retrieve it using
# the database handle.  Then do same with statement handle.

{ # begin scope

#@ _USE_DBH_
$dbh->do ("INSERT INTO insect (name,date,origin)
           VALUES('moth','2014-09-14','windowsill')");
my $seq = $dbh->{mysql_insertid};
#@ _USE_DBH_
print "seq (using dbh): $seq\n";

} # end scope

{ # begin scope

#@ _USE_STH_
my $sth = $dbh->prepare ("INSERT INTO insect (name,date,origin)
                          VALUES('moth','2014-09-14','windowsill')");
$sth->execute ();
my $seq = $sth->{mysql_insertid};
#@ _USE_STH_
print "seq (using sth): $seq\n";
# ... can also get the value with $dbh in this case...
$seq = $dbh->{mysql_insertid};
print "seq (using dbh): $seq\n";

} # end scope

$dbh->disconnect ();
