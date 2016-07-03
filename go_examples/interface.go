package main

import "fmt"
import "math"

func main() {
	rect := Rectangle{20, 50}
	circ := Circle{1}
	printArea(rect)
	printArea(circ)
}

type Shape interface {
	area() float64
	toString() string
}
type Rectangle struct {
	height float64
	width  float64
}
type Circle struct {
	radius float64
}

func (r Rectangle) area() float64 {
	return r.height * r.width
}

func (c Circle) area() float64 {
	return math.Pi * math.Pow(c.radius, 2)
}

func (r Rectangle) toString() string {
	return "Rectangle"
}
func (c Circle) toString() string {
	return "Circle"
}

func printArea(s Shape) {
	a := s.area()
	n := s.toString()
	fmt.Println(n, s, a)
}
