//  leap.go: Leap-year test of ISO date strings
package main

import "fmt"
import "time"


func main() {

   fmt.Println("Searching for leap years")
   const (
   	    layoutISO = "2006-01-02"
        layoutUS  = "January 2, 2006"
   )
   d1, _ := time.Parse(layoutISO, "1899-01-01")
   d2, _ := time.Parse(layoutISO, "1900-01-01")
   d3, _ := time.Parse(layoutISO, "1999-01-01")
   d4, _ := time.Parse(layoutISO, "2000-06-21")
   d5, _ := time.Parse(layoutISO, "1963-01-01")
   d6, _ := time.Parse(layoutISO, "2024-09-17")

   dates := []time.Time{d1, d2, d3, d4, d5, d6}
   for _, t := range dates {
      fmt.Println(t.Format(layoutUS)) // December 31, 1999
      year := t.Year()
      if year%4 == 0 && year%100 != 0 || year%400 == 0 {
         fmt.Println("The year is a leap year!")
      } else {
         fmt.Println("The year isn't a leap year.")
      }
   }
   }

