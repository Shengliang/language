package main

import "fmt"

type Vertex struct {
	X int
	Y int
}

func main() {
	v := Vertex{1, 2}
	p := &v
	// In C language, the following line should be p->X = 8;
	p.X = 8
	fmt.Println(v)
}
