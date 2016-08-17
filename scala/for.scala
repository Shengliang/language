/** Hello World */
import Math.pow
import Math.PI

object HelloWorld {
  def main(args: Array[String]): Unit = {
    println("Hello, world!"+ Math.PI);
    var i : Int  = 0;
    for (i <- 0 until args.size) {
       println((i, args(i)));
       println((i, Math.pow(i, 2)));
    } 
    args.foreach(arg => println(arg))
    args.foreach(println(_))
    args.foreach(println)
  }
}
