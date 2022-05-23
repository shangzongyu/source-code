#!/usr/bin/perl
# test_csv.pl: Text::CSV_XS tester.

use strict;
use warnings;
use IO::Handle;
use Text::CSV_XS;

my $icsv = Text::CSV_XS->new ({ binary => 1, eol => "\n" });
my $ocsv = Text::CSV_XS->new ({ binary => 1, sep_char => "|", eol => "\n" });

my $in = new IO::Handle;
my $out = new IO::Handle;
$in->fdopen (fileno (STDIN), "r") or die "Cannot fdopen STDIN: $!\n";
$out->fdopen (fileno (STDOUT), "w") or die "Cannot fdopen STDOUT: $!\n";

while (!$in->eof ())
{
  my $ref = $icsv->getline ($in)
    or die "error reading line: " . $icsv->error_input ();
  my @val = @{$ref};
  s/\cK/ /g foreach @val;
  $ocsv->print ($out, \@val) or die "print() error\n";
}
