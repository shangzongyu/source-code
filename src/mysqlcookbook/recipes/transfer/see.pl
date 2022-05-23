#!/usr/bin/perl
# see.pl: Print nonprinting chars sensibly.

use strict;
use warnings;

while (<>)
{
  my $len = length ($_);
  for my $i (0 .. $len-1)
  {
    my $c = substr ($_, $i, 1);
    my $o = ord ($c);
    if ($o == 10)   # (10 == linefeed)
    {
      $c = "\$\n"
    }
    elsif ($o < 32)   # control char? (32 = space)
    {
      $c = sprintf ("^%c", $o+64);
    }
    elsif ($o == 92)  # \ -> \\ (92 = backslash)
    {
      $c = "\\\\";
    }
    elsif ($o >= 127)     # DEL and non-ASCII as octal
    {
      $c = sprintf ("\\%3o", $o);
    }
    print $c;
  }
}
