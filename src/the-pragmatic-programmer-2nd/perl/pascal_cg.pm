#!/usr/bin/perl -w
package CG;
use strict;

# Code generator for 'Pascal' (see cg_base.pl)

sub blankLine() { print "\n"; }
sub comment()   { print "{$_[0] }\n"; }
sub startMsg()  { print "$_[0] = packed record\n"; }
sub endMsg()    { print "end;\n\n"; }
 
sub arrayType() {
  my ($name, $type, $size) = @_;
  $size--;
  print "  $name: array[0..$size] of $type;\n";
}

sub simpleType() {
  my ($name, $type) = @_;
  print "  $name: $type;\n";
}

1;
