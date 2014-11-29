using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Sokoban
{
    enum Direction : byte { Down, Left, Right, Up };
    class Player : Block
    {
        Direction dir = Direction.Down;
        private System.Drawing.Bitmap rightImage = (Bitmap)Properties.Resources.ResourceManager.GetObject("max_walk_right");
        private System.Drawing.Bitmap leftImage = (Bitmap)Properties.Resources.ResourceManager.GetObject("max_walk_left");
        private System.Drawing.Bitmap upImage = (Bitmap)Properties.Resources.ResourceManager.GetObject("max_walk_up");
        private System.Drawing.Bitmap downImage = (Bitmap)Properties.Resources.ResourceManager.GetObject("max_walk_down");
        static private System.Drawing.Bitmap eyesImage = (Bitmap)Properties.Resources.ResourceManager.GetObject("mouse_eyes");
        private int fLeft = 0, fRight = 0, fUp = 0, fDown = 0;
        public Player(int x, int y) : base(x, y) { }
        public override void Draw()
        {
            switch (dir)
            {
                case Direction.Down:
                    downImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fDown);
                    int newWidth = (int)Math.Round(((decimal)downImage.Width / downImage.Height)*width);
                    g.DrawImage(downImage, x + (30 - newWidth) / 2, y, newWidth, 30);
            	    break;
                case Direction.Left:
                    leftImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fLeft);
                    g.DrawImage(leftImage, x+1, y, 27, 30);
                    break;
                case Direction.Right:
                    rightImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fRight);
                    g.DrawImage(rightImage, x+1, y, 27, 30);
                    break;
                case Direction.Up:
                    upImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fUp);
                    g.DrawImage(upImage, x+4, y, 22, 30);
                    break;
            }
        }
        Block []from;
        Block []where;
        Block []boxes;
        public void ChangePosition(byte y, byte x, ref Block[] from, ref Block[] where, ref Block[] box)
        {
            this.x = width * x;
            this.y = height * y;
            this.from = from;
            this.where = where;
            where[1] = this;
            from[1] = null;
            this.boxes = box;
        }
        /*public override BlockState Id
        {
            get
            {
                if (onContainer)
                    return BlockState.Container;
                else
                    return BlockState.Char;
            }
        }*/
        float steps=0;
        bool withBox = false;
        public void Up(bool withBox)
        {
            this.withBox = withBox;
            dir = Direction.Up;
            steps = y;
            ImageAnimator.Animate(upImage, new EventHandler(this.GoUp));
        }
        public void Down(bool withBox)
        {
            this.withBox = withBox;
            dir = Direction.Down;
            steps = y;
            ImageAnimator.Animate(downImage, new EventHandler(this.GoDown));
        }
        public void Left(bool withBox)
        {
            this.withBox = withBox;
            dir = Direction.Left;
            steps = x;
            ImageAnimator.Animate(leftImage, new EventHandler(this.GoLeft));
        }

        public void Right(bool withBox)
        {
            this.withBox = withBox;
            dir = Direction.Right;
            steps = x;
            ImageAnimator.Animate(rightImage, new EventHandler(this.GoRight));
        }

        private void GoDown(object o, EventArgs e)
        {
            
            if (steps < y)
            {
                steps += 4.285F;
                if (steps+0.5 >= y)
                {
                    ImageAnimator.StopAnimate(downImage, new EventHandler(this.GoDown));
                    for (byte i = 0; i < from.Length; i++)
                    {
                        if (from[i] != null)
                            from[i].Draw();
                        if (where[i] != null)
                            where[i].Draw();
                    }

                    if (withBox)
                    {
                        if (boxes[0].Id == BlockState.Container)
                            boxes[1].OnContainer = true;
                        else
                            boxes[1].OnContainer = false;
                        boxes[1].Draw();
                    }
                    steps = 0;
                    
                }
                else
                {
                    fDown = ++fDown % downImage.GetFrameCount(System.Drawing.Imaging.FrameDimension.Time);
                    downImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fDown);
                    g.FillRectangle(new SolidBrush(Color.Black), x, steps - 4.285F, width, height + 4.285F);
                    g.DrawImage(downImage, x + 4, steps, 22, 30);
                    if (withBox)
                        Box.Draw(x, steps + 30);
                    while (Console.KeyAvailable) Console.ReadKey(true);
                }
            }
            
        }
        private void GoUp(object o, EventArgs e)
        {
            if (steps > y)
            {
                steps -= 4.285F;
                if (steps-0.5 <= y)
                {
                    ImageAnimator.StopAnimate(upImage, new EventHandler(this.GoUp));
                    for (byte i = 0; i < from.Length; i++)
                    {
                        if (from[i] != null)
                            from[i].Draw();
                        if (where[i] != null)
                            where[i].Draw();
                    }
                    if (withBox)
                    {
                        if (boxes[0].Id == BlockState.Container)
                            boxes[1].OnContainer = true;
                        else
                            boxes[1].OnContainer = false;
                        boxes[1].Draw();
                    }
                    steps = 0;
                    
                }
                else
                {
                    fUp = ++fUp % upImage.GetFrameCount(System.Drawing.Imaging.FrameDimension.Time);
                    upImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fUp);
                    g.FillRectangle(new SolidBrush(Color.Black), x, steps, width, height + 4.285F);
                    g.DrawImage(upImage, x+4, steps, 22, 30);
                    if (withBox)
                        Box.Draw(x, steps - 30);
                    while (Console.KeyAvailable) Console.ReadKey(true);
                }
            }
        }
        private void GoRight(object o, EventArgs e)
        {
            if (steps < x)
            {
                steps += 4.285F;
                if (steps + 0.5 >= x)
                {
                    ImageAnimator.StopAnimate(rightImage, new EventHandler(this.GoRight));
                    for (byte i = 0; i < from.Length; i++)
                    {
                        if (from[i] != null)
                            from[i].Draw();
                        if (where[i] != null)
                            where[i].Draw();
                    }
                    if (withBox)
                    {
                        if (boxes[0].Id == BlockState.Container)
                            boxes[1].OnContainer = true;
                        else
                            boxes[1].OnContainer = false;
                        boxes[1].Draw();
                    }
                    steps = 0;
                    
                }
                else
                {
                    fRight = ++fRight % upImage.GetFrameCount(System.Drawing.Imaging.FrameDimension.Time);
                    rightImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fRight);
                    g.FillRectangle(new SolidBrush(Color.Black), steps - 4.285F, y, width + 4.285F, height);
                    g.DrawImage(rightImage, steps+1, y, 27, 30);
                    if (withBox)
                        Box.Draw(steps + 30, y);
                    while (Console.KeyAvailable) Console.ReadKey(true);
                }
            }
        }
        private void GoLeft(object o, EventArgs e)
        {
            if (steps > x)
            {
                steps -= 4.285F;
                if (steps - 0.5 <= x)
                {
                    ImageAnimator.StopAnimate(leftImage, new EventHandler(this.GoLeft));
                    for (byte i = 0; i < from.Length; i++)
                    {
                        if (from[i] != null)
                            from[i].Draw();
                        if (where[i] != null)
                            where[i].Draw();
                    }
                    if (withBox)
                    {
                        if (boxes[0].Id == BlockState.Container)
                            boxes[1].OnContainer = true;
                        else
                            boxes[1].OnContainer = false;
                        boxes[1].Draw();
                    }
                    steps = 0;
                }
                else
                {
                    fLeft = ++fLeft % upImage.GetFrameCount(System.Drawing.Imaging.FrameDimension.Time);
                    leftImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fLeft);
                    g.FillRectangle(new SolidBrush(Color.Black), steps, y, width + 4.285F, height);
                    g.DrawImage(leftImage, steps+1, y, 27, 30);
                    if (withBox)
                        Box.Draw(steps - 30, y);
                    while (Console.KeyAvailable) Console.ReadKey(true);
                }
            }

        }
        public void StopAllMoves() 
        {
            ImageAnimator.StopAnimate(downImage, new EventHandler(this.GoDown));
            ImageAnimator.StopAnimate(leftImage, new EventHandler(this.GoLeft));
            ImageAnimator.StopAnimate(rightImage, new EventHandler(this.GoRight));
            ImageAnimator.StopAnimate(upImage, new EventHandler(this.GoUp));
            

        }
        public bool CanGo()
        {
            return steps == 0;
        }
        System.Drawing.Bitmap winImage = (Bitmap)Properties.Resources.ResourceManager.GetObject("max_throw_cat");
        int fWin = 0;
        public void Win()
        {
            ImageAnimator.Animate(winImage, new EventHandler(this.PlayWin));
            
        }
        int big = 2;
        public void BreakWin()
        {
            ImageAnimator.StopAnimate(winImage, new EventHandler(this.PlayWin));
        }
        private void PlayWin(object o, EventArgs e)
        {
            winImage.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, fWin++);
            g.FillRectangle(new SolidBrush(Color.Black), 20,20, 30+big, (int)((22+big)*1.375));
            g.DrawImage(winImage, 20, 20, 30 + big, (int)(22 + big * 1.375));
            System.Threading.Thread.Sleep(50);
            if (fWin > winImage.GetFrameCount(System.Drawing.Imaging.FrameDimension.Time) - 2)
            {
                fWin = 0;
                ImageAnimator.StopAnimate(winImage, new EventHandler(this.PlayWin));
            }
            big += 5;
        }
    }
}
