using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace array_one_size
{
    class Program
    {
        static void Main(string[] args)
        {
            // Создание массива из 10 элементов типа int все элементы массива инициализируются 
            // нулями.
            int[] intArray1 = new int[10];

            for (int i = 0; i < intArray1.Length; i++)
            {
                Console.Write("{0,4}", intArray1[i]);
            }

            Console.WriteLine();

            // Создание и инициализация.
            int[] intArray2 = new int[] { 1, 2, 3, 4 };

            for (int i = 0; i < intArray2.Length; i++)
            {
                Console.Write("{0,4}", intArray2[i]);
            }

            Console.WriteLine();

            // Создание и инициализация (укороченный вариант).
            int[] intArray3 = { 0, 3, 7, 17, 25 };

            // Можно объявить массив без инициализации.
            int[] intArray4;

            // Но его нельзя использовать, пока он не создан с помощью оператора new.

            // Ошибка компиляции.
            //intArray4[0] = 0;

            // Ошибка компиляции.
            //intArray4 = {0, 3, 7, 17, 25};

            intArray4 = new int[] { 0, 3, 7, 17, 25 };
            intArray4[0] = 10;

            for (int i = 0; i < intArray4.Length; i++)
            {
                Console.Write("{0,4}", intArray4[i]);
            }

            Console.WriteLine();

            // Создание массива из 10 элементов типа string все элементы массива инициализируются 
            // null, т. к. string - ссылочный тип.
            string[] stringArray1 = new string[10];
            string[] stringArray2 = new string[7]
            {
                "Sunday", 
                "Monday", 
                "Tuesday", 
                "Wednesday", 
                "Thursday", 
                "Friday", 
                "Saturday"
            };

            for (int i = 0; i < stringArray2.Length; i++)
            {
                Console.WriteLine(stringArray2[i]);
            }

            foreach (var cur in stringArray2)
            {
                Console.WriteLine(cur);                
            }





            Random random = new Random();

            Console.WriteLine("Source array of integers: ");

            int[] ar = new int[10];
            for (int i = 0; i < ar.Length; i++)
            {
                ar[i] = random.Next(-20, 20);
                Console.Write("{0,4}", ar[i]);
            }
            Console.WriteLine();

            int number = 0;
            int position = 0;

            Console.WriteLine("Enter an integer to search: ");
            number = Convert.ToInt32(Console.ReadLine());

            // Поиск первого вхождения числа в массив.
            position = Array.IndexOf(ar, number);

            if (position >= 0)
            {
                Console.WriteLine("First appearing at " + position + " position");
            }
            else
            {
                Console.WriteLine("No matches found");
            }
            Console.WriteLine();

            Console.WriteLine("Enter an integer to search: ");
            number = Convert.ToInt32(Console.ReadLine());

            // Поиск последнего вхождения числа в массив.
            position = Array.LastIndexOf(ar, number);

            if (position >= 0)
            {
                Console.WriteLine("Last appearing at " + position + " position");
            }
            else
            {
                Console.WriteLine("No matches found");
            }
            Console.WriteLine();

            Console.WriteLine("Array sorted in ascending order: ");

            // Сортировка по возрастанию.
            Array.Sort(ar);
            
            for (int i = 0; i < ar.Length; i++)
            {
                Console.Write("{0,4}", ar[i]);
            }
            Console.WriteLine("\n");

            Console.WriteLine("Array sorted in descending order: ");

            // Сортировка по убыванию.
            Array.Reverse(ar);

            foreach (int element in ar)
            {
                // Переменная element доступна только для чтения.
                Console.Write("{0,4}", element);
            }
            Console.WriteLine("\n");

            Console.WriteLine("Source array of floating-point numbers: ");

            double[] doubleArrar1 = new double[10];
            for (int i = 0; i < doubleArrar1.Length; i++)
            {
                doubleArrar1[i] = random.NextDouble() * 100;
                Console.Write("{0:F3}\t", doubleArrar1[i]);
            }
            Console.WriteLine("\n");

            Console.WriteLine("Copied array of floating-point numbers: ");

            double[] doubleArray2 = new double[10];
            Array.Copy(doubleArrar1, doubleArray2, doubleArrar1.Length);

            foreach (double element in doubleArray2)
            {
                // Переменная element доступна только для чтения.
                Console.Write("{0:F3}\t", element);
            }
            Console.WriteLine("\n");

            // Обнуление массива.
            Array.Clear(doubleArrar1, 0, doubleArrar1.Length);

            foreach (double element in doubleArrar1)
            {
                // Переменная element доступна только для чтения.
                Console.Write("{0,4}", element);
            }
            Console.WriteLine();

        }
    }
}
