using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Sokoban
{
    class Box : Block
    {
        //bool onContainer = false;
        public Box(int x, int y, bool onContainer = false) : base(x, y) {
            this.onContainer = onContainer;
            //Draw();
        }
        static public void Draw(float x, float y)
        {
            byte fl = 4; // full line
            byte hl = (byte)(fl / 2); // half line
            g.FillRectangle(new SolidBrush(Color.Black), new RectangleF(x, y, width-1, height-1));
            g.FillRectangle(new SolidBrush(Color.FromArgb(121, 90, 0)), new RectangleF(x, y, width-1, height-1));
            g.DrawRectangle(new Pen(Color.FromArgb(174, 146, 46), fl), x + hl, y + hl, width - fl-1, height - fl-1);
            g.DrawLine(new Pen(Color.FromArgb(174, 146, 46), fl), x + hl, y + hl, x + width - fl-1, y + height - fl-1);
            g.DrawLine(new Pen(Color.FromArgb(174, 146, 46), fl), x + width - fl, y + hl, x + hl-1, y + height - fl-1);
            //g.DrawRectangle(new Pen(Color.Black, 1), x - 1, y-1, width, height);
            
        }
        public override void Draw() {
            byte fl = 4; // full line
            byte hl = (byte)(fl / 2); // half line
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(x, y, width - 1, height - 1));
            g.FillRectangle(new SolidBrush(Color.FromArgb(121, 90, 0)), new Rectangle(x, y, width - 1, height - 1));
            g.DrawRectangle(new Pen(Color.FromArgb(174, 146, 46), fl), new Rectangle(x + hl, y + hl, width - fl - 1, height - fl - 1));
            if (onContainer)
            {
                g.DrawLine(new Pen(Color.FromArgb(0, 170, 0), fl), x + fl, y + fl, x + width - (fl + hl) - 1, y + height - (fl + hl) - 1);
                g.DrawLine(new Pen(Color.FromArgb(0, 170, 0), fl), x + width - (fl + hl), y + fl, x + fl - 1, y + height - (fl + hl) - 1);
            }
            else
            {
                g.DrawLine(new Pen(Color.FromArgb(174, 146, 46), fl), x + hl, y + hl, x + width - fl - 1, y + height - fl - 1);
                g.DrawLine(new Pen(Color.FromArgb(174, 146, 46), fl), x + width - fl, y + hl, x + hl - 1, y + height - fl - 1);
            }
            
            //g.DrawRectangle(new Pen(Color.Black, 1), new Rectangle(x-1, y-1, width, height));
        }
        public void ChangePosition(byte y, byte x, ref Block from, ref Block where)
        {
            this.x = width * x;
            this.y = height * y;
            where = this;
            from = null;
        }
        public override BlockState Id
        {
            get
            {
                    return BlockState.Box;
            }
        }
    }
}
