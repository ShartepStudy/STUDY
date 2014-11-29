using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Sokoban
{
    class Container: Block
    {
        public Container(int x, int y) : base(x, y) {/* Draw();*/ }
        public override void Draw() {
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(x, y, width, height));
            g.DrawLine(new Pen(Color.FromArgb(167, 167, 167), 4), x+6, y+6, x+width-8, y+height-8);
            g.DrawLine(new Pen(Color.FromArgb(167, 167, 167), 4), x+width - 8, y + 6, x + 6, y+height - 8);

        }
        public override BlockState Id
        {
            get
            {
                return BlockState.Container;
            }
        }
    }
}
