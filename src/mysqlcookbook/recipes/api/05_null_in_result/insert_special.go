// insert_special.go : Inserting special values to table.
package main

import (
	"context"
	"database/sql"
	"log"
	"time"

	_ "github.com/go-sql-driver/mysql"
)

type profile struct {
	name  string
	birth string
	color int
	foods string
	cats  int
}

func insert(db *sql.DB, p profile) error {
	query := "INSERT INTO profile(name, birth, color, foods, cats) VALUES (?, ?, ?, ?, ?)"
	ctx, cancelfunc := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancelfunc()
	stmt, err := db.PrepareContext(ctx, query)
	if err != nil {
		log.Printf("Error %s when preparing SQL statement", err)
		return err
	}
	defer stmt.Close()
	res, err := stmt.ExecContext(ctx, p.name, p.birth, p.color, p.foods, p.cats)
	if err != nil {
		log.Printf("Error %s when inserting row into profile table", err)
		return err
	}
	rows, err := res.RowsAffected()
	if err != nil {
		log.Printf("Error %s when finding rows affected", err)
		return err
	}
	log.Printf("%d profile created ", rows)
	prdID, err := res.LastInsertId()
	if err != nil {
		log.Printf("Error %s when getting last inserted profile", err)
		return err
	}
	log.Printf("Profile with ID %d created", prdID)
	return nil
}

func main() {

	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3306)/cookbook")
    if err != nil {
        log.Fatal(err)
    }
	defer db.Close()

	p := profile{
		name:  "askdba",
		birth: "1985-02-28",
		color: 2,
		foods: "lutefisk",
		cats:  0,
	}
	err = insert(db, p)
	if err != nil {
		log.Printf("Insert profile failed with error %s", err)
		return
	}

	if err != nil {
		log.Fatal(err)
	}

}
