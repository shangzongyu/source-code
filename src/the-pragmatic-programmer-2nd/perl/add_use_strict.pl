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
# adds a 'use strict' to all Perl scripts currently missing one.
# Assumes that an existing one starts in column one (so the
# comment above doesn't count).
#
# Passed a directory to search. Only looks at .pl files

use strict;

my $dir = shift or die "Missing directory";

for my $file (glob("$dir/*.pl")) {

  open(IP, "$file") or die "Opening $file: $!";
  undef $/;           # Turn off input record separator --
  my $content = <IP>; # read whole file as one string.
  close(IP);

  if ($content !~ /^use strict/m) {

    rename $file, "$file.bak" or die "Renaming $file: $!";
    open(OP, ">$file") or die "Creating $file: $!";
    
    # Put 'use strict' on first line that
    # doesn't start '#'
    $content =~ s/^(?!#)/\nuse strict;\n\n/m;

    print OP $content;
    close(OP);

    print "Updated $file\n";
  }
  else {
    print "$file already strict\n";
  }
}
