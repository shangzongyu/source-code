<?php
# calc_standings.php: calculate team standings, displaying each of the
# four groups of records from the standings2 table separately in an
# HTML table.

require_once "Cookbook.php";

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Cannot connect to server: " . $e->getMessage () . "\n");
}

# Compute best wins-losses value for each half season, each division.
# Then compute standings for each half season, division, with leader
# GB displayed as "-".

try
{
  $sth = $dbh->exec ("
    CREATE TEMPORARY TABLE firstplace
    SELECT half, division, MAX(wins-losses) AS wl_diff
    FROM standings2
    GROUP BY half, division
  ");

  $sth = $dbh->query ("
    SELECT st.half, st.division, st.team, st.wins AS W, st.losses AS L,
    TRUNCATE(st.wins/(st.wins+st.losses),3) AS PCT,
    IF(fp.wl_diff = st.wins-st.losses,
       '-',TRUNCATE((fp.wl_diff - (st.wins-st.losses)) / 2,1)) AS GB
    FROM standings2 AS st, firstplace AS fp
    WHERE st.half = fp.half AND st.division = fp.division
    ORDER BY st.half, st.division, st.wins-st.losses DESC, PCT DESC
  ");
}
catch (PDOException $e)
{
  die ("Cannot execute statement: " . $e->getMessage () . "\n");
}

$cur_half = "";
$cur_div = "";
while (list ($half, $div, $team, $wins, $losses, $pct, $gb)
         = $sth->fetch ())
{
  if ($cur_half != $half || $cur_div != $div) # new group of standings?
  {
    if ($cur_half != "")    # if there was a group in progress,
      print ("</table>\n"); # close the table
    # print standings header and remember new half/division values
    print ("<p>\n");
    print (htmlspecialchars ("$div Division, season half $half\n"));
    print ("</p>\n");
    print ("<table>\n");
    print ("<tr>\n");
    print ("<th>Team</th>\n");
    print ("<th>W</th>\n");
    print ("<th>L</th>\n");
    print ("<th>PCT</th>\n");
    print ("<th>GB</th>\n");
    print ("</tr>\n");
    $cur_half = $half;
    $cur_div = $div;
  }
  print ("<tr>\n");
  print ("<td>" . htmlspecialchars ($team) . "</td>\n");
  print ("<td align=\"right\">" . htmlspecialchars ($wins) . "</td>\n");
  print ("<td align=\"right\">" . htmlspecialchars ($losses) . "</td>\n");
  print ("<td align=\"right\">" . htmlspecialchars ($pct) . "</td>\n");
  print ("<td align=\"right\">" . htmlspecialchars ($gb) . "</td>\n");
  print ("</tr>\n");
}
if ($cur_half != "")    # if there was a group in progress,
  print ("</table>\n"); # close the table

$dbh = NULL;
?>
