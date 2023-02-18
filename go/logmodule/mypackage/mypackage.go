

// Ref: https://gobyexample.com/waitgroups

package mypackage

import (
    "fmt"
    "unsafe"
    "time"
    "runtime"
    "runtime/debug"
    "sync"
    "sync/atomic"
    "context"
    "strconv"
    "os"
    "path/filepath"
    "github.com/go-logr/logr"
    "github.com/go-logr/zerologr"
    "github.com/rs/zerolog"
)

type logrContextKey struct{}

func LogrFromContext(ctx context.Context) (*logr.Logger) {
    if myLog, ok := ctx.Value(logrContextKey{}).(*logr.Logger); ok {
	    return myLog
    }
    return nil
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
	Run(int)
	Schedule()
}

// A struct holding a string variable: SuperAnimals
type SuperAnimals struct {
	m_ctx context.Context
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
    log *logr.Logger
    messages chan int
    cnt uint64
    run_cnt uint64
}

func (x *Animals) Log() logr.Logger {
     cnt := atomic.AddUint64(&x.cnt, 1)
      _, filename, line, _ := runtime.Caller(1)
     return x.log.WithName(filepath.Base(filename)).WithName(strconv.Itoa(line)).WithName(x.locomotion).WithValues("food", x.food).WithValues("sound", x.sound).WithValues("cnt", cnt)
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


/*
func (x * Animals) goid() int {
	var buf [64]byte
	n := runtime.Stack(buf[:], false)
	idField := strings.Fields(strings.TrimPrefix(string(buf[:n]), "goroutine "))[0]
	id, err := strconv.Atoi(idField)
	if err != nil {
		panic(fmt.Sprintf("cannot get goroutine id: %v", err))
	}
	return id
}
*/

func (x *Animals) Run(id int) {
  
   var Log logr.Logger = x.Log().WithName("Run").WithValues("RUN_CNT", atomic.LoadUint64(&x.run_cnt)).WithValues("BEGIN_TIME", time.Now())
   Log.Info("Enter")
   run_cnt_id := atomic.AddUint64(&x.run_cnt, 1)
   for w := 0; w < 2; w++ {
	Log = Log.WithValues("run_cnt_id", strconv.FormatUint(run_cnt_id, 10)).WithValues("logr", fmt.Sprintf("%p", &Log)).WithValues("ID", id).WithValues("w", w);
        time.Sleep(100 * time.Millisecond)
    }
    x.messages <- id
    Log.WithValues("END_TIME", time.Now()).Info("Exit");
}
func (x *Animals) Schedule() {
        //var Log logr.Logger = logr.FromContextOrDiscard(x.m_ctx).WithName("Schedule")
        var Log logr.Logger = x.Log().WithName("Schedule")
	var wg sync.WaitGroup
	Log.Info("Enter", "BeginTime", time.Now())
	defer func() {
		Log.Info("Exit", "EndTime", time.Now())
	}()
	for id := 0; id < 5; id++ {
            wg.Add(1)
	    go func(id int) {
		 defer wg.Done()
		 x.Run(id)
	    }(id)
	}

	//time.Sleep(1*time.Second);
        go func(){
          Log.Info("wait...")
	  for id := range x.messages {
             Log.Info("got", "id", id)
          }
        }()

	wg.Wait()

}

func Foo() {
    ctx := context.Background()
    zl := zerolog.New(os.Stderr).Level(zerolog.DebugLevel)
    logger := zerologr.New(&zl);
    myLogObj := logger.WithValues("pkg", "mypackage")
    ctx = context.WithValue(ctx, logrContextKey{}, &myLogObj)
    myLog:= func() (log logr.Logger) {
      _, filename, line, _ := runtime.Caller(1)
      log = LogrFromContext(ctx).WithName(filepath.Base(filename)).WithName(strconv.Itoa(line))
      return log
    }

    debug.PrintStack()
    myLog().Info("log size info", "ctx size:", unsafe.Sizeof(ctx), "logger size", unsafe.Sizeof(myLogObj), "&logger size", unsafe.Sizeof(&myLogObj))

    m := map[string]Animaler{
	    "cow":
         &Animals{
                  SuperAnimals: SuperAnimals{
                     m_ctx : ctx,
                     locomotion: "walk",
                  },
                  food: "grass",
                  sound: "moo",
                  log: LogrFromContext(ctx),
		  messages: make(chan int),
         },
	    "brid":
         &Animals{
                  SuperAnimals: SuperAnimals{
                     m_ctx : ctx,
                     locomotion: "fly",
                  },
                  food: "worms",
                  sound: "peep",
                  log: LogrFromContext(ctx),
		  messages: make(chan int),
         },
	    "snake":
         &Animals{
                  SuperAnimals: SuperAnimals{
                     m_ctx : ctx,
                     locomotion: "slither",
                  },
                  food: "mice",
                  sound: "hsss",
                  log: LogrFromContext(ctx),
		  messages: make(chan int),
         },
    }
    var animal string
    animal = "cow"
    m[animal].Eat()
    m[animal].Move()
    m[animal].Speak()
    m[animal].Log().V(1).WithName("X").Info("msg", "x", 141)
    m[animal].Log().V(1).WithName("Y").Info("msg", "y", 107)
    m[animal].Log().V(1).WithName("Z").Info("msg", "z", 314)
    animal = "brid"
    m[animal].Log().V(0).Info("msg", "x", 42)
    animal = "snake"
    m[animal].Log().Info("msg", "x", 43)
    m[animal].Schedule()

}

