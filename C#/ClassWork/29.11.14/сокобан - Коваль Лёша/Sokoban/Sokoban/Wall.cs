using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Sokoban
{
    class Wall: Block
    {
        public Wall(int x, int y) : base(x, y) { /*Draw();*/ }
        public override void Draw() {
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(x, y, width, height));
            Color wall = Color.FromArgb(170, 195, 202);
            g.FillRectangle(new SolidBrush(wall), new Rectangle(x, y, 19, 9));
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(x+19, y, 2, 9));
            g.FillRectangle(new SolidBrush(wall), new Rectangle(x+21, y, 9, 9));

            g.FillRectangle(new SolidBrush(wall), new Rectangle(x, y+10, 6, 9));
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(6, y+10, 2, 9));
            g.FillRectangle(new SolidBrush(wall), new Rectangle(x+8, y+10, 22, 9));

            g.FillRectangle(new SolidBrush(wall), new Rectangle(x, y + 20, 13, 9));
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(x+13, y + 20, 2, 9));
            g.FillRectangle(new SolidBrush(wall), new Rectangle(x+15, y + 20, 15, 9));

            g.DrawRectangle(new Pen(Color.Black, 1), new Rectangle(x-1, y-1, width, height));
        }
        public override BlockState Id
        {
            get
            {
                return BlockState.Wall;
            }
        }
    }
}
