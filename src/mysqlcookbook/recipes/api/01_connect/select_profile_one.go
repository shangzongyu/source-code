package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

type Profile struct {
	id   int
	name string
	cats int
}

func main() {

	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")

	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	row := db.QueryRow("SELECT id, name, cats FROM profile where id=3")

    var profile Profile
    err = row.Scan(&profile.id, &profile.name, &profile.cats)

	if err == sql.ErrNoRows {
        fmt.Println("No row matched!")
    } else if err != nil {
		log.Fatal(err)
	} else {
        fmt.Printf("%v\n", profile)
    }

}
