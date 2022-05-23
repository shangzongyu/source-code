#!/bin/sh
# test_python.sh: test the cmdline.py script

# change these as necessary
PROGRAM=./cmdline.py
USER_NAME=cbuser
PASSWORD=cbpass
HOST_NAME=localhost

echo "Test short options with no space after option letters:"
COMMAND="$PROGRAM -u$USER_NAME -p$PASSWORD -h$HOST_NAME"
echo "$COMMAND"
$COMMAND

# note that password CANNOT have space between option and value
echo "Test short options with space after option letters:"
COMMAND="$PROGRAM -u $USER_NAME -p$PASSWORD -h $HOST_NAME"
echo "$COMMAND"
$COMMAND

echo "Test long options:"
COMMAND="$PROGRAM --user=$USER_NAME --password=$PASSWORD --host=$HOST_NAME"
echo "$COMMAND"
$COMMAND

echo "Test short option with missing argument:"
COMMAND="$PROGRAM -u"
echo "$COMMAND"
$COMMAND

echo "Test long option with missing argument:"
COMMAND="$PROGRAM --user"
echo "$COMMAND"
$COMMAND

echo "Test short password option with no password on command line:"
COMMAND="$PROGRAM -u $USER_NAME -p -h $HOST_NAME"
echo "$COMMAND"
$COMMAND

echo "Test long password option with no password on command line:"
COMMAND="$PROGRAM --user=$USER_NAME --password --host=$HOST_NAME"
echo "$COMMAND"
$COMMAND
