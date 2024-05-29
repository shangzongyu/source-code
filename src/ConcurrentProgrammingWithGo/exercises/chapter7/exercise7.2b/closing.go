package main

import (
	"fmt"
	"time"
)

func receiver(messages <-chan []int) {
	for {
		msg := <-messages
		fmt.Println(time.Now().Format("15:04:05"), "Received:", msg)
		time.Sleep(1 * time.Second)
	}
}

func main() {
	msgChannel := make(chan []int)
	go receiver(msgChannel)
	for i := 1; i <= 3; i++ {
		fmt.Println(time.Now().Format("15:04:05"), "Sending:", i)
		msgChannel <- make([]int, 10)
		time.Sleep(1 * time.Second)
	}
	close(msgChannel)
	time.Sleep(3 * time.Second)
}
