using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("1. Статистика по строке (кол-во букв, кол-во пробелов и т.п.)");
        Console.Write("Введите строку: ");
        string str = Console.ReadLine();
        StringInfo(str);

        Console.WriteLine("2. Поиск символа в строке");
        Console.Write("Введите символ для поиска: ");
        char c = Convert.ToChar(Console.ReadLine());

        str = str.Replace(char.ToLower(c), char.ToUpper(c));
        int lastIndex = str.LastIndexOf(char.ToUpper(c));
        str = str.Remove(lastIndex, str.Length - lastIndex);
        Console.WriteLine(str);
    }


    static void StringInfo(string s)
    {
        int signs = 0, lettersU = 0, lettersL = 0, digits = 0, spaces = 0;
        for (int i = 0; i < s.Length; i++)
        {
            if (char.IsDigit(s[i]))
                digits++;
            else if (s[i] == '?' || s[i] == '!' || s[i] == ',' || s[i] == '.' || s[i] == ';' || s[i] == ':' || s[i] == '-' || s[i] == '\'' || s[i] == '\"')
                signs++;
            else if (char.IsWhiteSpace(s[i]))
                spaces++;
            else if (char.IsLower(s[i]))
                lettersL++;
            else if (char.IsUpper(s[i]))
                lettersU++;
        }
        Console.WriteLine("\nОбщее кол-во символов: " + s.Length);
        Console.WriteLine("Букв в верхнем регистре: " + lettersU);
        Console.WriteLine("Букв в нижнем регистре: " + lettersL);
        Console.WriteLine("Пробелов: " + spaces);
        Console.WriteLine("Цифр: " + digits);
        Console.WriteLine("Знаков: " + signs + "\n");
    }
}