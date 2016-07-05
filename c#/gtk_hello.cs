// mcs gtk_hello.cs -pkg:gtk-sharp-2.0
// mono gtk_hello.exe
using Gtk;
using System;

class Hello
{
    static void Main ()
    {
        Application.Init ();

        Window window = new Window ("Hello Mono World");
        window.Show ();

        Application.Run ();
    }
}
