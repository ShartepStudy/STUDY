using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class_vs_struct
{
    class Program
    {
        class Point
        {
            public int x;
            public int y;
        }

        static void Main(string[] args)
        {
            Point p = new Point();  // создание объекта структуры в стеке
            //p.x = 5;
            //p.y = 7;
            Console.WriteLine(p.x);
            Console.WriteLine(p.y);
        }
    }
}
