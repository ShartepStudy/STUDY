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

    static public class battleground
    {
        public static int Width = 120;
        public static int Height = 60;
        public static MyTank aTank = new MyTank();
        public static List<Rocket> MyMissiles = new List<Rocket>();
        public static List<Rocket> VragiMissiles = new List<Rocket>();
        public static List<Enemy> Vragi = new List<Enemy>();
        public static int[,] mass = new int[Height, Width];
        public static  int cEnemy = 0;
        public static int  live = 5;
        public static long TimeGod = 0;
        public static long TimeToKill = 0;
        public static long TimeToGo = 0;

      static   battleground()
        {
            Console.SetWindowSize(battleground.Width, battleground.Height);
            Console.SetBufferSize(battleground.Width, battleground.Height);
        }

    }


    public class Program
    {
        private static void Main(string[] args)
        {
           
            Console.CursorVisible = false;
            Console.Title = "You have " + battleground.live.ToString() + ' ' + "live ";
            long MyTimeCount = 0;
            long VragiTimeCoun = 0;
            long EnemyTimeCreate = 0;
            long EnemyTimeGo = 0;
            
            Random rnd = new Random();

            while (battleground.live >0)
            {
                if (Win32Interop._kbhit() != 0)
                {
                    ConsoleKeyInfo code = Console.ReadKey(true);
                    MoveMyTank(code);
                }


                if (DateTime.Now.Ticks - MyTimeCount > 490000)
                {
                    MyTimeCount = DateTime.Now.Ticks;

                    for (int i = 0; i < battleground.MyMissiles.LongCount(); i++)
                    {
                        battleground.MyMissiles[i].Go();
                    }
                }

                //--------------------
                if (DateTime.Now.Ticks - VragiTimeCoun > 490000)
                {
                    VragiTimeCoun = DateTime.Now.Ticks;

                    for (int i = 0; i < battleground.VragiMissiles.LongCount(); i++)
                    {
                        battleground.VragiMissiles[i].Go();

                    }
                }
                //----------------------

                if (DateTime.Now.Ticks - EnemyTimeCreate > 60000000)
                {
                    EnemyTimeCreate = DateTime.Now.Ticks;

                    if (battleground.cEnemy < 10)
                    {
                        int live=0;
                        int tlife = rnd.Next(3) + 1;
                        switch (tlife)
                        {
                            case 1:
                                live = 1;
                                break;
                            case 2:
                                live = 3;
                                break;
                            case 3:
                                live = 5;
                                break;

                        }

                        Enemy tmp = new Enemy(live);
                        battleground.Vragi.Add(tmp);
                       battleground.cEnemy++;
                    }
                }
                if (DateTime.Now.Ticks - EnemyTimeGo > 2000000)
                {
                    EnemyTimeGo = DateTime.Now.Ticks;
                    if (battleground.cEnemy > 0)
                        {
                             
                            for (int i = 0; i < battleground.cEnemy; i++)
                            {
                                battleground.Vragi[i].Go();
                                   int tmp = rnd.Next(5);
                                    if (tmp == 1)
                                    {
                                        battleground.Vragi[i].Shooting();   
                                    }
                            }
                        }
            }
            }
        }

        public static void MoveMyTank(ConsoleKeyInfo code)
        {
            switch (code.Key)
            {
                case ConsoleKey.RightArrow:

                    if (DateTime.Now.Ticks - battleground.TimeToGo > 500000)
                    {
                        battleground.TimeToGo = DateTime.Now.Ticks;

                        if (battleground.aTank.Direction != (int) dir.RIGHT)
                            battleground.aTank.Direction = (int) dir.RIGHT;
                        else
                        {
                            battleground.aTank.Go();
                        }
                    }
                    break;
                case ConsoleKey.LeftArrow:

                    if (DateTime.Now.Ticks - battleground.TimeToGo > 500000)
                    {
                        battleground.TimeToGo = DateTime.Now.Ticks;


                        if (battleground.aTank.Direction != (int) dir.LEFT)
                            battleground.aTank.Direction = (int) dir.LEFT;
                        else
                        {
                            battleground.aTank.Go();
                            ;
                        }
                    }
                    break;
                case ConsoleKey.UpArrow:
                    if (DateTime.Now.Ticks - battleground.TimeToGo > 500000)
                    {
                        battleground.TimeToGo = DateTime.Now.Ticks;

                        if (battleground.aTank.Direction != (int) dir.UP)
                            battleground.aTank.Direction = ((int) dir.UP);
                        else
                        {
                            battleground.aTank.Go();
                        }
                    }
                    break;
                case ConsoleKey.DownArrow:
                    if (DateTime.Now.Ticks - battleground.TimeToGo > 500000)
                    {
                        battleground.TimeToGo = DateTime.Now.Ticks;

                        if (battleground.aTank.Direction != (int) dir.DOWN)
                            battleground.aTank.Direction = ((int) dir.DOWN);
                        else
                        {
                            battleground.aTank.Go();
                        }
                    }
                    break;

                case ConsoleKey.Spacebar:

                    if (DateTime.Now.Ticks - battleground.TimeToKill > 4500000)
                    {
                        battleground.TimeToKill = DateTime.Now.Ticks;

                        battleground.aTank.Shooting();
                    }
                    break;
            }
        } 
    }
}
