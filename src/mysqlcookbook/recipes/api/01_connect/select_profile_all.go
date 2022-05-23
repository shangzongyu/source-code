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

	res, err := db.Query("SELECT id, name, cats FROM profile")


	if err != nil {
		log.Fatal(err)
	}
	defer res.Close()

	for res.Next() {

		var profile Profile
		err := res.Scan(&profile.id, &profile.name, &profile.cats)

		if err != nil {
			log.Fatal(err)
		}

		fmt.Printf("%+v\n", profile)
	}
}
