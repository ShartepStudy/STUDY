using System;

namespace Classes
{
    class Program
    {
        static void Main()
        {
            int a = 10;
            int b = 20;
            int c = 30;

            double da = 2.5;
            double db = 4.8;

            Console.WriteLine("{0} + {1} = {2}", a, b, Mathematic.Sum(a, b));
            Console.WriteLine("{0} + {1} + {2} = {3}", a, b, c, Mathematic.Sum(a, b, c));
            Console.WriteLine("{0} + {1} = {2}", da, db, Mathematic.Sum(da, db));
        }
    }
}
