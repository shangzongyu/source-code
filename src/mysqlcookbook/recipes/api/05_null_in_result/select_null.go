// select_null.go : Selecting NULL values in Golang
package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

type Profile struct {
	name     string
	birthday string
}

func main() {

	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")

	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	sql := "SELECT name, COALESCE(birth, '') as birthday from profile WHERE id = 9"
	res, err := db.Query(sql)
	if err != nil {
		log.Fatal(err)
	}
	defer res.Close()

	if err != nil {
		log.Fatal(err)
	}

	for res.Next() {
		var profile Profile
		err = res.Scan(&profile.name, &profile.birthday)
		if err != nil {
			log.Fatal(err)
		}

		fmt.Printf("%v\n", profile)
	}
}
