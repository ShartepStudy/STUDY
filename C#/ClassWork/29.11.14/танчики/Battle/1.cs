using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Battle
{

    public class Win32Interop
    {
        [DllImport("crtdll.dll")]
        public static extern int _kbhit();
    }

    public class battleground
    {
        public static int Width = 120;
        public static int Height = 60;
    }


    public class Program
    {

        public static MyTank aTank;
        public static List<Rocket> MyMissiles;
        public static List<Enemy> Vragi; 
        public static int[,] mass = new int[battleground.Height, battleground.Width];

        private static void Main(string[] args)
        {
            aTank=new MyTank();
            MyMissiles= new List<Rocket>();
            Vragi=new List<Enemy>();
            long  MyTimeCount = 0;

            Console.SetWindowSize(battleground.Width, battleground.Height);
            //Console.SetBufferSize(battleground.Width+5, battleground.Height+5);
            Console.CursorVisible = false;
            Console.BufferHeight = battleground.Height;
            Console.BufferWidth = battleground.Width;


            int cEnemy = 0;
            long EnemyTimeCount = 0;
          

            while (true)
            {
                if (Win32Interop._kbhit() != 0)
                {
                    ConsoleKeyInfo code = Console.ReadKey(true);
                    MoveMyTank(code);
                }


                if (DateTime.Now.Ticks - MyTimeCount > 260000)
                {
                    MyTimeCount = DateTime.Now.Ticks;
                    for (int i = 0; i < MyMissiles.LongCount(); i++)
                    {
                        MyMissiles[i].Go();
                    }
                }
                //if (DateTime.Now.Ticks - EnemyTimeCount > 2000000)
                //{
                //    EnemyTimeCount = DateTime.Now.Ticks;

                //    if (cEnemy < 5)
                //    {
                //        Enemy tmp = new Enemy();

                //        Vragi.Add(tmp);
                //        cEnemy++;
                //    }

                //    Random rnd = new Random(DateTime.Now.Millisecond);

                //    for (int i = 0; i < Vragi.LongCount(); i++)
                //    {

                //        int tmp = rnd.Next(0, 3);
                //        if (tmp == 2)
                //        {
                //            tmp = rnd.Next(1, 4);
                //            Vragi[i].Direction = tmp;
                //        }

                //        Vragi[i].Go();
                //    }                    
                //}               
            }
        }

        public static void MoveMyTank(ConsoleKeyInfo code)
        {
            switch (code.Key)
            {
                case ConsoleKey.RightArrow:
                    if (aTank.Direction != (int) dir.RIGHT)
                        aTank.Direction = (int) dir.RIGHT;
                    else
                    {
                        aTank.Go();
                    }
                    break;
                case ConsoleKey.LeftArrow:
                    if (aTank.Direction != (int) dir.LEFT)
                        aTank.Direction = (int) dir.LEFT;
                    else
                    {
                        aTank.Go();
                        ;
                    }
                    break;
                case ConsoleKey.UpArrow:
                    if (aTank.Direction != (int) dir.UP)
                        aTank.Direction = ((int) dir.UP);
                    else
                    {
                        aTank.Go();
                    }
                    break;
                case ConsoleKey.DownArrow:
                    if (aTank.Direction != (int) dir.DOWN)
                        aTank.Direction = ((int) dir.DOWN);
                    else
                    {
                        aTank.Go();
                    }
                    break;

                case ConsoleKey.Spacebar:
                    aTank.Shooting();
                    break;
            }
        }

        public static long MCount { get; set; }
    }

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

    public class MyTank : ICombatUnit
    {
        public Point[,] mass;
        private char[,] pic;
        private int direction;
        private int size = 3;

        public MyTank()
        {

            mass = new Point[size, size];
            pic = new char[size, size];
            direction = 4;
            CreatePoint(10,45);
            CreatePic();
        }

        public void CreatePoint(int y, int x)
        {
            for (int i = 0, Y = y; i < size; i++, Y++)
            {
                for (int j = 0, X = x; j < size; j++, X++)
                {
                    mass[i, j].Y = Y;
                    mass[i, j].X = X;
                }
            }
        }

        public int Direction
        {
            get { return direction; }
            set
            {
                if (value > 0 && value < 5)
                {


                    direction = value;
                    CreatePic();
                }
            }
        }

        public void CreatePic()
        {

            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                    if (direction == 1)
                    {
                        if (y == 0 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2502);
                        }
                        else if (y == 2 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2580);
                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }
                    else if (direction == 2)
                    {
                        if (y == 0 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2584);
                        }
                        else if (y == 2 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2502);

                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }
                    else if (direction == 3)
                    {
                        if (y == 1 && x == 0)
                        {
                            pic[y, x] = Convert.ToChar(0x2500);
                        }
                        else if (y == 1 && x == 2)
                        {
                            pic[y, x] = Convert.ToChar(0x0258C);

                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }

                    else if (direction == 4)
                    {
                        if (y == 1 && x == 0)
                        {
                            pic[y, x] = Convert.ToChar(0x02590);

                        }
                        else if (y == 1 && x == 2)
                        {

                            pic[y, x] = Convert.ToChar(0x2500);
                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }
                }
            }
            Print();
        }

        public void Go()
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

            Clear();

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

        public void Print()
        {
            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[y, x].X, mass[y, x].Y);
                    Console.Write(pic[y, x]);
                }


            }


            tex();
        }

        private void tex()
        {
            Console.SetCursorPosition(10, 20);
            Console.Write(mass[0, 0].X.ToString() + ' ' + mass[0, size - 1].Y.ToString() + "\n" + "направление= " + direction);

        }

        private void Clear()
        {
            if (direction == 1)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[2, x].X, mass[2, x].Y);
                    Console.Write(' ');
                }

            }
            else if (direction == 2)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[0, x].X, mass[0, x].Y);
                    Console.Write(' ');
                }
            }

            else if (direction == 3)
            {
                for (int y = 0; y < size; y++)
                {
                    Console.SetCursorPosition(mass[y, 2].X, mass[y, 2].Y);
                    Console.Write(' ');
                }
            }


            else if (direction == 4)
            {
                for (int y = 0; y < size; y++)
                {
                    Console.SetCursorPosition(mass[y, 0].X, mass[y, 0].Y);
                    Console.Write(' ');
                }
            }



        }

        public void Shooting()
        {
            int x = 0;
            int y = 0;
            if (direction == 1)
            {
                x = mass[0, 1].X;
                y = (mass[0, 1].Y - 1);
            }

            else if (direction == 2)
            {
                x = mass[size - 1, 1].X;
                y = (mass[size - 1, 1].Y + 1);
            }
            else if (direction == 3)
            {
                x = mass[1, 0].X - 1;
                y = (mass[1, 0].Y);
            }


            else if (direction == 4)
            {
                x = mass[1, size - 1].X + 1;
                y = (mass[1, size - 1].Y);
            }

            Rocket tmp = new Rocket(x,y,direction);


            Program.MyMissiles.Add(tmp);
         //   tmp.Print();
        }
    }

    public class Rocket
    {
        public int direction;
        public Point COORD;
        char pic;

       public Rocket(int x, int y, int dir)
        {
            COORD.X = x;
            COORD.Y = y;
            direction = dir;
            switch (direction)
            {
                case 1:
                    pic = Convert.ToChar(0x2551);
                   
                    break;
                case 2:

                    pic = Convert.ToChar(0x2551);
                    break;
                case 3:
                    pic = Convert.ToChar(0x2550);
                  
                    break;
                case 4:

                    pic = Convert.ToChar(0x2550);
                    break;
            }

           Print();
        }

        private void Clear()
        {
            Console.SetCursorPosition(COORD.X,COORD.Y);
            Console.Write(' ');
        }
        public void Print()
        {
            Console.ForegroundColor = ConsoleColor.DarkRed; 
            Console.SetCursorPosition(COORD.X, COORD.Y);
            Console.Write(pic);
            Console.ForegroundColor = ConsoleColor.Gray;
        }

        public void Go()
        {

            if (direction == 1 && COORD.Y == 0)
            {
                Clear();
                Program.MyMissiles.Remove(this); 
                return;
            }

            else if (direction == 2 && COORD.Y == battleground.Height-1)
            {
                Clear();
                Program.MyMissiles.Remove(this); 
                return;
            }
            else if (direction == 3 && COORD.X == 0)
            {
                Clear();
                Program.MyMissiles.Remove(this);
                return;
            }

            else if (direction == 4 && COORD.X >= battleground.Width-1 )
            {
                Clear();
                Program.MyMissiles.Remove(this);
                return;
            }

            Clear();

            switch (direction)
            {
                case 1: COORD.Y--;
                    break;
                case 2: COORD.Y++;
                    break;
                case 3: COORD.X--;
                    break;
                case 4: COORD.X++;
                    break;
            }

            Print();
        }
        
    }

    public  class Enemy: ICombatUnit
    {
        public Point[,] mass;
        private char[,] pic;
        private int direction;
        private int size = 3;

        public Enemy()
        {

            mass = new Point[size, size];
            pic = new char[size, size];
            direction = 4;
            Random rnd= new Random();
            int tmp = rnd.Next(1, 3);
            if (tmp == 1)
            {
                CreatePoint(80, 10);
            }
            else  if (tmp == 2)
            {
                CreatePoint(20, 20);
            }
            else if (tmp == 3)
            {
                CreatePoint(40, 30);
            }
            
            CreatePic();
        }

        public void CreatePoint(int y, int x)
        {
            for (int i = 0, Y = y; i < size; i++, Y++)
            {
                for (int j = 0, X = x; j < size; j++, X++)
                {
                    mass[i, j].Y = Y;
                    mass[i, j].X = X;
                }
            }
        }

        public int Direction
        {
            get { return direction; }
            set
            {
                if (value > 0 && value < 5)
                {


                    direction = value;
                    CreatePic();
                }
            }
        }

        public void CreatePic()
        {

            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                    if (direction == 1)
                    {
                        if (y == 0 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2502);
                        }
                        else if (y == 2 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2580);
                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }
                    else if (direction == 2)
                    {
                        if (y == 0 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2584);
                        }
                        else if (y == 2 && x == 1)
                        {
                            pic[y, x] = Convert.ToChar(0x2502);

                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }
                    else if (direction == 3)
                    {
                        if (y == 1 && x == 0)
                        {
                            pic[y, x] = Convert.ToChar(0x2500);
                        }
                        else if (y == 1 && x == 2)
                        {
                            pic[y, x] = Convert.ToChar(0x0258C);

                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }

                    else if (direction == 4)
                    {
                        if (y == 1 && x == 0)
                        {
                            pic[y, x] = Convert.ToChar(0x02590);

                        }
                        else if (y == 1 && x == 2)
                        {

                            pic[y, x] = Convert.ToChar(0x2500);
                        }
                        else
                        {
                            pic[y, x] = Convert.ToChar(0x02588);
                        }
                    }
                }
            }
            Print();
        }

        public void Go()
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

            Clear();

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

        public void Print()
        {
            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[y, x].X, mass[y, x].Y);
                    Console.Write(pic[y, x]);
                }


            }


            tex();
        }

        private void tex()
        {
            //Console.SetCursorPosition(10, 20);
            //Console.Write(mass[0, 0].X.ToString() + ' ' + mass[0, size - 1].Y.ToString() + "\n" + "направление= " + direction );
            
        }

        private void Clear()
        {
            if (direction == 1)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[2, x].X, mass[2, x].Y);
                    Console.Write(' ');
                }

            }
            else if (direction == 2)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[0, x].X, mass[0, x].Y);
                    Console.Write(' ');
                }
            }

            else if (direction == 3)
            {
                for (int y = 0; y < size; y++)
                {
                    Console.SetCursorPosition(mass[y, 2].X, mass[y, 2].Y);
                    Console.Write(' ');
                }
            }


            else if (direction == 4)
            {
                for (int y = 0; y < size; y++)
                {
                    Console.SetCursorPosition(mass[y, 0].X, mass[y, 0].Y);
                    Console.Write(' ');
                }
            }



        }

        public void Shooting()
        {
            int x = 0;
            int y = 0;
            if (direction == 1)
            {
                x = mass[0, 1].X;
                y = (mass[0, 1].Y - 1);
            }

            else if (direction == 2)
            {
                x = mass[size - 1, 1].X;
                y = (mass[size - 1, 1].Y + 1);
            }
            else if (direction == 3)
            {
                x = mass[1, 0].X - 1;
                y = (mass[1, 0].Y);
            }


            else if (direction == 4)
            {
                x = mass[1, size - 1].X + 1;
                y = (mass[1, size - 1].Y);
            }

            Rocket tmp = new Rocket(x,y,direction);


            Program.MyMissiles.Add(tmp);
         //   tmp.Print();
        }

    }

}
