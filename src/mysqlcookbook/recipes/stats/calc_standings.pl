#!/usr/bin/perl
# calc_standings.pl: calculate team standings, displaying each of the
# four groups of records from the standings2 table separately.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

# Compute best wins-losses value for each half season, each division

$dbh->do (qq{
    CREATE TEMPORARY TABLE firstplace
    SELECT half, division, MAX(wins-losses) AS wl_diff
    FROM standings2
    GROUP BY half, division
});

# Compute standings for each half season, division, with leader
# GB displayed as "-"

my $sth = $dbh->prepare (qq{
  SELECT st.half, st.division, st.team, st.wins AS W, st.losses AS L,
  TRUNCATE(st.wins/(st.wins+st.losses),3) AS PCT,
  IF(fp.wl_diff = st.wins-st.losses,
     '-',TRUNCATE((fp.wl_diff - (st.wins-st.losses)) / 2,1)) AS GB
  FROM standings2 AS st, firstplace AS fp
  WHERE st.half = fp.half AND st.division = fp.division
  ORDER BY st.half, st.division, st.wins-st.losses DESC, PCT DESC
});
$sth->execute ();

#@ _DISPLAY_STANDINGS_
my ($cur_half, $cur_div) = ("", "");
while (my ($half, $div, $team, $wins, $losses, $pct, $gb)
          = $sth->fetchrow_array ())
{
  if ($cur_half ne $half || $cur_div ne $div) # new group of standings?
  {
    # print standings header and remember new half/division values
    print "\n$div Division, season half $half\n";
    printf "%-20s  %3s  %3s  %5s  %s\n", "Team", "W", "L", "PCT", "GB";
    $cur_half = $half;
    $cur_div = $div;
  }
  printf "%-20s  %3d  %3d  %5s  %s\n", $team, $wins, $losses, $pct, $gb;
}
#@ _DISPLAY_STANDINGS_

$dbh->disconnect ();
