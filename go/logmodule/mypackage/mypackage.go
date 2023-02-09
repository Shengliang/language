

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
    cnt int
}

func (x *Animals) Log() logr.Logger {
	x.cnt+=1
     return x.log.WithName(x.locomotion).WithValues("food", x.food).WithValues("sound", x.sound).WithValues("cnt", x.cnt)
}

// Now we are indirectly implementing
// the Animaler interface without any
// keywords.
// We are about to define each method
// declared in the Animaler interface.
func (x *Animals) Eat() {
	// this method will access the variable
	// food in Animal class
	fmt.Println(x.food)
}

func (x *Animals) Move() {
	// this method will access the variable
	// locomotion in Animal class
	fmt.Println(x.locomotion)
}

func (x *Animals) Speak() {
	// this method will access the variable
	// sound in Animal class
	fmt.Println(x.sound)
}

func (x *Animals) Error() {
	fmt.Println("Invalid query entered!")
}

func Foo() {
    ctx := context.Background()
    zl := zerolog.New(os.Stderr).Level(zerolog.DebugLevel)
    logger := zerologr.New(&zl);
    ctx = logr.NewContext(ctx, logger.WithName("helper").WithValues("pkg", "mypackage"))
    helper(ctx)

    m := map[string]Animaler{
	    "cow":
         &Animals{
                  SuperAnimals: SuperAnimals{
                     locomotion: "walk",
                  },
                  food: "grass",
                  sound: "moo",
                  log: logr.FromContextOrDiscard(ctx),
         },
	    "brid":
         &Animals{
                  SuperAnimals: SuperAnimals{
                     locomotion: "fly",
                  },
                  food: "worms",
                  sound: "peep",
                  log: logr.FromContextOrDiscard(ctx),
         },
	    "snake":
         &Animals{
                  SuperAnimals: SuperAnimals{
                     locomotion: "slither",
                  },
                  food: "mice",
                  sound: "hsss",
                  log: logr.FromContextOrDiscard(ctx),
         },
    }
    var animal string
    animal = "cow"
    m[animal].Eat()
    m[animal].Move()
    m[animal].Speak()
    m[animal].Log().V(1).Info("msg", "x", 41)
    m[animal].Log().V(1).Info("msg", "y", 107)
    m[animal].Log().V(1).Info("msg", "z", 314)
    animal = "brid"
    m[animal].Log().V(0).Info("msg", "x", 42)
    animal = "snake"
    m[animal].Log().Info("msg", "x", 43)
}

