package main

import (
	"fmt"
	"sort"
)

type Person struct {
	name string
	age  int
}

func (p Person) String() string {
	return fmt.Sprintf("%s: %d", p.name, p.age)
}

type MySort []Person

func (a MySort) Len() int      { return len(a) }
func (a MySort) Swap(i, j int) { a[i], a[j] = a[j], a[i] }
func (a MySort) Less(i, j int) bool {
	if a[i].age == a[j].age {
		return a[i].name < a[j].name
	} else {
		return a[i].age < a[j].age
	}
}

func main() {
	people := []Person{
		{"Bob", 31},
		{"John", 42},
		{"Michael", 17},
		{"Jenny", 31},
	}
	fmt.Println(people)
	sort.Sort(MySort(people))
	fmt.Println(people)
}
