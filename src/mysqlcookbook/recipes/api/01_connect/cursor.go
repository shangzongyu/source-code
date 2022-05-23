package main
import (
  "log"
  "database/sql"
  _"github.com/go-sql-driver/mysql"
)
func main() {
  db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")
  if err != nil {
    panic(err.Error())
  }
  defer db.Close()

  update, err := db.Exec("UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'")
  if err != nil {
		log.Fatal(err)
	}

  rows, err := update.RowsAffected()
	if err != nil {
		log.Fatal(err)
	}
	if rows != 1 {
		log.Fatalf("expected to affect 1 row, affected %d", rows)
	}

    log.Printf("Rows affected %d\n", rows)

}
