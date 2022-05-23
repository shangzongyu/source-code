#!/usr/bin/python3
# seqdiag.py: test AUTO_INCREMENT operations

import mysql.connector
import cookbook

def init_table(conn):
  try:
    cursor = conn.cursor()
    cursor.execute("DROP TABLE IF EXISTS seqdiag")
    cursor.execute('''
                   CREATE TABLE seqdiag
                   (seq INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (seq))
                   ''')
    cursor.close()
    conn.commit()
  except mysql.connector.Error as e:
    print("Cannot create seqdiag table")
    print("Error: %s" % e)

def gen_seq_val(cursor):
  try:
    cursor.execute("INSERT INTO seqdiag (seq) VALUES(NULL)")
  except mysql.connector.Error as e:
    print("Cannot create AUTO_INCREMENT value")
    print("Error: %s" % e)

conn = cookbook.connect()

init_table(conn)
cursor = conn.cursor()

gen_seq_val(cursor)
seq = cursor.lastrowid
print("seq: %d" % seq)
cursor.execute("SET @x = LAST_INSERT_ID(48)")
seq = cursor.lastrowid
print("seq after SET via lastrowid: %d" % seq)
cursor.execute("SELECT LAST_INSERT_ID()")
row = cursor.fetchone()
seq = row[0]
print("seq after SET via LAST_INSERT_ID(): %d" % seq)

cursor.close()
conn.commit()
conn.close()

conn1 = cookbook.connect()
conn2 = cookbook.connect()

# Issue two sequence-generating queries using separate connection
# objects to see whether they interfere with each other's
# lastrowid value.
#@ _INDEPENDENT_CONNS_
cursor1 = conn1.cursor()
cursor2 = conn2.cursor()
gen_seq_val(cursor1)   # issue query that generates a sequence number
gen_seq_val(cursor2)   # issue another, using a different cursor
seq1 = cursor1.lastrowid
seq2 = cursor2.lastrowid
print("seq1: %d seq2: %d " % (seq1, seq2))  # these values will be different
cursor1.close()
cursor2.close()
#@ _INDEPENDENT_CONNS_

conn1.close()
conn2.close()
