#!/usr/bin/perl
# hashtest.pl: try using MD5() to hash filename paths, see whether
# it's faster.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

$dbh->do ("DROP TABLE IF EXISTS hashtest");
$dbh->do (qq{
          CREATE TABLE hashtest
          (
            hash  CHAR(32) NOT NULL UNIQUE,
            path  VARCHAR(255)
          )
        });

for (my $j = 0; $j < 100000; $j++)
{
  my $s;
  for (my $i = 0; $i < 100; $i++)
  {
    $s .= chr (int ( rand () * 26 ) + 97);
  }
  $dbh->do (qq{
            INSERT INTO hashtest (hash,path) VALUES(MD5(?),?)
            }, undef, $s, $s);
}

$dbh->disconnect ();
