#!/bin/sh
#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---

CMD="java dbc.dbc_ex"
failcount=0

expect_okay() {
    if echo "$*" | $CMD #>/dev/null 2>&1
    then
      :
    else
      echo "FAILED! $*"
      failcount=`expr $failcount + 1`
    fi
}

expect_fail() {
    if echo "$*" | $CMD >/dev/null 2>&1
    then
      echo "FAILED! (Should have failed): $*"
      failcount=`expr $failcount + 1`
    fi
}

report() {
  if [ $failcount -gt 0 ]
  then
    echo -e "\n\n*** FAILED $failcount TESTS\n"
    exit 1 # In case we are part of something larger
  else
    exit 0 # In case we are part of something larger
  fi
}

#
# Start the tests
#

expect_okay F123456789876543210E # Should run thru
expect_fail F5    # Fails, speed too high
expect_fail 1     # Fails, empty
expect_fail F10E1 # Fails, empty
expect_fail F1238 # Fails, skips
expect_okay FE    # Never turn on
expect_fail F1E   # Emptying while running
expect_okay F10E  # Should be ok
report            # Report results
