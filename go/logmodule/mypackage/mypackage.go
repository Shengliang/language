

package mypackage

// Importing fmt package for the sake of printing
import (
    "fmt"
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
// Animal is the name we want but since we are
// to use it as an interface, we will change
// the name into Animaler.
type Animaler interface {

	// Note that we will
	// declare the methods to be used
	// later here in this
	// interface
	Eat()
	Move()
	Speak()
	Error()
	Log() logr.Logger
}

// A struct holding a string variable: SuperAnimals
type SuperAnimals struct {
	locomotion string
}

// An embedded struct holding content
// from another struct and two
// other string variables
// named Animals
type Animals struct {
    SuperAnimals
    food string
    sound string
    log logr.Logger
}

func (x Animals) Log() logr.Logger {
     return x.log
}

// Now we are indirectly implementing
// the Animaler interface without any
// keywords.
// We are about to define each method
// declared in the Animaler interface.
func (x Animals) Eat() {
	// this method will access the variable
	// food in Animal class
	fmt.Println(x.food)
}

func (x Animals) Move() {
	// this method will access the variable
	// locomotion in Animal class
	fmt.Println(x.locomotion)
}

func (x Animals) Speak() {
	// this method will access the variable
	// sound in Animal class
	fmt.Println(x.sound)
}

func (x Animals) Error() {
	fmt.Println("Invalid query entered!")
}

func Foo() {
    ctx := context.Background()
    zl := zerolog.New(os.Stderr).Level(zerolog.DebugLevel)
    logger := zerologr.New(&zl);
    ctx = logr.NewContext(ctx, logger.WithName("helper").WithValues("key1", "value1"))
    helper(ctx)

    m := map[string]Animaler{ "cow": 
         Animals{
                  SuperAnimals: SuperAnimals{
                     locomotion: "walk",
                  },
                  food: "grass",
                  sound: "moo",
                  log: logr.FromContextOrDiscard(ctx),
         },
    }
    var animal string
    animal = "cow"
    m[animal].Eat()
    m[animal].Move()
    m[animal].Speak()
    m[animal].Log().Info("start", "x", 42)
}

