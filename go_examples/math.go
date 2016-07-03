package main

import "fmt"
import "math"

func add(x int, y int) int {
	return x + y
}

func swap(x, y string) (string, string) {
	return y, x
}

func getsum(a, b int) int {
	sum := 0
	for i := a; i < b; i++ {
		sum += i
	}
	return sum
}

func Sqrt(x float64) float64 {
	var delta, z, zn float64
	zn = 1.0
	delta = 0.0001
	for {
		z = zn
		zn = z - (z*z-x)/(2*z)
		if math.Abs(zn-z) < delta {
			mz := math.Sqrt(x)
			fmt.Printf("%g %g %g\n", mz, z, z-mz)
			return z
		}
	}
}

func diag(x int, y int) float64 {
	var zz float64
	zz = float64(x*x + y*y)
	return Sqrt(zz)
}

func main() {
	var x int
	var y int
	x = 3
	y = 5
	fmt.Printf("hello world\n")
	a, b := swap("hello", "world")
	fmt.Println(a, b)
	sum := add(x, y)
	d := diag(x, y)
	fmt.Printf("%d + %d = %d %T\n", x, y, sum, sum)
	fmt.Printf("%d^2 + %d^2 = %.2g^2 %T\n", x, y, d, d)
	x = 1
	y = 10
	fmt.Printf("%d + ... + %d = %d\n", x, y, getsum(x, y))
}
