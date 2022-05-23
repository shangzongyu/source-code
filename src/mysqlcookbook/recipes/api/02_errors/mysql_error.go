// mysql_error.go : MySQL error exception handling
package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

var actor string

func main() {

	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")
	defer db.Close()

	if err != nil {
		log.Fatal(err)
	}

	err = db.QueryRow("SELECT actor FROM actors where actor='Dwayne Jhonson'").Scan(&actor)
	if err != nil {
		if err == sql.ErrNoRows {
			fmt.Print("There were no rows, but otherwise no error occurred")
		} else {
			fmt.Println(err.Error())
		}
	}
	fmt.Println(actor)

	err = db.QueryRow("SELECT actors FROM actors where actor='Dwayne Jhonson'").Scan(&actor)
	if err != nil {
		if err == sql.ErrNoRows {
			fmt.Print("There were no rows, but otherwise no error occurred")
		} else {
			fmt.Println(err.Error())
		}
	}
	fmt.Println(actor)
}
