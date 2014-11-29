using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Battle
{
    public class Rocket
    {
        public int direction;
        public Point COORD;
        char pic;
        public int side;
        public Rocket(int x, int y, int dir,int side)
        {
            COORD.X = x;
            COORD.Y = y;
            direction = dir;
            this.side = side;
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
            Console.SetCursorPosition(COORD.X, COORD.Y);
            Console.Write(' ');
        }
        public void Print()
        {
            if (side == 2)
            {
                Console.ForegroundColor = ConsoleColor.DarkRed;
                Console.SetCursorPosition(COORD.X, COORD.Y);
                Console.Write(pic);
                Console.ForegroundColor = ConsoleColor.Gray;     
            }
            if (side == 1)
            {
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.SetCursorPosition(COORD.X, COORD.Y);
                Console.Write(pic);
                Console.ForegroundColor = ConsoleColor.Gray;     
            }
          
        }

        private bool TrySpace ()
        {
             if (direction == 1 && COORD.Y == 0)
            {
                Clear();
                battleground.MyMissiles.Remove(this);
                return true;
            }

            else if (direction == 2 && COORD.Y == battleground.Height - 1)
            {
                Clear();
                battleground.MyMissiles.Remove(this);
                return true;
            }
            else if (direction == 3 && COORD.X == 0)
            {
                Clear();
                battleground.MyMissiles.Remove(this);
                return true;
            }

            else if (direction == 4 && COORD.X >= battleground.Width - 1)
            {
                Clear();
                battleground.MyMissiles.Remove(this);
                return true;
            }

            return false;

        }
        private bool TryGoSide1 ()
        {

            foreach (var V in battleground.Vragi)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {


                        switch (direction)
                        {
                            case (int)dir.UP:

                                if (V.mass[i, j].X == COORD.X && V.mass[i, j].Y - 1 == COORD.Y - 1)
                                {
                                    Clear();
                                    battleground.MyMissiles.Remove(this);
                                    V.Kill();
                                   
                                    return true;
                                }
                                break;
                            case (int)dir.DOWN:
                                if (V.mass[i, j].X == COORD.X && V.mass[i, j].Y + 1 == COORD.Y + 1)
                                {
                                    Clear();
                                    battleground.MyMissiles.Remove(this);
                                    V.Kill();
                                    
                                    return true;
                                }
                                break;
                            case (int)dir.LEFT:
                                if (V.mass[i, j].X - 1 == COORD.X - 1 && V.mass[i, j].Y == COORD.Y)
                                {
                                    Clear();
                                    battleground.MyMissiles.Remove(this);
                                    V.Kill();
                                   
                                    return true;
                                }
                                break;
                            case (int)dir.RIGHT:
                                if (V.mass[i, j].X + 1 == COORD.X + 1 && V.mass[i, j].Y == COORD.Y)
                                {
                                    Clear();
                                    battleground.MyMissiles.Remove(this);
                                    V.Kill();
                                   
                                    return true;
                                }
                                break;

                        }

                    }
                }
                
            }

            foreach (var n in battleground.VragiMissiles)
            {
                if (this.COORD.X == n.COORD.X && this.COORD.Y == n.COORD.Y)
                {
                    this.Clear();
                    battleground.MyMissiles.Remove(this);
                    n.Clear();
                    battleground.VragiMissiles.Remove(n);
                    return true;
                }
            }

            return false;
        }
        private bool TryGoSide2 ()
         {
             for (int i = 0; i < 3; i++)
             {
                 for (int j = 0; j < 3; j++)
                 {

                     switch (direction)
                     {
                         case (int) dir.UP:
                             if (battleground.aTank.mass[i, j].X == COORD.X && battleground.aTank.mass[i, j].Y-1 == COORD.Y-1)
                             {
                                 Clear();
                                 battleground.VragiMissiles.Remove(this);
                                 battleground.aTank.Kill();
                                 return true;
                             }
                             break;
                         case (int) dir.DOWN:
                              if (battleground.aTank.mass[i, j].X == COORD.X && battleground.aTank.mass[i, j].Y+1 == COORD.Y+1)
                             {
                                 Clear();
                                 battleground.VragiMissiles.Remove(this);
                                 battleground.aTank.Kill();
                                 return true;
                             }
                             break;
                         case (int) dir.LEFT:
                              if (battleground.aTank.mass[i, j].X-1 == COORD.X-1 && battleground.aTank.mass[i, j].Y == COORD.Y)
                             {
                                 Clear();
                                 battleground.VragiMissiles.Remove(this);
                                 battleground.aTank.Kill();
                                 return true;
                             }
                             break;

                         case (int)dir.RIGHT:
                             if (battleground.aTank.mass[i, j].X + 1 == COORD.X + 1 && battleground.aTank.mass[i, j].Y == COORD.Y)
                             {
                                 Clear();
                                 battleground.VragiMissiles.Remove(this);
                                 battleground.aTank.Kill();
                                 return true;
                             }
                             break;
                     }
                     
                 }
             }

             foreach (var n in battleground.MyMissiles)
             {
                 if (this.COORD.X == n.COORD.X && this.COORD.Y == n.COORD.Y)
                 {
                     this.Clear();
                     battleground.VragiMissiles.Remove(this);
                     n.Clear();
                     battleground.MyMissiles.Remove(n);
                     return true;
                 }
             }
            return false;
         }

        public void Go()
        {
            

            bool  Inside = false;
            bool  Before = false;
         
            if (TrySpace()) return;

            if (side == 1)
            {
                if (TryGoSide1()) return;
            }

            else if (side == 2)
            {
               
                if (TryGoSide2()) return;


               
                foreach (var h in battleground.Vragi)
                {

                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {

                            switch (direction)
                            {
                                case (int) dir.UP:
                                    if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y - 1)
                                        Before = true;
                                    else if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y)
                                        Inside = true;
                                   
                                    break;
                                case (int) dir.DOWN:

                                    if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y + 1)
                                        Before = true;
                                    else if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y)
                                        Inside = true;
                                   
                                    break;

                            
                                case (int) dir.LEFT:

                                    if (h.mass[i, j].X == COORD.X-1 && h.mass[i, j].Y == COORD.Y )
                                        Before = true;
                                    else if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y)
                                        Inside = true;
                                   
                                  
                                    break;
                                case (int) dir.RIGHT:

                                    if (h.mass[i, j].X == COORD.X + 1 && h.mass[i, j].Y == COORD.Y)
                                        Before = true;
                                    else if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y)
                                        Inside = true;
                                    
                                    break;

                            }

                            //if (h.mass[i, j].X == COORD.X && h.mass[i, j].Y == COORD.Y)
                            //{

                            //    Inside = true;
                            //    break;
                            //}


                        }

                       
                    }

                }
            }

            if (!Inside) Clear();


            //if (!Inside) Clear();
            
            switch (direction)
            {
                case 1:
                    COORD.Y--;
                    break;
                case 2:
                    COORD.Y++;
                    break;
                case 3:
                    COORD.X--;
                    break;
                case 4:
                    COORD.X++;
                    break;
            }


            if (!Before && !Inside) Print();

         //   if (!Inside) Print();
          //  if (k)
            //    Print();
            
        }

    }
}
