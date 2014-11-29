using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace Sokoban
{
    class Win32Interop
    {
        [System.Runtime.InteropServices.DllImport("crtdll.dll")]
        public static extern int _kbhit();
    }
    class GameCore
    {
        
        [System.Runtime.InteropServices.DllImport("kernel32.dll")]
        static extern IntPtr GetConsoleWindow();
        private static IntPtr handle = GetConsoleWindow();
        protected Graphics g = Graphics.FromHwnd(handle);
        System.Drawing.Point p;
        private ushort level = 1;
        private Block[,][] field;
        private ushort width;
        private ushort height;
        List<Block> boxesOnMap = new List<Block>();
        string[] levels;
        public void GameMenu()
        {
            
            byte countFiles = (byte)Directory.GetFiles("Level\\", "*.sm").Length;
            levels = new string[countFiles];
            int lvl;
            for (byte i = 0; i < countFiles; i++)
            {
                if ((lvl = int.Parse(Path.GetFileNameWithoutExtension(Directory.GetFiles("Level\\", "*.sm")[i]).Replace("level", "")))!=-1) {
                    levels[lvl-1] = Path.GetFileName(Directory.GetFiles("Level\\", "*.sm")[i]);
                }
            }
            ConsoleKeyInfo key;
            do 
            {
                if (field!= null)
                    ((Player)field[p.Y, p.X][1]).StopAllMoves();
                g.Clear(Color.Black);
                Console.Clear();
                Console.WriteLine("1) Начать игру");
                Console.WriteLine("2) Выбрать уровень");
                Console.WriteLine("0) Выход");
                key = Console.ReadKey(true);
                if (key.Key == ConsoleKey.D1)
                    CreateLevel(1);
                if (key.Key == ConsoleKey.D2)
                {
                    byte countLevels = ReadFromFile();
                    string str = string.Empty;
                    do 
                    {
                        if (str.Length > 0 && level == 0)
                            break;
                        Console.Clear();
                        Console.Write("Отмена: 0\n");
                        Console.Write("Открытые Уровни: ");
                        for(byte i=0;i<countLevels;i++) {
                               Console.Write(i+1);
                               if (i<countLevels-1)
                                   Console.Write(", ");
                        }
                        Console.WriteLine();
                    } while (!ushort.TryParse((str = Console.ReadLine()), out level) || (ushort.TryParse(str, out level) && level > countLevels ));
                    if (level!=0)
                        CreateLevel(level);
                }
                    
            } while (key.Key != ConsoleKey.D0);
        }
        private void ReadLevelFromFile()
        {
            using (FileStream fs = new FileStream("level\\" + levels[level-1], FileMode.Open, FileAccess.Read))
            {
                uint countPlayers = 0;
                uint countContainers = 0;
                field = null;
                byte[,] arrMap;
                System.Runtime.Serialization.IFormatter formatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                arrMap = (byte[,])formatter.Deserialize(fs);
                height = (byte)arrMap.GetLength(0);
                width = (byte)arrMap.GetLength(1);
                Console.SetCursorPosition(width * 30 / 8 + 2, 2);
                Console.Write("Level: " + level + "/" + levels.Length);
                int x = 0;
                int y = 0;
                field = new Block[height, width][];
                for (byte i = 0; i < height; ++i)
                {
                    x = 0;
                    for (byte j = 0; j < width; ++j)
                    {
                        field[i, j] = new Block[2];
                        switch ((BlockState)arrMap[i, j]) {

                            case BlockState.Empty:
                                field[i, j][0] = new Block(x, y);
                                break;
                            case BlockState.Wall:
                                field[i, j][0] = new Wall(x, y);
                                break;
                            case BlockState.Box:
                                field[i, j][0] = new Block(x, y);
                                field[i, j][1] = new Box(x, y, false);
                                boxesOnMap.Add(field[i, j][1]);
                                break;
                            case BlockState.BoxContainer:
                                countContainers++;
                                field[i, j][0] = new Container(x, y);
                                field[i, j][1] = new Box(x, y, true);
                                boxesOnMap.Add(field[i, j][1]);
                                break;
                            case BlockState.Container:
                                countContainers++;
                                field[i, j][0] = new Container(x, y);
                                break;
                            case BlockState.Char:
                                countPlayers++;
                                if (countPlayers > 1)
                                    throw new Exception("На уровне больше одного игрока!");
                                p.X = j;
                                p.Y = i;
                                field[i, j][1] = new Player(x, y);
                                field[i, j][0] = new Block(x, y);
                                break;
                            
                        }
                        x += Block.Width;
                    }
                    y += Block.Height;
                }    
                if (boxesOnMap.Count != countContainers)
                    throw new Exception("Количество контейнеров не совпадает с количеством ящиков!");
                for (byte i = 0; i < height; ++i)
                    for (byte j = 0; j < width; ++j)
                        for (byte k = 0; k < field[i, j].Length; k++)
                            if (field[i, j][k])
                                field[i, j][k].Draw();

                
            }
        }
        public void CreateLevel(int lvl = -1)
        {
            try
            {
                Console.Clear();
                width = height = 0;

                boxesOnMap.Clear();
                Block.Clear();
                
                if (lvl != -1)
                    level = (ushort)lvl;
                if (level >= levels.Length+1) {
                    Console.WriteLine("Поздравляю! Все уровни пройдены! Можете создать свой уровень через редактор уровней.");
                    Console.ReadLine();
                    return;
                }

                try
                {
                    ReadLevelFromFile();
                }
                catch (System.Exception ex)
                {
                    ++level;
                    CreateLevel(level);
                    return;
                }

                
                if (level == 1)
                {
                    Console.SetCursorPosition(4, 20);
                    Console.Write("Инструкции: Push \"box\" to \"x\"");
                    Console.SetCursorPosition(4, 21);
                    Console.Write("Движения: WASD or Arrows");
                    Console.SetCursorPosition(4, 22);
                    Console.Write("Меню: TAB");
                    Console.SetCursorPosition(4, 23);
                    Console.Write("Переиграть уровень: R");
                }


                level++;

                Game();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                Console.ReadLine();
                System.Diagnostics.Process.GetCurrentProcess().CloseMainWindow();
            }
            
        }
        private void SideMove(sbyte x, sbyte y)
        {
            bool withBox = false;
            if (field[p.Y + y, p.X + x][0].Id != BlockState.Wall)
            {
                if (field[p.Y + y, p.X + x][1]!=null && field[p.Y + y, p.X + x][1].Id == BlockState.Box)
                    withBox = true;
                bool nextStep = field[p.Y + y + y, p.X + x + x][0].Id != BlockState.Wall && field[p.Y + y + y, p.X + x + x][1] == null;
                if (!nextStep)
                    nextStep = field[p.Y + y + y, p.X + x + x][1] != null && field[p.Y + y + y, p.X + x + x][1].Id != BlockState.Box;
                if (!nextStep)
                    nextStep = !withBox;

                if (nextStep)
                {
                    //while (!((Player)field[p.Y, p.X][1]).CanGo()) {}
                    if (((Player)field[p.Y, p.X][1]).CanGo()) {
                        if (x > 0)
                            ((Player)field[p.Y, p.X][1]).Right(withBox);
                        else if (x < 0)
                            ((Player)field[p.Y, p.X][1]).Left(withBox);
                        else if (y < 0)
                            ((Player)field[p.Y, p.X][1]).Up(withBox);
                        else if (y > 0)
                            ((Player)field[p.Y, p.X][1]).Down(withBox);

                        if (withBox)
                            ((Box)field[p.Y + y, p.X + x][1]).ChangePosition((byte)(p.Y + y + y), (byte)(p.X + x + x), ref field[p.Y + y, p.X + x][1], ref field[p.Y + y + y, p.X + x + x][1]);
                        ((Player)field[p.Y, p.X][1]).ChangePosition((byte)(p.Y + y), (byte)(p.X + x), ref field[p.Y, p.X], ref field[p.Y + y, p.X + x], ref field[p.Y + y + y, p.X + x + x]);
                    
                        p.Y = p.Y + y;
                        p.X = p.X + x;
                    }
                }
            }
        }
        private void WriteToFile()
        {
            if (level <= levels.Length && ReadFromFile() < level + 1)
            {
                using (FileStream fs = new FileStream("level\\levels.bin", FileMode.Create, FileAccess.Write))
                {

                    //string writeText = level;
                    //byte[] writeBytes = Encoding.UTF8.GetBytes(writeText);
                    System.Runtime.Serialization.IFormatter formatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                    char d = Convert.ToChar(level + 3);
                    formatter.Serialize(fs, d.ToString());

                    //fs.Write(writeBytes, 0, writeBytes.Length);
                    fs.Flush(); // сохранить данные на диск
                    fs.Close();
                }
            }
            //fs.Dispose();
        }
        private byte ReadFromFile()
        {
            byte lvl;
            try
            {
                using (FileStream fs = new FileStream("level\\levels.bin", FileMode.Open, FileAccess.Read)) 
                {
                
                        //string writeText = level;
                        //byte[] writeBytes = Encoding.UTF8.GetBytes(writeText);
                        System.Runtime.Serialization.IFormatter formatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                        string text = (string)formatter.Deserialize(fs);
                        lvl = (byte)(Convert.ToChar(text) - 3);
                        //string text  = t.ToString();
                        //string text = fs.Read().ToString();

                    
                        fs.Close();
                    
                    //fs.Dispose();
                }
            }
            catch 
            {
                return 1;
            }
            return lvl;
            
        }
        public void Game()
        {
            ConsoleKeyInfo key;
            bool win = false;
            // Console.ReadKey(true) клавишу считывает, но не отображает
            while (true)
            {
                if (Win32Interop._kbhit()!=0)
                {
                        key = Console.ReadKey(true);
                    switch (key.Key)
                    {
                            
                        case ConsoleKey.UpArrow:
                        case ConsoleKey.W:
                            SideMove(0, -1);
                            break;
                        case ConsoleKey.DownArrow:
                        case ConsoleKey.S:
                            SideMove(0, 1);
                            break;
                        case ConsoleKey.LeftArrow:
                        case ConsoleKey.A:
                            SideMove(-1, 0);
                            break;
                        case ConsoleKey.RightArrow:
                        case ConsoleKey.D:
                            SideMove(1, 0);
                            break;
                        case ConsoleKey.Tab:
                            return;
                        case ConsoleKey.R:
                            CreateLevel(--level);
                            return;
                    }
                    //while (!((Player)field[p.Y, p.X][1]).CanGo()) { Console.ReadKey(true); }
                    
                }
                win = true;
                foreach (Box b in boxesOnMap)
                    if (!(win = b.OnContainer))
                        break;
                if (win)
                {
                    while (!((Player)field[p.Y, p.X][1]).CanGo())
                    { }
                    Block.Clear();
                    ((Player)field[p.Y, p.X][1]).Win();
                    
                    WriteToFile();
                    
                    break;

                }
            }
            Console.ReadKey(true);
            ((Player)field[p.Y, p.X][1]).BreakWin();
            CreateLevel(level);
        }
    }
}
