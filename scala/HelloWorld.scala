/** Hello World */
object HelloWorld {
  def foo() : Int = {
    var N: Int = 0
    var i: Int = 0
    print("Enter: N = ")
    N = scala.io.StdIn.readInt
    var A:Map[Int,Int] = Map()
    for (i <- 1 to N) {
        var a: Int = 0
        var b: Int = 0
        var B: Int = 0
        print("Enter: x := ")
        a = scala.io.StdIn.readInt
        print("Enter: y := ")
        b = scala.io.StdIn.readInt
        var r = A.get(a)
        if (r != None ) {
           B = r.get
           if (B != b) {
             println("NO");
             return 0;
           }
        } else {
           A += (a -> b)
        }
    }
    println("YES");
    return 1;
  }
  def bar() = {
    var T: Int = 0
    var i: Int = 0
    print("Enter a Int: T := ")
    T = scala.io.StdIn.readInt
    for (a <- 1 to T) {
        foo();
    }
  }
  def main(args: Array[String]): Unit = {
    for (a <- 2 to 2) {
       println("Hello, world!")
    }
    var arr = new Array[Int](2);
    for (i <- 0 to arr.size-1) {
        arr(i) = 7
    }
    arr.foreach(println)
    arr(0) = 0
    arr(1) = 1
    arr.foreach(println)

    var m = Array.ofDim[ Array[Int] ](2)
    m(0) = Array.ofDim[Int](7)
    m(1) = Array.ofDim[Int](7)
    for(r <- 0 to 1) {
       for(c <- 0 to 6) {
           m(r)(c) = r*7+c;
       }
    }
    for(r <- 0 to 1) {
       for(c <- 0 to 6) {
           print(" " + m(r)(c))
       }
       println()
    }
    println()

    var matrix = Array.tabulate[Int](2,7) { (i,j) => i*7 +j }
    for(r <- 0 to 1) {
       for(c <- 0 to 6) {
           print(" " + matrix(r)(c))
       }
       println()
    }
    println()
    bar();
  }
}
