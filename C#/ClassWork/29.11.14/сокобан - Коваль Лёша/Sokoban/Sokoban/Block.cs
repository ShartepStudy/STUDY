using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;

namespace Sokoban
{
    enum BlockState : byte { Empty, Wall, Box, Container, BoxContainer, Char };
    class Block
    {
        [DllImport("kernel32.dll")]
        static extern IntPtr GetConsoleWindow();
        private static IntPtr handle = GetConsoleWindow();
        protected static Graphics g = Graphics.FromHwnd(handle);
        protected int x;
        protected int y;
        protected static int width = 30;
        protected static int height = 30;
        protected bool onContainer = false;
        static public void Clear()
        {
            g.Clear(Color.Black);
        }
        public Block(Block obj)
        {
            this.onContainer = obj.onContainer;
            this.x = obj.x;
            this.y = obj.y;
        }
        public Block(int x, int y)
        {
            
            //width = 30;
            //height = 30;
            this.x = x;
            this.y = y;
            //Draw();
        }

        public virtual BlockState Id
        {
            get {
                return BlockState.Empty;
            }
        }
        public virtual void Draw()
        {
            g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(x, y, width, height));
        }
        public static bool operator true(Block obj)
        {
            return obj != null;
        }
        public static bool operator false(Block obj)
        {
            return obj == null;
        }
        public static int Width
        {
            get
            {
                return width;
            }
        }
        public static int Height
        {
            get
            {
                return height;
            }
        }
        public bool OnContainer
        {
            get
            {
                return onContainer;
            }
            set
            {
                onContainer = value;
            }
        }
    }
}
