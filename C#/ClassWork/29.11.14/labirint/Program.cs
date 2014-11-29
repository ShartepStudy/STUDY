using System;
using System.Text;
using System.IO;

using System.Runtime.InteropServices;
using System.Threading;

public class Coord
{
    public int x;
    public int y;
}

public class Win32Interop
{
    [DllImport("crtdll.dll")]
    public static extern int _kbhit();
}

class Sample
{
    public static void Main()
    {
        Console.Title = "Лабиринт";
        Console.CursorVisible = false;
        int width = 70;
        int height = 20;
        Random r = new Random();
        int[,] maze = new int[height, width];
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (x == 0 || y == 0 || x == width - 1 || y == height - 1) maze[y, x] = 1;
                else maze[y, x] = r.Next(0, 5);

                if (x == 1 && y == 1) maze[y, x] = 7;

                if (maze[y, x] == 1) // если стенка
                {
                    Console.ForegroundColor = ConsoleColor.DarkGreen;
                    Console.Write(Convert.ToChar(0x2593));
                }
                else if (maze[y, x] == 2) // если монетка
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.Write("$");
                }
                else if (maze[y, x] == 7)
                {
                    Console.ForegroundColor = ConsoleColor.Blue;
                    Console.Write((char)1);
                }
                else if (maze[y, x] == 3) // если враг
                {

                    if (r.Next(0, 15) == 0)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.Write((char)1);
                    }
                    else
                    {
                        maze[y, x] = 0;
                        Console.Write(" ");
                    }
                }
                else
                {
                    Console.Write(" ");
                }
            }
            Console.WriteLine();
        }

        Coord c = new Coord();
        c.x = c.y = 1;

        while (true)
        {
            if (Win32Interop._kbhit() != 0)
            {
                ConsoleKeyInfo k = Console.ReadKey(true);
                Console.SetCursorPosition(c.x, c.y);
                Console.Write(" ");
                if (k.Key == ConsoleKey.DownArrow && maze[c.y + 1, c.x] != 1)
                {
                    c.y++;
                }

                Console.SetCursorPosition(c.x, c.y);
                Console.ForegroundColor = ConsoleColor.Blue;
                Console.Write((char)1);
            }
            else
            {
                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        if (maze[y, x] == 3)
                        {
                            /* логика движения ботов */
                        }
                    }
                }
                //Console.WriteLine("@");
                Thread.Sleep(15);
            }
        }
    }
}