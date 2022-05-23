#!/usr/bin/python3
# transaction.py: simple transaction demonstration

# By default, this creates an InnoDB table.  If you specify a storage
# engine on the command line, that will be used instead.  Normally,
# this should be a transaction-safe engine that is supported by your
# server.  However, you can pass a nontransactional storage engine
# to verify that rollback doesn't work properly for such engines.

# The script uses a table named "money" and drops it if necessary.
# Change the name if you have a valuable table with that name. :-)

import sys
import mysql.connector
import cookbook

# Create the example table and populate it with a couple of rows

def init_table(conn, tbl_engine):
  try:
    cursor = conn.cursor()
    cursor.execute("DROP TABLE IF EXISTS money")
    cursor.execute("CREATE TABLE money (name CHAR(5), amt INT, PRIMARY KEY(name)) ENGINE = "
                              + tbl_engine)
    cursor.execute("INSERT INTO money (name, amt) VALUES('Eve', 10)")
    cursor.execute("INSERT INTO money (name, amt) VALUES('Ida', 0)")
    cursor.close()
    conn.commit()
  except mysql.connector.Error as e:
    print("Cannot initialize test table")
    print("Error: %s" % e)

# Display the current contents of the example table

def display_table(conn):
  try:
    cursor = conn.cursor()
    cursor.execute("SELECT name, amt FROM money")
    while True:
      row = cursor.fetchone()
      if row is None:
        break
      print("%s has $%d" % row)
    cursor.close()
  except mysql.connector.Error as e:
    print("Cannot display contents of test table")
    print("Error: %s" % e)

tbl_engine = "InnoDB" # default storage engine
if len(sys.argv) > 1:
  tbl_engine = sys.argv[1]

print("Using storage engine " + tbl_engine + " to test transactions")

conn = cookbook.connect()

print("----------")
print("This transaction should succeed.")
print("Table contents before transaction:")
init_table(conn, tbl_engine)
display_table(conn)

#@ _DO_TRANSACTION_
try:
  cursor = conn.cursor()
  # move some money from one person to the other
  cursor.execute("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'")
  cursor.execute("UPDATE money SET amt = amt + 6 WHERE name = 'Ida'")
  cursor.close()
  conn.commit()
except mysql.connector.Error as e:
  print("Transaction failed, rolling back. Error was:")
  print(e)
  try:  # empty exception handler in case rollback fails
    conn.rollback()
  except:
    pass
#@ _DO_TRANSACTION_

print("Table contents after transaction:")
display_table(conn)

print("----------")
print("This transaction should fail.")
print("Table contents before transaction:")
init_table(conn, tbl_engine)
display_table(conn)

try:
  cursor = conn.cursor()
  # move some money from one person to the other
  cursor.execute("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'")
  cursor.execute("UPDATE money SET xamt = xamt + 6 WHERE name = 'Ida'")
  cursor.close()
  conn.commit()
except mysql.connector.Error as e:
  print("Transaction failed, rolling back. Error was:")
  print(e)
  try:  # empty exception handler in case rollback fails
    conn.rollback()
  except:
    pass

print("Table contents after transaction:")
display_table(conn)

conn.close()
