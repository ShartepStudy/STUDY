using System;

namespace Properties
{

    static class Input
    {
        static int number;

        public static int Number()
        {
            while (true)
            {
                try
                {
                    number = Convert.ToInt32(Console.ReadLine());
                }
                catch (System.FormatException)
                {
                    Console.WriteLine("Нужно было ввести число, а не строку!");
                    continue;
                }
                catch (System.OverflowException)
                {
                    Console.WriteLine("Слишком больше число!");
                    continue;
                }
                break;
            }
            return number;
        }
    }

    class Program
    {
        static void Main()
        {
            int x = Input.Number();
        }
    }
}