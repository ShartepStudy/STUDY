using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Battle
{
    interface ICombatUnit
    {
        int Direction { get; set; }
        void Go();
        void CreatePic();
        void CreatePoint(int y, int x);
    }

    public enum dir
    {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    };

    public class MyTank :CombatUnit
    {
        public MyTank(int dir = 1, int x = 55, int y = 60, int live = 1)
            : base(dir, x, y, live)
        {
            ;
        }

        public override void Go()
        {
             if (direction == 1 && mass[0, 0].Y == 0)
            {
                return;
            }

            else if (direction == 2 && mass[0, 0].Y == battleground.Height - size)
            {
                return;
            }
            else if (direction == 3 && mass[0, 0].X == 0)
            {
                return;
            }

            else if (direction == 4 && mass[0, 0].X >= battleground.Width - size)
            {
                return;
            }

            base.Clear();

            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {

                    switch (direction)
                    {
                        case 1: mass[y, x].Y--;
                            break;
                        case 2: mass[y, x].Y++;
                            break;
                        case 3: mass[y, x].X--;
                            break;
                        case 4: mass[y, x].X++;
                            break;
                    }
                }

            }

            Print();
        
        }
        public override void Shooting()
        {
            int x = 0;
            int y = 0;
            if (direction == 1 && mass[0, 1].Y - 1 >=0)
            {
                x = mass[0, 1].X;
                y = (mass[0, 1].Y - 1);
            }

            else if (direction == 2 && mass[size - 1, 1].Y + 1 < battleground.Height)
            {
                x = mass[size - 1, 1].X;
                y = (mass[size - 1, 1].Y + 1);
            }
            else if (direction == 3 && mass[1, 0].X - 1 >0)
            {
                x = mass[1, 0].X - 1;
                y = (mass[1, 0].Y);
            }


            else if (direction == 4 && mass[1, size - 1].X + 1 <battleground.Width)
            {
                x = mass[1, size - 1].X + 1;
                y = (mass[1, size - 1].Y);
            }
            if (x != 0 && y != 0)
            {
                Rocket tmp = new Rocket(x, y, direction,1);
                battleground.MyMissiles.Add(tmp); 
            }

        
           
        }
        public override void Kill()
        {
            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[y, x].X, mass[y, x].Y);
                    Console.Write(' ');
                }
            }


            if (DateTime.Now.Ticks - battleground.TimeGod > 60000000)
            {
                battleground.TimeGod = DateTime.Now.Ticks;
                battleground.live--;

                Console.Title = "You have " + battleground.live.ToString() + ' ' + "live ";
                if (battleground.live > 0)
                {
                    direction = 1;
                    CreatePoint(55, 60);
                    CreatePic();
                    Print();
                }
            }
            else if (battleground.live>0)
            {
                Print();
            }
               
        }
        public override void Print()
        {
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            for (int y = 0; y < size; y++)
            {
                Console.SetCursorPosition(0, 0);
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[y, x].X, mass[y, x].Y);
                    Console.Write(pic[y, x]);

                }
            }
            Console.SetCursorPosition(0, 0);
            Console.ForegroundColor = ConsoleColor.Gray;

        }
    }
}
