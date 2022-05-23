// mycnf.go : Reads ~/.my.cnf file for DSN construct
package main

import (
	"fmt"

	"github.com/svetasmirnova/mysqlcookbook/recipes/lib"
)

func main() {

	fmt.Println("Calling db.MyCnf()")
    var dsn string

    dsn, err := cookbook.MyCnf("client")
    if err != nil {
	  fmt.Printf("error: %v\n", err)
    } else {
	  fmt.Printf("DSN is: %s\n", dsn)
    }
}
