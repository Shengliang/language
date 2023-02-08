
package main

import (
	"os"

	"github.com/go-logr/zerologr"
	"github.com/rs/zerolog"
)

func main() {
	zl := zerolog.New(os.Stderr).Level(zerolog.DebugLevel)
	logger := zerologr.New(&zl).WithName("somename").WithValues("key1", "val1")
	logger.Info("hello")
	
	// Output:
	// {"key1":"val1","v":0,"logger":"somename","message":"hello"}
}
