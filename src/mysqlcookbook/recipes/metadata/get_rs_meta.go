package main

import (
  "fmt"
  "log"
  "flag"
  "github.com/svetasmirnova/mysqlcookbook/recipes/lib"
)

func main() {
  db, err := cookbook.Connect()
  if err != nil {
    log.Fatal(err)
  }
  defer db.Close()

  stmt := "SELECT name, birth FROM profile"
  flag.Parse()
  values := flag.Args()
  if len(values) > 0 {
    stmt = values[0]
  }
  fmt.Printf("Statement: %s\n", stmt)

  rows, err := db.Query(stmt)
  if err != nil {
    log.Fatal(err)
  }
  defer rows.Close()

  // metadata information becomes available at this point ...
  cols, err := rows.ColumnTypes()
  if err != nil {
    log.Fatal(err)
  }

  ncols := len(cols)
  fmt.Printf("Number of columns: %d\n", ncols)
  if (ncols == 0) {
    fmt.Println("Note: statement has no result set")
  }

  for i := 0; i < ncols; i++ {
    fmt.Printf("---- Column %d (%s) ----\n", i, cols[i].Name())
    fmt.Printf("DatabaseTypeName: %s\n", cols[i].DatabaseTypeName())

    collen, ok := cols[i].Length()
    if ok {
      fmt.Printf("Length: %d\n", collen)
    }

    precision, scale, ok := cols[i].DecimalSize()
    if ok {
      fmt.Printf("DecimalSize precision: %d, scale: %d\n", precision, scale)
    }

    colnull, ok := cols[i].Nullable()
    if ok {
      fmt.Printf("Nullable: %t\n", colnull)
    }

    fmt.Printf("ScanType: %s\n", cols[i].ScanType())
  }
}
