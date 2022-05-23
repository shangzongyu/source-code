#!/usr/bin/perl
# to_excel.pl: Read tab-delimited, linefeed-terminated input, write
# Excel-format output to the standard output.

use strict;
use warnings;
use Excel::Writer::XLSX;

binmode (STDOUT);
my $ss = Excel::Writer::XLSX->new (\*STDOUT);
my $ws = $ss->add_worksheet ();
my $row = 0;

while (<>)                            # read each row of input
{
  chomp;
  my @data = split (/\t/, $_, 10000); # split, preserving all fields
  my $col = 0;
  foreach my $val (@data)             # write row to the worksheet
  {
    $ws->write ($row, $col, $val);
    $col++;
  }
  $row++;
}
