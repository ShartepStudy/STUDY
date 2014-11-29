using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Battle
{
    public class Enemy : CombatUnit
    {
        static  Random rnd = new Random(DateTime.Now.Millisecond);
        private int hod = 0;
        public Enemy(int live):base(2,rnd.Next((battleground.Height-3)),rnd.Next(battleground.Width-3),live)
        {
            ;
        }
        private void TrySpace()
       {
           hod++;

           if (hod % 10 == 0)
           {
               direction = rnd.Next(5);
               CreatePic();
           }

           if (direction == 1 && mass[0, 0].Y == 0)
           {
               direction = 2; // return;
           }

           else if (direction == 2 && mass[0, 0].Y == battleground.Height - size)
           {
               direction = 1; //return;
           }
           else if (direction == 3 && mass[0, 0].X == 0)
           {
               direction = 4;// return;
           }

           else if (direction == 4 && mass[0, 0].X >= battleground.Width - size)
           {
               direction = 3; //return;
           }

       }
        private bool  TryGo()
       {
           for (int y = 0; y < size; y++)
           {
               for (int x = 0; x < size; x++)
               {

                   foreach (var V in battleground.Vragi)
                   {
                       for (int i = 0; i < size; i++)
                       {
                           for (int j = 0; j < size; j++)
                           {
                               if (this != V)
                               {
                                   switch (direction)
                                   {
                                       case (int) dir.UP:
                                           if (mass[y, x].Y - 2 == V.mass[i, j].Y && mass[y, x].X == V.mass[i, j].X)
                                               return false;
                                           break;
                                       case (int) dir.DOWN:
                                           if (mass[y, x].Y + 2 == V.mass[i, j].Y && mass[y, x].X == V.mass[i, j].X)
                                               return false;
                                           break;
                                       case (int) dir.LEFT:
                                           if (mass[y, x].Y == V.mass[i, j].Y && mass[y, x].X - 2 == V.mass[i, j].X)
                                               return false;
                                           break;
                                       case (int) dir.RIGHT:
                                           if (mass[y, x].Y == V.mass[i, j].Y && mass[y, x].X + 2 == V.mass[i, j].X)
                                               return false;
                                           break;
                                   }
                               }

                           }
                       } 


                   }

                   //switch (direction)
                   //{
                   //    case (int)dir.UP: mass[y, x].Y--;
                   //        break;
                   //    case (int)dir.DOWN: mass[y, x].Y++;
                   //        break;
                   //    case (int)dir.LEFT: mass[y, x].X--;
                   //        break;
                   //    case (int)dir.RIGHT: mass[y, x].X++;
                   //        break;
                   //}
               }

           }
            return true;
       }
        private void TryKill()
        {
            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {

                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            if (mass[y, x].X == battleground.aTank.mass[i, j].X
                                && mass[y, x].Y == battleground.aTank.mass[i, j].Y)
                            {
                                battleground.aTank.Kill();
                            }

                        }
                    }
                }
            }
        }
        public override void Go()
        {
            TrySpace();
            if (TryGo()==false) return;
            CreatePic();
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
            TryKill();
            Print();
        }
        public override void Print()
        {
            Console.SetCursorPosition(0, 0);
            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                  if (live > 3)
                  {
                      Console.ForegroundColor = ConsoleColor.DarkYellow;
                  }
                  else if (live > 1)
                  {
                      Console.ForegroundColor = ConsoleColor.Yellow;
                  }
                  else if (live == 1)
                  {
                      Console.ForegroundColor = ConsoleColor.Gray;
                  }

                   
                    Console.SetCursorPosition(mass[y, x].X, mass[y, x].Y);
                    Console.Write(pic[y, x]);
                }
            }
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.SetCursorPosition(0, 0);    
            
        }
        public override void Shooting()
        {
            int x = 0;
            int y = 0;
            if (direction == 1 && mass[0, 1].Y - 1 >= 0)
            {
                x = mass[0, 1].X;
                y = (mass[0, 1].Y - 1);
            }

            else if (direction == 2 && mass[size - 1, 1].Y + 1 < battleground.Height)
            {
                x = mass[size - 1, 1].X;
                y = (mass[size - 1, 1].Y + 1);
            }
            else if (direction == 3 && mass[1, 0].X - 1 > 0)
            {
                x = mass[1, 0].X - 1;
                y = (mass[1, 0].Y);
            }


            else if (direction == 4 && mass[1, size - 1].X + 1 < battleground.Width)
            {
                x = mass[1, size - 1].X + 1;
                y = (mass[1, size - 1].Y);
            }
            if (x != 0 && y != 0)
            {
                Rocket tmp = new Rocket(x, y, direction,2);
                battleground.VragiMissiles.Add(tmp);
            }
        }
        public override  void Kill()
        {

           Console.SetCursorPosition(0, 0);
            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)
                {
                    Console.SetCursorPosition(mass[y, x].X, mass[y, x].Y);
                    Console.Write(' ');
                }
            }

            live--;

            if (live > 0)
            {
                Print();
            }
            else
            {
                battleground.Vragi.Remove(this);
                battleground.cEnemy--;
            }

          

        }
    }
}
