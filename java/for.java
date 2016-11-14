import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.util.Scanner;

public class Solution {

    public static void main(String[] args) {
 
            Scanner sc=new Scanner(System.in);
            int T=sc.nextInt();
            for(int i=0;i<T;i++){
                int a=sc.nextInt();
                int b=sc.nextInt();
                int n=sc.nextInt();
                for(int j=0; j<n; j++) {
                    a+=b*(1<<j);
                    System.out.printf("%d ", a);
                }
                System.out.printf("\n");
                
            }
    }
}



