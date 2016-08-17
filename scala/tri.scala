object Solution {
  var m = Array.tabulate[Char](32, 63) { (i,j) => '_' }
  def pr() {
     for(i <- 0 to 31 ) {
         for(j <- 0 to 62) {
             print(m(i)(j))
         }
         println()
     }
     println()
  }

  def init1(r: Int,  c : Int,  d:Int, v:Char) {
     for(i <- (r+0) to (r+d) ) {
         for(j <- 0 to i) {
             m(i)(c-j) = v 
             m(i)(c+j) = v 
         }
     }
  }

  def init_(r: Int,  c : Int,  d:Int, v:Char, l:Int) {
     var di:Int = 0
     for(i <- r to (r-d) by -1 ) {
         for(j <- 0 to di) {
             m(i)(c-j) = v 
             m(i)(c+j) = v 
         }
         di=di+1
     }
     //init_(31,31,15,'_');
     //init_(31,31-16,7,'_'); 
     //init_(31,31+16,7,'_');
     //init_(15,31,7,'_');

     if ((d/2 >= 0) && (l>0)) {
       init_(r,c-d-1,d/2,'_', l-1); 
       init_(r,c+d+1,d/2,'_', l-1);
       init_(r-d-1,c,d/2,'_', l-1);
     }
  }

  def drawTriangles(n: Int) {
    //Draw the N'th iteration of the fractal as described 
    // in the problem statement
    init1(0,31,31,'1');
    if (n>0) {
       init_(31,31,15,'_', n-1);
    }
    pr();
  }

  def main(args: Array[String]) {
    drawTriangles(readInt())
  }
}

