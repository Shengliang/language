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

// By is the type of a "less" function
type By func(p1, p2 *Person) bool
type personSorter struct {
	persons []Person
	by      By
	//by func(p1, p2 *Person) bool
}

func (by By) Sort(persons []Person) {
	ps := &personSorter{
		persons: persons,
		by:      by,
	}
	sort.Sort(ps)
}

func (s *personSorter) Len() int {
	return len(s.persons)
}

func (s *personSorter) Swap(i, j int) {
	s.persons[i], s.persons[j] = s.persons[j], s.persons[i]
}

func (s *personSorter) Less(i, j int) bool {
	return s.by(&s.persons[i], &s.persons[j])
}

func main() {
	mysort := func(p1, p2 *Person) bool {
		if p1.age == p2.age {
			return p1.name < p2.name
		} else {
			return p1.age < p2.age
		}
	}
	people := []Person{
		{"Bob", 31},
		{"John", 42},
		{"Michael", 17},
		{"Jenny", 31},
	}
	fmt.Println(people)
	By(mysort).Sort(people)
	fmt.Println(people)
}
