// Compile:
// $ javac Animal.java MammalInt.java 
// Run:
// $ java MammalInt 
// Output:
// Mammal eats
// Mammal travels

public class MammalInt implements Animal{

   public void eat(){
      System.out.println("Mammal eats");
   }

   public void travel(){
      System.out.println("Mammal travels");
   } 

   public int noOfLegs(){
      return 0;
   }

   public static void main(String args[]){
      MammalInt m = new MammalInt();
      m.eat();
      m.travel();
   }
} 
