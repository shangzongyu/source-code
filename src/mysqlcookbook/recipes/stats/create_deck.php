<?php
# create_deck.php: create a deck table and populate it with cards
# (13 faces, 4 suits)

require_once "Cookbook.php";

$dbh = Cookbook::connect ();

# drop and recreate the deck table, then populate it

#@ _CREATE_TABLE_
$sth = $dbh->exec ("DROP TABLE IF EXISTS deck");

$sth = $dbh->exec ("
  CREATE TABLE deck
  (
    face  ENUM('A', 'K', 'Q', 'J', '10', '9', '8',
               '7', '6', '5', '4', '3', '2') NOT NULL,
    suit  ENUM('hearts', 'diamonds', 'clubs', 'spades') NOT NULL
  )
");

$face_array = array ("A", "K", "Q", "J", "10", "9", "8",
                     "7", "6", "5", "4", "3", "2");
$suit_array = array ("hearts", "diamonds", "clubs", "spades");

# insert a "card" into the deck for each combination of suit and face

$sth = $dbh->prepare ("INSERT INTO deck (face,suit) VALUES(?,?)");
foreach ($face_array as $face)
  foreach ($suit_array as $suit)
    $sth->execute (array ($face, $suit));
#@ _CREATE_TABLE_

$dbh = NULL;
?>
