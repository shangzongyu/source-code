// select.go : Selecting data from table
package main

import (
    "database/sql"
    "fmt"
    "log"

    _ "github.com/go-sql-driver/mysql"
)

type Artist struct {
    id         int
    actor       string
}

func main() {

    db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")

    if err != nil {
        log.Fatal(err)
    }
    defer db.Close()

    res, err := db.Query("SELECT * FROM actors")

    defer res.Close()

    if err != nil {
        log.Fatal(err)
    }

    for res.Next() {

        var artist Artist
        err := res.Scan(&artist.id, &artist.actor)

        if err != nil {
            log.Fatal(err)
        }

        fmt.Printf("%v\n", artist)
    }
}
