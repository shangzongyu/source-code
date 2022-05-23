#!/usr/bin/perl
# placeholder.pl: demonstrate statement processing in Perl
# (with placeholders)

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

{ # begin scope

print "Execute INSERT statement with do()\n";
#@ _PLACEHOLDER_DO_
my $count = $dbh->do ("INSERT INTO profile (name,birth,color,foods,cats)
                       VALUES(?,?,?,?,?)",
                      undef,
                      "De'Mont", "1973-01-12", undef, "eggroll", 4);
#@ _PLACEHOLDER_DO_
printf "Number of rows inserted: %d\n", $count;

} # end scope

{ # begin scope

print "Execute INSERT statement with prepare() + execute()\n";
#@ _PLACEHOLDER_PREPARE_EXECUTE_1_
my $sth = $dbh->prepare ("INSERT INTO profile (name,birth,color,foods,cats)
                          VALUES(?,?,?,?,?)");
my $count = $sth->execute ("De'Mont", "1973-01-12", undef, "eggroll", 4);
#@ _PLACEHOLDER_PREPARE_EXECUTE_1_
printf "Number of rows inserted: %d\n", $count;

} # end scope

{ # begin scope

print "Select rows using placeholder\n";
#@ _PLACEHOLDER_PREPARE_EXECUTE_2_
my $sth = $dbh->prepare ("SELECT * FROM profile WHERE cats > ?");
$sth->execute (2);
while (my $ref = $sth->fetchrow_hashref ())
{
  print "id: $ref->{id}, name: $ref->{name}, cats: $ref->{cats}\n";
}
#@ _PLACEHOLDER_PREPARE_EXECUTE_2_

} # end scope

{ # begin scope

print "Construct INSERT statement usinq quote()\n";
#@ _QUOTE_
my $stmt = sprintf ("INSERT INTO profile (name,birth,color,foods,cats)
                     VALUES(%s,%s,%s,%s,%s)",
                    $dbh->quote ("De'Mont"),
                    $dbh->quote ("1973-01-12"),
                    $dbh->quote (undef),
                    $dbh->quote ("eggroll"),
                    $dbh->quote (4));
my $count = $dbh->do ($stmt);
#@ _QUOTE_
print "Statement:\n$stmt\n";
print "Number of rows inserted: $count\n";

} # end scope

$dbh->disconnect ();
