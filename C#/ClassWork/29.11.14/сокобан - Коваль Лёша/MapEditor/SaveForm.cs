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
    public partial class SaveForm : Form
    {
        ushort lvl;
        public SaveForm()
        {
            InitializeComponent();
            ushort countLevels = 1;
            
            for (byte i = 0; i < Directory.GetFiles(Application.StartupPath + "\\Level", "*.sm").Length; i++)
            {
                if (int.Parse(Path.GetFileNameWithoutExtension(Directory.GetFiles("Level\\", "*.sm")[i]).Replace("level", "")) != -1)
                    ++countLevels;
            }
            numericUpDown1.Value = countLevels;
            numericUpDown1.Maximum = countLevels;
        }

        public ushort Level
        {
            get
            {
                return lvl;
            }
        }
        private void b_ok_Click(object sender, EventArgs e)
        {
            lvl = (ushort)numericUpDown1.Value;
            this.DialogResult = DialogResult.OK;
        }

        private void b_cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }
    }
}
