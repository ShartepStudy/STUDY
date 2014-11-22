using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace modifiers
{
    class Program
    {
        static void Main(string[] args)
        {
            ConsoleKeyInfo cki;
            cki = Console.ReadKey(true);
            if (cki.Modifiers != 0)
            {
                if ((cki.Modifiers & ConsoleModifiers.Alt) != 0)
                    Console.Write("ALT+");
                if ((cki.Modifiers & ConsoleModifiers.Shift) != 0)
                    Console.Write("SHIFT+");
                if ((cki.Modifiers & ConsoleModifiers.Control) != 0)
                    Console.Write("CTL+");
            }
            Console.WriteLine(cki.Key.ToString());
        }
    }
}
