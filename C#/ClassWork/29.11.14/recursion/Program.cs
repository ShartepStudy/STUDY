using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Drawing;

namespace ConsoleApplication13
{
    class Program
    {

        class COORD
        {
            public int X;
            public int Y;

            public COORD(int x, int y)
            {
                X = x;
                Y = y;
            }
        }


        static int size = 5; // 5 - ... размер доски!
        static int[,] ar = new int[size, size]; // массив, изначально забитый нулями!
        // ноль в ячейке говорит о том, что мы на ней конём ещё не были

        static COORD[] p = new COORD[8]; // массив смещений


        static bool Pony(int x, int y, int step = 1)
        {
            ar[x, y] = step;
            Show();
            if (step >= size * size) return true;

            for (int i = 0; i < 8; i++)
            {
                if ((x + p[i].X >= 0) && (x + p[i].X < size) && (y + p[i].Y >= 0) &&
                    (y + p[i].Y < size) && (ar[x + p[i].X, y + p[i].Y] == 0))
                {
                    if (Pony(x + p[i].X, y + p[i].Y, step + 1)) return true;
                }
            }
            ar[x, y] = 0;
            Console.WriteLine("OTKAT!\n");
            Thread.Sleep(500);
            Show();
            return false;
        }

        static void Show()
        {
            Console.Clear();
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    Console.Write("\t" + ar[i, j]);
                }
                Console.WriteLine("\n");
            }
            Thread.Sleep(500);
        }

        static void Main()
        {
            // задаём возможные 8 смещений!
            p[0] = new COORD(-2, -1);
            p[1] = new COORD(2, -1);
            p[2] = new COORD(-1, -2);
            p[3] = new COORD(1, -2);
            p[4] = new COORD(-2, 1);
            p[5] = new COORD(2, 1);
            p[6] = new COORD(-1, 2);
            p[7] = new COORD(1, 2);

            // попытка заполнить доску!
            Pony(0, 0); // x, y, step


            //for (int i = 0; i < size; i++)
            //{
            //    for (int j = 0; j < size; j++)
            //    {
            //        Console.Write("\t" + ar[i, j]);
            //    }
            //    Console.WriteLine("\n");
            //}
        }

    }
}