package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os"
)

func main() {

	filename := "sample.txt"
	fmt.Println("Create file " + filename)
	file, err := os.Create(filename)
	if err != nil {
		log.Fatal(err)
	}
	file.WriteString("This is Sheng-Laing Song.")
	file.Close()

	fmt.Println("Read file " + filename)
	stream, err := ioutil.ReadFile(filename)
	if err != nil {
		log.Fatal(err)
	}
	readString := string(stream)
	fmt.Println(readString)
}
