// http://www.tutorialspoint.com/java/util/java_util_priorityqueue.htm
// package com.tutorialspoint;

import java.util.*;

public class PriorityQueueDemo {
   public static void main(String args[]) {
       // create priority queue
       PriorityQueue < Integer >  prq = new PriorityQueue < Integer > (); 
           
       // insert values in the queue
       for ( int i = 0; i  <  10; i++ ){  
           prq.add (new Integer (10-i)) ; 
       }
          
       System.out.println ( "Priority queue values are: " + prq);
       Object[] arr = prq.toArray();
       for (int i=0; i<arr.length; i++) {
          System.out.println("Value: " + arr[i].toString());
       }
          
       // check if queue contains 5
       boolean b = prq.contains(5);
          
       System.out.println ( "Priority queue contains 5: " + b);

       Integer head;
       while ((head = prq.poll())!=null) {
          System.out.println("head Value: " + head.toString());
       }
   }
}
