package main

import (
	"context"
	"os"

	"github.com/go-logr/logr"
	"github.com/go-logr/zerologr"
	"github.com/rs/zerolog"
)

func helper(ctx context.Context) {
	logger := logr.FromContextOrDiscard(ctx)
	logger.Info("hello from helper")
}
func main() {
	ctx := context.Background()
	zl := zerolog.New(os.Stderr).Level(zerolog.DebugLevel)
	logger := zerologr.New(&zl)
	ctx = logr.NewContext(ctx, logger.WithName("helper"))
	helper(ctx)
}
