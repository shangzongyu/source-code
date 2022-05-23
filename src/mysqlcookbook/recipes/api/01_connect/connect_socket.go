// connect_socket.go : Connect MySQL server using socket
package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

func main() {
	db, err := sql.Open("mysql", "cbuser:cbpass@unix(/tmp/mysql.sock)/cookbook?charset=utf8mb4")
	defer db.Close()

	if err != nil {
		log.Fatal(err)
	}

	var user string
	err = db.QueryRow("SELECT USER()").Scan(&user)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Connected User:", user, "via MySQL socket")
}
