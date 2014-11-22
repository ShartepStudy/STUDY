using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace basic_types
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Некоторое простое сообщение\nИ ещё одно простое сообщение на новой строке");
            /*выводит в консоль следующее сообщение:
             "Некоторое простое сообщение
             И ещё одно простое сообщение на новой строке"*/
            Console.WriteLine("Пример табуляции:\n1\t2\t3\n4\t5\t6");
            /*выводит в консоль следующее сообщение:
             "Пример табуляции:
             1  2   3
             4  5   6"*/
            Console.WriteLine(@"Пример буквального строкового литерала:
            1       \t     3
                \n   5       6");
            /*выводит в консоль следующее сообщение:
             "Пример буквального строкового литерала:
                          1       \t     3
                               \n   5       6"*/



            /*при помощи метода GetType() программа возвращает тип данных литералов,
            демонстрируя действие суффиксов
            ----------------------------------------*/
            
            Console.WriteLine((10D).GetType());
            /*выводит в консоль: System.Double что соответствует типу данных double*/
            
            Console.WriteLine((10F).GetType());
            /*выводит в консоль: System.Single что соответствует типу данных float*/

            Console.WriteLine((10M).GetType());
            /*выводит в консоль: System.Decimal что соответствует типу данных decimal*/
            
            Console.WriteLine((10).GetType());
            /*выводит в консоль: System.Int32 что соответствует типу данных int*/

            Console.WriteLine((10L).GetType());
            /*выводит в консоль: System.Int64 что соответствует типу данных long*/

            Console.WriteLine((10UL).GetType());
            /*выводит в консоль: System.UInt64 что соответствует типу данных ulong*/
            
            Console.WriteLine(0xFF);
            /*выводит в консоль: 255 шестнадцатиричное число 0xFF соответствует десятичному числу 255*/


            byte a = 1;
            byte b = 2;
            byte c = (byte)(a + b);
            //decimal d = 3.14;


            String str = "hello :)";
            Object anotherString = str.Clone();
            Console.WriteLine(anotherString);

            // Выводит в консоль: "hello :)"
            Console.WriteLine(str.Contains("hello"));

            // Выводит в консоль: true
            Console.WriteLine(str.Insert(6, "world"));

            // Выводит в консоль: "hello world:)"
            Console.WriteLine(str.Remove(5, 1));

            // Выводит в консоль: "hello:)"
            Console.WriteLine(str.Replace(":)", ":("));

            // Выводит в консоль: "hello :("
            Console.WriteLine(str.StartsWith("hell"));

            // Выводит в консоль: "true"
            Console.WriteLine(str.Substring(6));

            // Выводит в консоль: ":)"
            Console.WriteLine(str.ToUpper());

            // Выводит в консоль: "HELLO :)"
            str = "       " + str + "       ";
            Console.WriteLine(str.TrimEnd());

            // Выводит в консоль: "       hello :)"
            str = "       " + str + "       ";
            str = str.Trim();

            // Выводит в консоль: "hello :)"
            Console.WriteLine(str);

            // Выводит в консоль: "The message is "hello :)" and some numeric value is 512"
            Console.WriteLine(String.Format(
                "The message is \"{0}\" and some numeric value is {1}",
                str,
                512
            ));



            string rev = new string(str.Reverse().ToArray());
        }
    }
}
