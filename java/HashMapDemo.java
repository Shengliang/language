// javac -Xlint HashMapDemo.java
// $ java HashMapDemo 
// 
// Original Ref: http://www.tutorialspoint.com/java/java_hashmap_class.htm
// Modified based on
// http://stackoverflow.com/questions/46898/how-to-efficiently-iterate-over-each-entry-in-a-map

import java.util.*;

public class HashMapDemo {

   public static void main(String args[]) {
   
      // Create a hash map
      HashMap<String, Double> hm = new HashMap<String, Double>();
      // Put elements to the map
      hm.put("Zara", new Double(3434.34));
      hm.put("Mahnaz", new Double(123.22));
      hm.put("Ayan", new Double(1378.00));
      hm.put("Daisy", new Double(99.22));
      hm.put("Qadir", new Double(-19.08));
      
      // Get a set of the entries
      Set<HashMap.Entry<String,Double>> set = hm.entrySet();
      // Get an iterator
      Iterator<HashMap.Entry<String,Double>> i = set.iterator();
      // Display elements
      while(i.hasNext()) {
         HashMap.Entry<String,Double> me = i.next();
         System.out.print(me.getKey() + ": ");
         System.out.println(me.getValue());
      }

      // Java 1.5+ syntax
      for( HashMap.Entry<String,Double> me : hm.entrySet()) {
         System.out.print(me.getKey() + ": ");
         System.out.println(me.getValue());
      }

      System.out.println();
      // Deposit 1000 into Zara's account
      double balance = hm.get("Zara").doubleValue();
      hm.put("Zara", new Double(balance + 1000));
      System.out.println("Zara's new balance: " +
      hm.get("Zara"));
   }
}
