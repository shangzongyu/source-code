<?php
# shuffle_deck.php: shuffle the deck table and display resulting card order

require_once "Cookbook.php";

$dbh = Cookbook::connect ();

# "shuffle" the deck by randomizing it, then print card information

#@ _SHUFFLE_DECK_
function shuffle_deck ($dbh)
{
  $sth = $dbh->query ("SELECT face, suit FROM deck ORDER BY RAND()");
  $sth->setFetchMode (PDO::FETCH_OBJ);
  return ($sth->fetchAll ());
}
#@ _SHUFFLE_DECK_

$card = shuffle_deck ($dbh);
#@ _PRINT_ARRAY_
for ($i = 0; $i < count ($card); $i++)
  printf ("%s %s\n", $card[$i]->face, $card[$i]->suit);
#@ _PRINT_ARRAY_
if (count ($card) == 0)
  printf ("No cards found in deck\n");

$dbh = NULL;
?>
