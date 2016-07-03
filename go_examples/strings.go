package main

import (
	"fmt"
	"sort"
	"strings"
)

func main() {

	str := "hello World"
	fmt.Println(strings.Contains(str, "lo"))
	fmt.Println(strings.Index(str, "lo"))
	fmt.Println(strings.Count(str, "l"))
	fmt.Println(strings.Replace(str, "l", "x", 3))

	words := strings.Split(str, " ")
	sort.Strings(words)
	fmt.Println("Words:", words)

	listOfNums := strings.Join([]string{"3", "2", "1"}, ",")
	fmt.Println(listOfNums)
}
