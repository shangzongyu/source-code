// transaction.go: simple transaction demonstration

// By default, this creates an InnoDB table.  If you specify a storage
// engine on the command line, that will be used instead.  Normally,
// this should be a transaction-safe engine that is supported by your
// server.  However, you can pass a nontransactional storage engine
// to verify that rollback doesn't work properly for such engines.

// The script uses a table named "money" and drops it if necessary.
// Change the name if you have a valuable table with that name. :-)
package main

import (
  "log"
  "fmt"
  "flag"
  "database/sql"
  "github.com/svetasmirnova/mysqlcookbook/recipes/lib"
)

func initTable(db *sql.DB, tblEngine string) (error) {
  var queries [4]string
  var err error = nil
  queries[0] = "DROP TABLE IF EXISTS money"
  queries[1] = "CREATE TABLE money (name CHAR(5), amt INT, PRIMARY KEY(name)) ENGINE = " + tblEngine
  queries[2] = "INSERT INTO money (name, amt) VALUES('Eve', 10)"
  queries[3] = "INSERT INTO money (name, amt) VALUES('Ida', 0)"

  for _, query := range queries {
    _, err = db.Exec(query)
    if err != nil {
      fmt.Println("Cannot initialize test table")
      fmt.Printf("Error: %s\n", err.Error())
      return err
    }
  }

  return nil
}

func displayTable(db *sql.DB) (error) {
  rows, err := db.Query("SELECT name, amt FROM money")
  if err != nil {
    return err
  }
  defer rows.Close()

  for rows.Next() {
    var (
      name string
      amt  int32
    )
    if err := rows.Scan(&name, &amt); err != nil {
      fmt.Println("Cannot display contents of test table")
      fmt.Printf("Error: %s\n", err.Error())
      return err
    }

    fmt.Printf("%s has $%d\n", name, amt)
  }

  return nil
}

func runTransaction(db *sql.DB, queries []string) (error) {
  tx, err := db.Begin()
  if err != nil {
    return err
  }

  for _, query := range queries {
    _, err := tx.Exec(query)
    if err != nil {
      fmt.Printf("Transaction failed, rolling back.\nError was: %s\n",
                 err.Error())
      if txerr := tx.Rollback(); err != nil {
        return txerr
      }
      return err
    }
  }

  if err := tx.Commit(); err != nil {
    return err
  }

  return nil
}

func main() {
  db, err := cookbook.Connect()
  if err != nil {
    log.Fatal(err)
  }
  defer db.Close()

  var tblEngine string = "InnoDB"
  flag.Parse()
  values := flag.Args()
  if len(values) > 0 {
    tblEngine = values[0]
  }
  fmt.Printf("Using storage engine %s to test transactions\n", tblEngine)

  fmt.Println("----------")
  fmt.Println("This transaction should succeed.")
  fmt.Println("Table contents before transaction:")

  if err := initTable(db, tblEngine); err != nil {
    log.Fatal(err)
  }

  if err = displayTable(db); err != nil {
    log.Fatal(err)
  }

  var trx = []string{
    "UPDATE money SET amt = amt - 6 WHERE name = 'Eve'",
    "UPDATE money SET amt = amt + 6 WHERE name = 'Ida'",
  }

  runTransaction(db, trx)

  fmt.Println("Table contents after transaction:")
  if err = displayTable(db); err != nil {
    log.Fatal(err)
  }

  fmt.Println("----------")
  fmt.Println("This transaction should fail.")
  fmt.Println("Table contents before transaction:")

  if err := initTable(db, tblEngine); err != nil {
    log.Fatal(err)
  }

  if err = displayTable(db); err != nil {
    log.Fatal(err)
  }

  trx = []string{
    "UPDATE money SET amt = amt - 6 WHERE name = 'Eve'",
    "UPDATE money SET xamt = amt + 6 WHERE name = 'Ida'",
  }

  runTransaction(db, trx);

  fmt.Println("Table contents after transaction:")
  if err = displayTable(db); err != nil {
    log.Fatal(err)
  }
}
