using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Runtime.InteropServices;
using System.IO;
using System.Windows.Forms;

namespace Sokoban
{
    class Program
    {

        static void Main(string[] args)
        {
            Console.CursorVisible = false;
            Console.WindowHeight = 40;
            Console.BufferHeight = 40;
            System.Threading.Thread.Sleep(400);
            Console.Title = "Сокобан";

            GameCore game = new GameCore();
            game.GameMenu();
            //game.Game();
            //Console.ReadLine();
        }
    }
}
