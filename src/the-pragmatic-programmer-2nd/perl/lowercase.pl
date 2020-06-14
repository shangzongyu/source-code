#!/usr/bin/perl -w
#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
#
# From "Text Manipulation",
# Convert files in current directory with uppercase names to lower case
#

use strict;


foreach (<*>) {
  if (-f && ($_ eq uc($_))) {
    rename $_, lc($_) or die "Can't rename $_: $!"
  }
}
  
