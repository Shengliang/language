import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;


public class SolutionArray {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        int n = sc.nextInt();
        int len = A.length();
        String[] arr = new String[len-n+1];
        
        int c = 0;
        for(int i=0; i<(len-n+1); i++) {
            arr[i] = A.substring(i, i+n);
            System.out.printf("%s\n",  arr[i]);
        }
        Arrays.sort(arr);

        System.out.printf("%s\n%s\n", arr[0], arr[len-n]);

        
    }
}
