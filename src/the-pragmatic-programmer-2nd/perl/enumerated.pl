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

# From "Text Manipulation",
# Read from standard input a file containing
#
#  line 1:  name
#  line 2:  constant1
#  line 3:  constant2
#    :         :
#
# Produce the file name.h, which contains
#
#   |extern const char* NAME_names[];
#   |typedef enum {
#   |   constant1,
#   |   constant2,
#   |     :
#   | } NAME;
#
# and the file name.c, which contains
#
#   | const char* NAME_names[] = {
#   |   "constant1",
#   |   "constant2",
#   | };
#
# The header file should be included in your normal
# code. This lets you get the name associated
# with a constant by indexing into NAME_names
#

my @consts;

my $name = <>;
die "Invalid format - missing name" unless defined($name);

chomp $name;

# Read in the rest of the file
while (<>) {
  chomp;
  s/^\s*//; s/\s*$//;
  die "Invalid line: $_" unless /^(\w+)$/;
  
  push @consts, $_;
}

# Now generate the file
open(HDR, ">$name.h") or die "Can't open $name.h: $!";
open(SRC, ">$name.c") or die "Can't open $name.c: $!";

my $uc_name = uc($name);
my $array_name = $uc_name . "_names";

print HDR "/* File generated automatically - do not edit */\n";
print HDR "extern const char *$ {array_name}[];";
print HDR "typedef enum {\n  ";
print HDR join ",\n  ", @consts;
print HDR "\n} $uc_name;\n\n";

print SRC "/* File generated automatically - do not edit */\n";
print SRC "const char *$ {array_name}[] = {\n  \"";
print SRC join "\",\n  \"", @consts;
print SRC "\"\n};\n";

close(SRC);
close(HDR);
