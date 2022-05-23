// null-in-result.go : Selecting NULL values in Golang
package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

type Profile struct {
	name     string
	birth sql.NullString
	foods    sql.NullString
}

func main() {

	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")

	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	sql := "SELECT name, birth, foods FROM profile"
	res, err := db.Query(sql)

	if err != nil {
		log.Fatal(err)
	}
	defer res.Close()

	for res.Next() {
		var profile Profile
		err = res.Scan(&profile.name, &profile.birth, &profile.foods)
		if err != nil {
			log.Fatal(err)
		}

		if profile.birth.Valid && profile.foods.Valid {
			fmt.Printf("name: %s, birth: %s, foods: %s\n",
				profile.name, profile.birth.String, profile.foods.String)
		} else if profile.birth.Valid {
			fmt.Printf("name: %s, birth: %s, foods: NULL\n",
				profile.name, profile.birth.String)
		} else if profile.foods.Valid {
			fmt.Printf("name: %s, birth: NULL, foods: %s\n",
				profile.name, profile.foods.String)
		} else {
			fmt.Printf("name: %s, birth: NULL, foods: NULL\n",
				profile.name)
		}
	}
}
