using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;



namespace ConsoleApplication1
{
    public class Win32Interop
    {
        [DllImport("crtdll.dll")]
        public static extern int _kbhit();
    }

    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                if (Win32Interop._kbhit() != 0)
                {
                    ConsoleKeyInfo k = Console.ReadKey(true);
                    Console.WriteLine(k.Key);
                    if (k.Key == ConsoleKey.A) Console.Write("A");
                }
                else
                {
                    Console.WriteLine("@");
                    Thread.Sleep(15);
                }
            }
        }
    }
}