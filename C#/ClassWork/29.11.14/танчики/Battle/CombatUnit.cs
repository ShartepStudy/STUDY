using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Battle
{
   abstract  public class CombatUnit
    {
        public Point[,] mass;
        public char[,] pic;
        public int direction;
        public int size = 3;
        public int live;

       public CombatUnit(int dir=1,int x=55,int y=60,int live =1)
       {
           Console.SetWindowSize(battleground.Width, battleground.Height);
           Console.SetBufferSize(battleground.Width, battleground.Height);

           this.live = live;
           mass = new Point[size, size];
           pic = new char[size, size];
           direction = dir;
           CreatePoint(x,y);
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

       private void tex()
       {
           //Console.SetCursorPosition(10, 20);
           //Console.Write(mass[0, size - 1].Y.ToString() + ' '+mass[0, 0].X.ToString() + ' '  +"\n" + "направление= " + direction);
           //Console.Write(battleground.live);
       }
       public void Clear()
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

       public abstract void Go();
       public abstract void Kill();
       public abstract void Shooting();
       public abstract void Print();

    }
}
