#!/usr/bin/perl
# invoice.pl: multiple-table insert where both tables have an AUTO_INCREMENT
# column.  Save master table AUTO_INCREMENT value before inserting detail
# records to avoid losing it.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();
my $sth;
my $inv_id;

#@ _FRAG_
$dbh->do ("INSERT INTO invoice (inv_id,date) VALUES(NULL,CURDATE())");
$inv_id = $dbh->{mysql_insertid};
$sth = $dbh->prepare ("INSERT INTO inv_item (inv_id,qty,description)
                       VALUES(?,?,?)");
$sth->execute ($inv_id, 1, "hammer");
$sth->execute ($inv_id, 3, "nails, box");
$sth->execute ($inv_id, 12, "bandage");
#@ _FRAG_

$dbh->disconnect ();
