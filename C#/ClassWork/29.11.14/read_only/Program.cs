using System;
using System.Text;
using System.IO;

class Test
{
    public readonly int t = 10;
    public static int s = 10;
    public const int c = 25;
    public readonly int[] mass = { 1, 2, 3 };
    public Test()
    {
        t = 5;
        //c = 25;
    }
}

/*

Ключевое слов readonly отличается от ключевого слова const. Поле с модификатором const может быть
инициализировано только при объявлении поля. Поле с модификатором readonly может быть инициализировано
при объявлении или в конструкторе. Следовательно, поля с модификатором readonly могут иметь различные
значения в зависимости от использованного конструктора. Кроме того, поле const является константой
во время компиляции, а поле readonly можно использовать для констант времени выполнения,
как показано в следующем примере:

public static readonly uint timeStamp = (uint)DateTime.Now.Ticks;

*/

class Sample
{
    public static void Main(string[] args)
    {
        Test obj = new Test();
        Console.WriteLine(obj.t);
        Console.WriteLine(Test.s);
        obj.mass[0] = 50;
        //obj.mass = new int[3];
        //obj.t = 10;
    }
}