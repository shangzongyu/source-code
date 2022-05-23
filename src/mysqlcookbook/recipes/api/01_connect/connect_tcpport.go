// connect_tcpport.go : Connect MySQL server using tcp port number
package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

func main() {
	db, err := sql.Open("mysql", "cbuser:cbpass@tcp(127.0.0.1:3307)/cookbook?charset=utf8mb4")

	if err != nil {
		log.Fatal(err)
	}

	var user string
	err2 := db.QueryRow("SELECT USER()").Scan(&user)

	if err2 != nil {
		log.Fatal(err2)
	}

	fmt.Println("Connected User:", user, "via MySQL TCP/IP localhost on port 3306")
}
