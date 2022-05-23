#!/usr/bin/perl
# hexdump.pl: Dump input in hex format.

# Usage: hexdump.pl [ filename ] ...

use strict;
use warnings;

sub hexdump
{
my $pos = 0;
my $buf;
my $map =
  '........... ....' .
  '................' .
  ' !"#$%&\'()*+,-./' .
  '0123456789:;<=>?' .
  '@ABCDEFGHIJKLMNO' .
  'PQRSTUVWXYZ[\]^_' .
  '`abcdefghijklmno' .
  'pqrstuvwxyz{|}~.' .
  '................' .
  '................' .
  '................' .
  '................' .
  '................' .
  '................' .
  '................' .
  '................' ;

  while (read (STDIN, $buf, 16))
  {
    my $len = length ($buf);
    my $hex;
    my $asc;
    for my $i (0 .. $len-1)
    {
      $hex .= " " if $i == 8;
      my $c = substr ($buf, $i, 1);
      $hex .= unpack ("H2", $c) . " ";
      $asc .= substr ($map, ord ($c), 1);
    }
    printf "%05x: %-48s %s\n", $pos, $hex, $asc;
    $pos += 16;
  }
}

# Read stdin if no files were named, otherwise read each named file

if (@ARGV == 0)
{
  hexdump ();
}
else
{
  while (@ARGV)
  {
    open (STDIN, shift (@ARGV));
    hexdump ();
  }
}
