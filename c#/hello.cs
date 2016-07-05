// mcs hello.cs
// mono hello.exe
using System;
 
public class HelloWorld
{
    static public void Main (string[] args)
    {

        Console.WriteLine ("Hello Mono World");

        Console.WriteLine("Number of command line parameters = {0}",
          args.Length);
         for(int i = 0; i < args.Length; i++)
         {
           Console.WriteLine("Arg[{0}] = [{1}]", i, args[i]);
         }
    }
}
