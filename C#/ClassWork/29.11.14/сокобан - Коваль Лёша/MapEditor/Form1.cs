using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MapEditor
{
    public partial class Form1 : Form
    {
        enum BlockState : byte { Empty, Wall, Box, Container, BoxContainer, Char };
        private Bitmap CreateWallImage()
        {
            Bitmap wall = new Bitmap(pb_box.Width, pb_box.Height);
            Graphics gr = Graphics.FromImage(wall);
            Color w = Color.FromArgb(170, 195, 202);
            gr.FillRectangle(new SolidBrush(w), new Rectangle(0, 0, 19, 9));
            gr.FillRectangle(new SolidBrush(w), new Rectangle(21, 0, 9, 9));

            gr.FillRectangle(new SolidBrush(w), new Rectangle(0, 10, 6, 9));
            gr.FillRectangle(new SolidBrush(w), new Rectangle(8, 10, 22, 9));

            gr.FillRectangle(new SolidBrush(w), new Rectangle(0, 20, 13, 10));
            gr.FillRectangle(new SolidBrush(w), new Rectangle(15, 20, 15, 10));
            return wall;
        }
        private Bitmap CreateBoxImage()
        {
            Bitmap box = new Bitmap(pb_box.Width, pb_box.Height);
            byte fl = 4; // full line
            byte hl = (byte)(fl / 2); // half line
            Graphics gr = Graphics.FromImage(box);
            gr.FillRectangle(new SolidBrush(Color.FromArgb(121, 90, 0)), new RectangleF(0, 0, pb_box.Width, pb_box.Width));
            gr.DrawRectangle(new Pen(Color.FromArgb(174, 146, 46), fl), hl, hl, pb_box.Width - fl, pb_box.Height - fl);
            gr.DrawLine(new Pen(Color.FromArgb(174, 146, 46), fl), hl, hl, pb_box.Width - fl, pb_box.Height - fl);
            gr.DrawLine(new Pen(Color.FromArgb(174, 146, 46), fl), pb_box.Width - fl, hl, hl, pb_box.Height - fl);
            return box;
        }
        private Bitmap CreateBoxContainerImage()
        {
            byte fl = 4; // full line
            byte hl = (byte)(fl / 2); // half line
            Bitmap boxContainer = new Bitmap(pb_box_cont.Width, pb_box_cont.Height);
            Graphics gr = Graphics.FromImage(boxContainer);
            gr.FillRectangle(new SolidBrush(Color.FromArgb(121, 90, 0)), new Rectangle(0, 0, pb_box_cont.Width, pb_box_cont.Height));
            gr.DrawRectangle(new Pen(Color.FromArgb(174, 146, 46), fl), new Rectangle(hl, hl, pb_box_cont.Width - fl, pb_box_cont.Height - fl));
            gr.DrawLine(new Pen(Color.FromArgb(0, 170, 0), fl), fl, fl, pb_box_cont.Width - (fl + hl), pb_box_cont.Height - (fl + hl));
            gr.DrawLine(new Pen(Color.FromArgb(0, 170, 0), fl), pb_box_cont.Width - (fl + hl), fl, fl, pb_box_cont.Height - (fl + hl));
            return boxContainer;
        }
        private Bitmap CreateContainerImage()
        {
            Bitmap container = new Bitmap(pb_container.Width, pb_container.Height);
            Graphics gr = Graphics.FromImage(container);
            gr.DrawLine(new Pen(Color.FromArgb(167, 167, 167), 4), 6, 6, pb_container.Width - 8, pb_container.Height - 8);
            gr.DrawLine(new Pen(Color.FromArgb(167, 167, 167), 4), pb_container.Width - 8, 6, 6, pb_container.Height - 8);
            return container;
        }
        private Bitmap CreatePlayerImage()
        {
            Bitmap originalPlayer;
            originalPlayer = (Bitmap)Properties.Resources.ResourceManager.GetObject("max_walk_down");
            //player.SelectActiveFrame(System.Drawing.Imaging.FrameDimension.Time, 0);

            Bitmap player = new Bitmap(30, 30);
            Graphics gr = Graphics.FromImage(player);
            int newWidth = (int)Math.Round(((decimal)originalPlayer.Width / originalPlayer.Height) * 30);
            
            //player.Width = newWidth;
            //player.Height = 30;
            gr.DrawImage(originalPlayer, (30 - newWidth) / 2, 0, newWidth, 30);
            return player;
        }
           
        public Form1()
        {
            InitializeComponent();

            pb_wall.Image = CreateWallImage();
            pb_box.Image = CreateBoxImage();
            pb_container.Image = CreateContainerImage();
            pb_player.Image = CreatePlayerImage();
            pb_box_cont.Image = CreateBoxContainerImage();
            DirectoryInfo dr = new DirectoryInfo(Application.StartupPath + "\\level");
            if (!dr.Exists)
                Directory.CreateDirectory(dr.FullName);
            openFileDialog1.InitialDirectory = Application.StartupPath + "\\level";
        }
        private byte width;
        private byte height;
        private PictureBox[] map;
        private BlockState choosenBlock;
        private bool playerOnMap = false;
        private ushort countBox = 0;
        private ushort countContainer = 0;
        private void mi_new_Click(object sender, EventArgs e)
        {
            
            NewMap frm = new NewMap();
            if (DialogResult.OK == frm.ShowDialog())
            {
                playerOnMap = false;
                countBox = countContainer = 0;
                if (map != null)
                {
                    for (ushort i = 0; i < map.Length;i++ )
                    {
                        map[i].Dispose();
                    }
                    map = null;
                }
                width = frm.ImageWidth;
                height = frm.ImageHeight;
                map = new PictureBox[height*width];
                ushort it = 0;
                for (byte i = 0; i < height; i++)
                {
                    for (byte j = 0; j < width; j++)
                    {
                        map[it] = new PictureBox();
                        map[it].BorderStyle = BorderStyle.FixedSingle;
                        map[it].Location = new Point(j * 32, i * 32);
                        map[it].Size = new Size(32, 32);
                        map[it].Name = "img" + it;
                        /*if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                        {
                            map[it].Image = CreateWallImage();
                            map[it].Tag = BlockState.Wall;
                        }
                        else
                        {*/
                            map[it].Tag = BlockState.Empty;
                            map[it].MouseClick += new MouseEventHandler(mapClickImage);
                        //}
                        
                        ++it;
                    }
                }
                this.panel2.Controls.AddRange(map);
            }
            frm.Dispose();
        }
        private BlockState CheckTagOnClick(Object bs)
        {
            switch ((BlockState)bs)
            {
                case BlockState.BoxContainer:
                    --countBox;
                    --countContainer;
            	    break;
                case BlockState.Box:
                    --countBox;
                    break;
                case BlockState.Container:
                    --countBox;
                    break;
                case BlockState.Char:
                    playerOnMap = false;
                    break;
            }
            return (BlockState)bs;
        }
        private void mapClickImage(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                BlockState clickedBlock = CheckTagOnClick(((PictureBox)sender).Tag);
                switch (choosenBlock)
                {
                    case BlockState.BoxContainer:
                        if (((PictureBox)sender).Tag == null || clickedBlock != BlockState.BoxContainer)
                        {
                            ((PictureBox)sender).Image = CreateBoxContainerImage();
                            ((PictureBox)sender).Tag = BlockState.BoxContainer;
                            ++countBox;
                            ++countContainer;
                        }
                        break;
                    case BlockState.Box:
                        if (((PictureBox)sender).Tag == null || clickedBlock != BlockState.Box)
                        {
                            ((PictureBox)sender).Image = CreateBoxImage();
                            ((PictureBox)sender).Tag = BlockState.Box;
                            ++countBox;
                        }
                        break;
                    case BlockState.Wall:
                        if (((PictureBox)sender).Tag == null || clickedBlock != BlockState.Wall)
                        {
                            ((PictureBox)sender).Tag = BlockState.Wall;
                            ((PictureBox)sender).Image = CreateWallImage();
                        }
                        break;
                    case BlockState.Container:
                        if (((PictureBox)sender).Tag == null || clickedBlock != BlockState.Container)
                        {
                            ((PictureBox)sender).Tag = BlockState.Container;
                            ((PictureBox)sender).Image = CreateContainerImage();
                            ++countContainer;
                        }
                        break;
                    case BlockState.Char:
                        if (((PictureBox)sender).Tag == null || clickedBlock != BlockState.Char)
                        {
                            if (playerOnMap)
                            {
                                for (ushort i = 0; i < map.Length; i++)
                                {
                                    if (map[i].Tag != null && (BlockState)map[i].Tag == BlockState.Char)
                                    {
                                        map[i].Tag = BlockState.Empty;
                                        map[i].Image.Dispose();
                                        map[i].Image = null;

                                    }
                                }
                            }
                            ((PictureBox)sender).Tag = BlockState.Char;
                            playerOnMap = true;
                            ((PictureBox)sender).Image = CreatePlayerImage();
                        }
                        break;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (((PictureBox)sender).Image != null) {
                    if ((BlockState)(((PictureBox)sender).Tag) == BlockState.Char)
                        playerOnMap = false;
                    if ((BlockState)(((PictureBox)sender).Tag) == BlockState.Container)
                        --countContainer;
                    if ((BlockState)(((PictureBox)sender).Tag) == BlockState.Box)
                        --countBox;
                    if ((BlockState)(((PictureBox)sender).Tag) == BlockState.BoxContainer)
                    {
                        --countBox;
                        --countContainer;
                    }
                    ((PictureBox)sender).Tag = BlockState.Empty;
                    ((PictureBox)sender).Image.Dispose();
                    ((PictureBox)sender).Image = null;
                }
            }
        }
        private void itemChoose_MouseClick(object sender, MouseEventArgs e)
        {
            choosenBlock = (BlockState)(Convert.ToInt32(((PictureBox)sender).Tag));
        }

        private void mi_quit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void mi_save_Click(object sender, EventArgs e)
        {
            
            try
            {
                if (map == null)
                    throw new Exception("Прежде чем сохранить что-то, нужно чтоб это что-то было создано!");
                if (!playerOnMap)
                    throw new Exception("Нужно указать где будет находится игрок!");
                if (countBox < 1 || countBox != countContainer)
                    throw new Exception("Количество контейнеров должно совпадать с количеством коробок!");
                ushort lvl;
                SaveForm sf = new SaveForm();
                if (sf.ShowDialog() == DialogResult.OK)
                {
                    int tempLvl;
                    lvl = sf.Level;
                    byte countFiles = (byte)Directory.GetFiles("Level\\", "*.sm").Length;
                    DialogResult saveFormResult = DialogResult.Yes;
                    for (byte i = 0; i < countFiles; i++)
                    {
                        bool parse = int.TryParse(Path.GetFileNameWithoutExtension(Directory.GetFiles("Level\\", "*.sm")[i]).Replace("level", ""), out tempLvl);
                        if (parse && tempLvl == lvl)
                        {
                            if ((saveFormResult = MessageBox.Show("Такой уровень уже существует, перезаписать файл?", "Внимание!", MessageBoxButtons.YesNoCancel)) == DialogResult.No)
                            {
                                mi_save_Click(sender, e);
                                return;
                            }
                            break;
                        }
                    }
                    if (saveFormResult != DialogResult.Cancel)
                    {
                        byte[,] arrMap = new byte[height, width];
                        ushort it = 0;
                        for (byte i = 0; i < height; i++)
                        {
                            for (byte j = 0; j < width; j++)
                            {
                                arrMap[i, j] = (byte)map[it++].Tag;
                            }
                        }
                        using (FileStream fs = new FileStream("level\\level" + lvl + ".sm", FileMode.Create, FileAccess.Write))
                        {

                            //string writeText = level;
                            //byte[] writeBytes = Encoding.UTF8.GetBytes(writeText);
                            System.Runtime.Serialization.IFormatter formatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                            formatter.Serialize(fs, arrMap);

                            //fs.Write(writeBytes, 0, writeBytes.Length);
                            fs.Flush(); // сохранить данные на диск
                            fs.Close();
                            MessageBox.Show("Сохранено");
                        }
                    }
                    else
                        MessageBox.Show("Отменено");
                }
                sf.Dispose();
            }
            catch (System.Exception ex)
            {
                //MessageBox.Show(countBox.ToString());
                //MessageBox.Show(countContainer.ToString());
                MessageBox.Show(ex.Message, "Ошибочка вышла!");
            }
        }

        private void mi_open_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(openFileDialog1.FileName, FileMode.Open, FileAccess.Read))
                {
                    choosenBlock = BlockState.Empty;
                    byte[,] arrMap;
                    System.Runtime.Serialization.IFormatter formatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                    arrMap = (byte[,])formatter.Deserialize(fs);
                    height = (byte)arrMap.GetLength(0);
                    width = (byte)arrMap.GetLength(1);

                    if (map != null)
                    {
                        for (ushort i = 0; i < map.Length; i++)
                        {
                            map[i].Dispose();
                        }
                        map = null;
                    }
                    map = new PictureBox[height * width];

                    ushort it = 0;
                    for (byte i = 0; i < height; ++i )
                    {
                        for (byte j = 0; j < width; ++j)
                        {
                            map[it] = new PictureBox();
                            map[it].BorderStyle = BorderStyle.FixedSingle;
                            map[it].Location = new Point(j * 32, i * 32);
                            map[it].Size = new Size(32, 32);
                            map[it].Name = "img" + it;
                            map[it].MouseClick += new MouseEventHandler(mapClickImage);
                            switch ((BlockState)arrMap[i, j])
                            {
                                case BlockState.Wall:
                                    map[it].Tag = BlockState.Wall;
                                    map[it].Image = CreateWallImage();
                                    break;
                                case BlockState.Container:
                                    map[it].Tag = BlockState.Container;
                                    map[it].Image = CreateContainerImage();
                                    ++countContainer;
                                    break;
                                case BlockState.Box:
                                    map[it].Tag = BlockState.Box;
                                    map[it].Image = CreateBoxImage();
                                    ++countBox;
                                    break;
                                case BlockState.BoxContainer:
                                    map[it].Tag = BlockState.BoxContainer;
                                    map[it].Image = CreateBoxContainerImage();
                                    ++countContainer;
                                    ++countBox;
                                    break;
                                case BlockState.Char:
                                    map[it].Tag = BlockState.Char;
                                    map[it].Image = CreatePlayerImage();
                                    playerOnMap = true;
                                    break;
                                default:
                                    map[it].Tag = BlockState.Empty;
                                    break;
                            }
                            ++it;
                        }
                    }
                    this.panel2.Controls.AddRange(map);

                }
                
            }

        }

    }
}
