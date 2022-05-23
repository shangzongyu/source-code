<?php
# args.php: demonstrate use of argument variables for PHP command-line scripts

#@ _FRAG_
print ("Number of arguments: $argc\n");
print ("Program name: $argv[0]\n");
print ("Arguments following program name:\n");
if ($argc == 1)
  print ("None\n");
else
{
  for ($i = 1; $i < $argc; $i++)
    print ("$i: $argv[$i]\n");
}
#@ _FRAG_
?>
