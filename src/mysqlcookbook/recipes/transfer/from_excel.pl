#!/usr/bin/perl
# from_excel.pl: Read Excel spreadsheet, write tab-delimited,
# linefeed-terminated output to the standard output.

use strict;
use warnings;
use Spreadsheet::ParseExcel::Simple;

@ARGV or die "Usage: $0 excel-file\n";

my $xls = Spreadsheet::ParseExcel::Simple->read ($ARGV[0]);
foreach my $sheet ($xls->sheets ())
{
  while ($sheet->has_data ())
  {  
    my @data = $sheet->next_row ();
    print join ("\t", @data) . "\n";
  }
}
