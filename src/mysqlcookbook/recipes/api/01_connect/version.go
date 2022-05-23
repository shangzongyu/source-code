package main

import (
    "database/sql"
    "fmt"
    "log"

    _ "github.com/go-sql-driver/mysql"
)

func main() {

    db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")

    if err != nil {
        log.Fatal(err)
    }
    defer db.Close()

    var version string

    err = db.QueryRow("SELECT VERSION()").Scan(&version)

    if err != nil {
        log.Fatal(err)
    }

    fmt.Println(version)
}
