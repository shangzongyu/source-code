#!/usr/bin/perl -w
package CG;
use strict;

# Code generator for 'C' (see cg_base.pl)

sub blankLine() { print "\n"; }
sub comment()   { print "/*$_[0] */\n"; }
sub startMsg()  { print "typedef struct {\n"; }
sub endMsg()    { print "} $_[0];\n\n"; }
 
sub arrayType() {
  my ($name, $type, $size) = @_;
  print "  $type $name\[$size];\n";
}

sub simpleType() {
  my ($name, $type) = @_;
  print "  $type $name;\n";
}

1;
