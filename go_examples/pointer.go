package main

import "fmt"

func swap(px, py *int) {
	tmp := *px
	*px = *py
	*py = tmp
}

func swap2(x, y int) (int, int) {
	return y, x
}

func main() {
	var a = 3
	var b = 4
	fmt.Println(a, b)
	swap(&a, &b)
	fmt.Println(a, b)
        x, y := swap2(a,b)
	fmt.Println(x, y)
}
