#!/usr/bin/perl -w
#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
use strict;

# From "Code Generators",
# usage:  cg_base <language>  <flatfile
#  where <language> identifies a code generator called
#  <language>_cg.pl

my $lang = shift or die "Missing language";
$lang .= "_cg.pm";

require "$lang" or die "Couldn't load $lang";

# Read and parse the file

my $name;

while (<>) {
  chomp;
  if    (/^\s*$/)     { CG::blankLine(); }
  elsif (/^\#(.*)/)   { CG::comment($1); }
  elsif (/^M\s*(.+)/) { CG::startMsg($1); $name = $1; }
  elsif (/^E/)        { CG::endMsg($name); }
  elsif (/^F\s*(\w+)\s+(\w+)$/)
                      { CG::simpleType($1,$2); }
  elsif (/^F\s*(\w+)\s+(\w+)\[(\d+)\]$/)
                      { CG::arrayType($1,$2,$3); }
  else {
    die "Invalid line: $_";
  }
}


