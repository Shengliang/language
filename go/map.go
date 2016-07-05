package main

import "fmt"
import "reflect"

func main() {

	persons := make(map[string]int)
	persons["Alice"] = 26
	persons["Bob"] = 25
	fmt.Println(len(persons))

	fmt.Println(reflect.ValueOf(persons).MapKeys())

	names := make([]string, 0, len(persons))
	for k := range persons {
		names = append(names, k)
	}
	fmt.Println(names)
}
