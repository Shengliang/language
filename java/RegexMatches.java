import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexMatches
{
     public static void rm_dup_words(String input) {
         //String pattern = "\\b(\\w+)(\\b\\s+\\b\\1\\b)*";
         String pattern = "\\b(\\w+)(\\s+\\1)*";
         Pattern r = Pattern.compile(pattern, Pattern.CASE_INSENSITIVE);
         Matcher m = r.matcher(input);
         boolean findMatch = true;
         while(m.find( )){
             input = input.replaceAll(m.group(), m.group(1));
             findMatch = false;
         }
         System.out.println(input);
         return;
    }

    public static void main( String args[] ){

      // String to be scanned to find the pattern.
      String line = "This order was was was placed for QT3000! OK OK OK OK?";
      String pattern = "(.*?)(\\d+)(.*)";

      // Create a Pattern object
      Pattern r = Pattern.compile(pattern);

      // Now create matcher object.
      Matcher m = r.matcher(line);
      if (m.find( )) {
         System.out.println("Found value: " + m.group(0) );
         System.out.println("Found value: " + m.group(1) );
         System.out.println("Found value: " + m.group(2) );
      } else {
         System.out.println("NO MATCH");
      }
     rm_dup_words(line);
   }
}
