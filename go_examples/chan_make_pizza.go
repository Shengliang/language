package main

import "fmt"
import "time"
import "strconv"

var pizzaNum = 0
var pizza = ""

func makeDough(stringChan chan string) {
	pizzaNum++
	pizza = "Pizza #" + strconv.Itoa(pizzaNum)
        fmt.Println("S1: Make Dough" + pizza)
	stringChan <- pizza
	time.Sleep(time.Millisecond * 10)
}

func addSauce(stringChan chan string) {
	pizza := <-stringChan
	fmt.Println("S2: Add Sauce" + pizza)
	stringChan <- pizza
	time.Sleep(time.Millisecond * 10)
}

func addToppings(stringChan chan string) {
	pizza := <-stringChan
	fmt.Println("S3: Add Toppings" + pizza)
	time.Sleep(time.Millisecond * 10)
}

func main() {

	stringChan := make(chan string)
	for i := 0; i < 3; i++ {
		go makeDough(stringChan)
		go addSauce(stringChan)
		go addToppings(stringChan)
		time.Sleep(time.Millisecond * 300)
	}
}
