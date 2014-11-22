using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace runing_string
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                if (Console.KeyAvailable == true)
                {
                    ConsoleKeyInfo k = Console.ReadKey(true);
                    Console.Write(k.KeyChar);
                }
                else
                {
                    Console.Write("_");
                }
                Thread.Sleep(15);
            }

        }
    }
}
