using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorld
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hellow World!");
            Console.WriteLine(args[1]);
            Console.WriteLine(args[0]);

            int age = 30;
            string name = "Alik";

            Console.WriteLine("Привет, мое имя " + name + ". Мой возраст " + age + " лет!");
        }

    }
}
