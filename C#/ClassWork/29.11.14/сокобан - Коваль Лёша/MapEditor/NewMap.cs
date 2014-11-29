using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class NewMap : Form
    {
        private byte width;
        private byte height;
        public NewMap()
        {
            InitializeComponent();
        }

        private void b_cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }

        private void b_ok_Click(object sender, EventArgs e)
        {
            width = (byte)numericUpDown1.Value;
            height = (byte)numericUpDown2.Value;
            this.DialogResult = DialogResult.OK;
        }
        public byte ImageWidth
        {
            get
            {
                return width;
            }
        }
        public byte ImageHeight
        {
            get
            {
                return height;
            }
        }
    }
}
