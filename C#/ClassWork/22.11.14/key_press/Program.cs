using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace key_press
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                ConsoleKeyInfo k = Console.ReadKey(true);
                Console.WriteLine(k.Key);
                if (k.Key == ConsoleKey.A) Console.Write("A");               
            }
        }
    }
}
