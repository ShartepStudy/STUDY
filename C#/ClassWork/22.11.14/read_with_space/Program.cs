using System;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            string str = "";
            while (true)
            {
                ConsoleKeyInfo k = Console.ReadKey();
                if (k.Key == ConsoleKey.Enter)
                {
                    Console.WriteLine();
                    break;
                }
                str += k.KeyChar;
            }
            Console.WriteLine(str);
        }
    }
}
