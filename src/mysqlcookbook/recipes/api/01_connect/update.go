// update.go : Update data with Golang example
package main

import (
    "database/sql"
    "fmt"
    "log"

    _ "github.com/go-sql-driver/mysql"
)

type Profile struct {
    id         int
    name       string
}

func main() {

    db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")

    if err != nil {
        log.Fatal(err)
    }
    defer db.Close()

    sql := "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'"
    res, err := db.Exec(sql)

    if err != nil {
        panic(err.Error())
    }

    affectedRows, err := res.RowsAffected()

    if err != nil {
        log.Fatal(err)
    }

    fmt.Printf("The statement affected %d rows\n", affectedRows)
}
