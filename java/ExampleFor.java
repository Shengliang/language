import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.util.Scanner;
import java.net.URLDecoder;

public class ExampleFor {

    public static void main(String[] args) {
 
            Scanner sc=new Scanner(System.in);
	    try {
		    String path =  ExampleFor.class.getProtectionDomain().getCodeSource().getLocation().getPath();
		    String decodedPath = URLDecoder.decode(path, "UTF-8");
		    // String className = this.getClass().getSimpleName(); 
		    String className = new Object(){}.getClass().getEnclosingClass().getName();
	            // int n=sc.nextInt();
		    int n = 1;
	            for(int j=0; j<n; j++) {
	                  System.out.printf(decodedPath + className);
	            }
	            System.out.printf("\n");
		    throw new UnsupportedEncodingException("ME");

	    } catch (UnsupportedEncodingException e) {
	    	System.out.printf("Failed to decode:" + e.getMessage(), e);
	        e.printStackTrace();
	    }
	    finally {
		System.out.printf("Finally!\n");
            }
    }
}
