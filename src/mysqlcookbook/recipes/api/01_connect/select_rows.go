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

    sql := "SELECT id,name FROM profile"
    res, err := db.Query(sql)

    if err != nil {
        log.Fatal(err)
    }
    defer res.Close()

    for res.Next() {
            var profile Profile
            err = res.Scan(&profile.id, &profile.name)
        if err != nil {
            log.Fatal(err)
        }

        fmt.Printf("%v\n", profile)
   }
}
