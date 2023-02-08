package main

import (
	"fmt"
	"os"

//	"github.com/go-logr/logr"
	"github.com/go-logr/zerologr"
	"github.com/rs/zerolog"
)

func main() {
	zl := zerolog.New(os.Stderr).Level(zerolog.InfoLevel)
	logger := zerologr.New(&zl)

	logger.Info("info from logr") // Logs to level 0 by default
	logger.Info("This is the message", "field1", 123, "field2", false)

	// Error logs are always visible
	logger.Error(fmt.Errorf("new error"), "error from logr")

	logger.V(0).Info("level 0") // Visible on InfoLevel
	logger.V(1).Info("level 1") // Visible on DebugLevel
	logger.V(2).Info("level 2") // Visible on TraceLevel
	logger.V(3).Info("level 3") // With zerolog never visible
	
	// Output:
	// {"v":0,"message":"info from logr"}
	// {"error":"new error","message":"error from logr"}
	// {"v":0,"message":"level 0"}
}
