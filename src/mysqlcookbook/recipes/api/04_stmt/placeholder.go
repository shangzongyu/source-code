package main

import (
  "log"
  "github.com/svetasmirnova/mysqlcookbook/recipes/lib"
)

func main() {
  db, err := cookbook.Connect()
  if err != nil {
    log.Fatal(err)
  }
  defer db.Close()

  stmt := `INSERT INTO profile (name,birth,color,foods,cats)
           VALUES(?,?,?,?,?)`

  _, err = db.Exec(stmt, "De'Mont", "1973-01-12", nil, "eggroll", 4)
  if err != nil {
    log.Fatal(err)
  }

  pstmt, err := db.Prepare(`INSERT INTO profile (name,birth,color,foods,cats)
                 VALUES(?,?,?,?,?)`)
  if err != nil {
    log.Fatal(err)
  }
  defer pstmt.Close()

  _, err = pstmt.Exec("De'Mont", "1973-01-12", nil, "eggroll", 4)
  if err != nil {
    log.Fatal(err)
  }
}
