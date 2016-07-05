/*
 * Given a 2D matrix
 * abc
 * def
 * ghi
 * 123
 * 
 * Print each element in diagonal direction.
 * a
 * db
 * gec
 * 1hf
 * 2i
 * 3
 */
package main

import (
	"fmt"
)

type Matrix [][]byte

func print(m Matrix) {
	R := len(m)
	C := len(m[0])
	fmt.Println("R:", R, "C:", C)
	for r := 0; r < R; r++ {
		for c := 0; c < C; c++ {
			fmt.Printf("%c", m[r][c])
		}
                fmt.Printf("\n")
	}
        fmt.Printf("\n")
}

func diag_print(m Matrix) {
	R := len(m)
	C := len(m[0])
	fmt.Println("R:", R, "C:", C)
        // print from 0,0 to R-1,C-1
	r, c := 0, 0
	for {
		fmt.Printf("%c", m[r][c])
                // quit if it is the last element 
		if r == (R-1) && c == (C-1) {
			fmt.Println("\n")
			return
		}
                // walk diag direction
		r = r - 1
		c = c + 1
                // wrap around
		if r == -1 || c == C {
			fmt.Printf("\n")
			r = c + r + 1
			c = 0
			if r >= R {
				c = r - R + 1
				r = R - 1
			}
		}
	}
}

func main() {
	m := Matrix{
		[]byte("abc"),
		[]byte("def"),
		[]byte("ghi"),
		[]byte("123"),
	}
	print(m)
	diag_print(m)
}
