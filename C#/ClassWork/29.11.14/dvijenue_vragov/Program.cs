
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

public class cc
{
    public Coord c;
    public int dir;
    public cc()
    {
        c = new Coord();
    }
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
        Console.Title = "Движение врагов";
        Console.CursorVisible = false;

        int width = 55;
        int height = 25;
        int max_enemy = 10;

        int[,] mass = new int[height, width];
        Random r = new Random();

        int cur_enemy = 0;
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                int rn = r.Next(0, 50);
                if (rn == 0) mass[j, i] = 1;
                else if (rn == 1 && cur_enemy < max_enemy)
                {
                    cur_enemy++;
                    mass[j, i] = 2;
                }
                if (j == 0 || i == 0 || j == height - 1 || i == width - 1) mass[j, i] = 1;
            }
        }
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (mass[j, i] == 1)
                {
                    Console.ForegroundColor = ConsoleColor.DarkGreen;
                    Console.Write(Convert.ToChar(0x2593));
                }
                else if (mass[j, i] == 2)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write((char)2);
                }
                else Console.Write(" ");
            }
            Console.WriteLine();
        }

        int k = 0; // количество врагов
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (mass[j, i] == 2) k++;
            }
        }

        Console.WriteLine();
        Console.WriteLine();



        cc[] enemy = new cc[k];

        int cur = 0; // заполнение информации о координатах и направлении врагов
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (mass[j, i] == 2)
                {
                    enemy[cur] = new cc();
                    enemy[cur].dir = 2;
                    enemy[cur].c.x = i;
                    enemy[cur].c.y = j;
                    cur++;
                }
            }
        }



        while (true)
        {
            for (int j = 0; j < height; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    if (mass[j, i] == 2)
                    {
                        int num = -1;
                        for (int q = 0; q < k; q++)
                        {
                            if (enemy[q].c.x == i && enemy[q].c.y == j) { num = q; break; }
                        }
                        if (num < 0) continue;
                        if (enemy[num].dir == 1)
                        {
                            Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                            Console.Write(" ");
                            mass[enemy[num].c.y, enemy[num].c.x] = 0;
                            enemy[num].c.x--;
                            if (mass[enemy[num].c.y, enemy[num].c.x] != 0)
                            {
                                enemy[num].dir = r.Next(1, 5);
                                enemy[num].c.x++;
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                            }
                            else
                            {
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                            }
                        }
                        else if (enemy[num].dir == 2)
                        {
                            Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                            Console.Write(" ");
                            mass[enemy[num].c.y, enemy[num].c.x] = 0;
                            enemy[num].c.y--;
                            if (mass[enemy[num].c.y, enemy[num].c.x] != 0)
                            {
                                enemy[num].dir = r.Next(1, 5);
                                enemy[num].c.y++;
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                            }
                            else
                            {
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                            }
                        }
                        else if (enemy[num].dir == 3)
                        {
                            Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                            Console.Write(" ");
                            mass[enemy[num].c.y, enemy[num].c.x] = 0;
                            enemy[num].c.x++;
                            if (mass[enemy[num].c.y, enemy[num].c.x] != 0)
                            {
                                enemy[num].dir = r.Next(1, 5);
                                enemy[num].c.x--;
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                            }
                            else
                            {
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                            }
                            if (i < width - 1) i++;
                        }
                        else if (enemy[num].dir == 4)
                        {
                            Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                            Console.Write(" ");
                            mass[enemy[num].c.y, enemy[num].c.x] = 0;
                            enemy[num].c.y++;
                            if (mass[enemy[num].c.y, enemy[num].c.x] != 0)
                            {
                                enemy[num].dir = r.Next(1, 5);
                                enemy[num].c.y--;
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                            }
                            else
                            {
                                Console.SetCursorPosition(enemy[num].c.x, enemy[num].c.y);
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.Write((char)2);
                                mass[enemy[num].c.y, enemy[num].c.x] = 2;
                            }
                            if (j < height - 1) j++;
                        }
                    }
                }
            }
            Thread.Sleep(15);
        }

    }
}
