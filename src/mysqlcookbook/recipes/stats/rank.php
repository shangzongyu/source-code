<?php
# rank.php: assign ranks to a set of values

require_once "Cookbook.php";

$dbh = Cookbook::connect ();

# Assign ranks using position (row number) within the set of values,
# except that tied values all get the rank accorded the first of them.

#@ _ASSIGN_RANKS_
$sth = $dbh->query ("SELECT score FROM t ORDER BY score DESC");
$rownum = 0;
$rank = 0;
unset ($prev_score);
print ("Row\tRank\tScore\n");
while (list ($score) = $sth->fetch ())
{
  ++$rownum;
  if ($rownum == 1 || $prev_score != $score)
    $rank = $rownum;
  print ("$rownum\t$rank\t$score\n");
  $prev_score = $score;
}
#@ _ASSIGN_RANKS_

$dbh = NULL;
?>
