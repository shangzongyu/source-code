#!/usr/bin/perl
# booksales.pl: show how to use LAST_INSERT_ID(expr)

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

$dbh->do ("INSERT INTO booksales (title,copies)
           VALUES('The Greater Trumps',LAST_INSERT_ID(1))
           ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+1)");
my $count = $dbh->{mysql_insertid};
print "count: $count\n";

$dbh->disconnect ();
