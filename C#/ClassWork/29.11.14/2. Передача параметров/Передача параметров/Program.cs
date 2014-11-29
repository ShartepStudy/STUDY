using System;

namespace Classes
{
    class Program
    {
        static void Main()
        {
            // Передача значимого и ссылочного типа по значению без пересоздания ссылочной 
            // переменной.

            int number = 0;
            int[] ar = {0, 1, 2, 4};

            Console.WriteLine("Inside Main before calling MethodByValue1");
            Print(ar, number);

            MethodByValue1(ar, number);

            Console.WriteLine("Inside Main after calling MethodByValue1");
            Print(ar, number);

            // Передача значимого и ссылочного типа по значению с пересозданием ссылочной 
            // переменной.
            
            number = 10;
            ar = new int[]{1, 2, 3};

            Console.WriteLine("\n\nInside Main before calling MethodByValue2");
            Print(ar, number);

            MethodByValue2(ar, number);

            Console.WriteLine("Inside Main after calling MethodByValue2");
            Print(ar, number);

            // Передача значимого и ссылочного типа по ссылке.

            number = 10;
            ar = new int[]{1, 2, 3};

            Console.WriteLine("\n\nInside Main before calling MethodByReference");
            Print(ar, number);

            MethodByReference(ref ar, ref number);

            Console.WriteLine("Inside Main after calling MethodByReference");
            Print(ar, number);
        }

        static void MethodByValue1(int[] ar, int number)
        {
            ar[0] = 100;
            number = 100;
        }

        private static void MethodByValue2(int[] ar, int number)
        {
            Console.WriteLine("Inside MethodByValue2 before changing"); 
            Print(ar, number);

            number = 100;
            ar = new int[] {3, 2, 1};

            Console.WriteLine("Inside MethodByValue2 after changing"); 
            Print(ar, number);
        }

        private static void MethodByReference(ref int[] ar, ref int number)
        {
            Console.WriteLine("Inside MethodByReference before changing"); 
            Print(ar, number);

            number = 100;
            ar = new int[] {3, 2, 1};

            Console.WriteLine("Inside MethodByReference after changing"); 
            Print(ar, number);
        }

        private static void Print(int[] ar, int number)
        {
            Console.WriteLine("number = {0}", number);

            Console.Write("ar { ");

            foreach (int element in ar)
            {
      	        Console.Write(element + " ");
            }

            Console.WriteLine("}");
        }
    }
}