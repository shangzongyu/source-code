// transaction.go : MySQL transaction handling
package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

type Artist struct {
	id    int
	actor string
}

func main() {

	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook?autocommit=false")
	defer db.Close()

	if err != nil {
		log.Fatal(err)
	}

	tx, err := db.Begin()
	sql := "INSERT INTO actors(id,actor) values (0,'Dwayne Johnson')"

	res, err := db.Exec(sql)
	if err != nil {
		panic(err.Error())
		tx.Rollback()
	}

	err = tx.Commit()

	if err != nil {
		panic(err.Error())
	}
	id, err := res.LastInsertId()
	affectedRows, err := res.RowsAffected()

	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("The insert id %d \n", id)
	fmt.Printf("The statement affected %d rows\n", affectedRows)

	sel, err := db.Query("SELECT id,actor FROM actors")

	if err != nil {
		log.Fatal(err)
	}

	for sel.Next() {
		var artist Artist

		err := sel.Scan(&artist.id, &artist.actor)

		if err != nil {
			log.Fatal(err)
		}

		fmt.Printf("%v\n", artist)
	}
}
