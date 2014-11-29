namespace MapEditor
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.pb_player = new System.Windows.Forms.PictureBox();
            this.pb_box_cont = new System.Windows.Forms.PictureBox();
            this.pb_container = new System.Windows.Forms.PictureBox();
            this.pb_box = new System.Windows.Forms.PictureBox();
            this.pb_wall = new System.Windows.Forms.PictureBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.mi_file = new System.Windows.Forms.ToolStripMenuItem();
            this.mi_new = new System.Windows.Forms.ToolStripMenuItem();
            this.mi_open = new System.Windows.Forms.ToolStripMenuItem();
            this.mi_save = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.mi_quit = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb_player)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_box_cont)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_container)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_box)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_wall)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.WindowText;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.pb_player);
            this.panel1.Controls.Add(this.pb_box_cont);
            this.panel1.Controls.Add(this.pb_container);
            this.panel1.Controls.Add(this.pb_box);
            this.panel1.Controls.Add(this.pb_wall);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.Location = new System.Drawing.Point(0, 24);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(32, 188);
            this.panel1.TabIndex = 0;
            // 
            // pb_player
            // 
            this.pb_player.Dock = System.Windows.Forms.DockStyle.Top;
            this.pb_player.Location = new System.Drawing.Point(0, 120);
            this.pb_player.Name = "pb_player";
            this.pb_player.Size = new System.Drawing.Size(30, 30);
            this.pb_player.TabIndex = 3;
            this.pb_player.TabStop = false;
            this.pb_player.Tag = MapEditor.Form1.BlockState.Char;
            this.pb_player.MouseClick += new System.Windows.Forms.MouseEventHandler(this.itemChoose_MouseClick);
            // 
            // pb_box_cont
            // 
            this.pb_box_cont.Dock = System.Windows.Forms.DockStyle.Top;
            this.pb_box_cont.Location = new System.Drawing.Point(0, 90);
            this.pb_box_cont.Name = "pb_box_cont";
            this.pb_box_cont.Size = new System.Drawing.Size(30, 30);
            this.pb_box_cont.TabIndex = 4;
            this.pb_box_cont.TabStop = false;
            this.pb_box_cont.Tag = MapEditor.Form1.BlockState.BoxContainer;
            this.pb_box_cont.MouseClick += new System.Windows.Forms.MouseEventHandler(this.itemChoose_MouseClick);
            // 
            // pb_container
            // 
            this.pb_container.Dock = System.Windows.Forms.DockStyle.Top;
            this.pb_container.Location = new System.Drawing.Point(0, 60);
            this.pb_container.Name = "pb_container";
            this.pb_container.Size = new System.Drawing.Size(30, 30);
            this.pb_container.TabIndex = 2;
            this.pb_container.TabStop = false;
            this.pb_container.Tag = MapEditor.Form1.BlockState.Container;
            this.pb_container.MouseClick += new System.Windows.Forms.MouseEventHandler(this.itemChoose_MouseClick);
            // 
            // pb_box
            // 
            this.pb_box.Dock = System.Windows.Forms.DockStyle.Top;
            this.pb_box.Location = new System.Drawing.Point(0, 30);
            this.pb_box.Name = "pb_box";
            this.pb_box.Size = new System.Drawing.Size(30, 30);
            this.pb_box.TabIndex = 1;
            this.pb_box.TabStop = false;
            this.pb_box.Tag = MapEditor.Form1.BlockState.Box;
            this.pb_box.MouseClick += new System.Windows.Forms.MouseEventHandler(this.itemChoose_MouseClick);
            // 
            // pb_wall
            // 
            this.pb_wall.Dock = System.Windows.Forms.DockStyle.Top;
            this.pb_wall.Location = new System.Drawing.Point(0, 0);
            this.pb_wall.Name = "pb_wall";
            this.pb_wall.Size = new System.Drawing.Size(30, 30);
            this.pb_wall.TabIndex = 0;
            this.pb_wall.TabStop = false;
            this.pb_wall.Tag = MapEditor.Form1.BlockState.Wall;
            this.pb_wall.MouseClick += new System.Windows.Forms.MouseEventHandler(this.itemChoose_MouseClick);
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.BackColor = System.Drawing.SystemColors.WindowText;
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(32, 24);
            this.panel2.Name = "panel2";
            this.panel2.Padding = new System.Windows.Forms.Padding(5);
            this.panel2.Size = new System.Drawing.Size(242, 188);
            this.panel2.TabIndex = 1;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mi_file});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(274, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // mi_file
            // 
            this.mi_file.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mi_new,
            this.mi_open,
            this.mi_save,
            this.toolStripSeparator1,
            this.mi_quit});
            this.mi_file.Name = "mi_file";
            this.mi_file.Size = new System.Drawing.Size(48, 20);
            this.mi_file.Text = "&Файл";
            // 
            // mi_new
            // 
            this.mi_new.Name = "mi_new";
            this.mi_new.Size = new System.Drawing.Size(189, 22);
            this.mi_new.Text = "Создать новую карту";
            this.mi_new.Click += new System.EventHandler(this.mi_new_Click);
            // 
            // mi_open
            // 
            this.mi_open.Name = "mi_open";
            this.mi_open.Size = new System.Drawing.Size(189, 22);
            this.mi_open.Text = "Открыть...";
            this.mi_open.Click += new System.EventHandler(this.mi_open_Click);
            // 
            // mi_save
            // 
            this.mi_save.Name = "mi_save";
            this.mi_save.Size = new System.Drawing.Size(189, 22);
            this.mi_save.Text = "Сохранить...";
            this.mi_save.Click += new System.EventHandler(this.mi_save_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(186, 6);
            // 
            // mi_quit
            // 
            this.mi_quit.Name = "mi_quit";
            this.mi_quit.Size = new System.Drawing.Size(189, 22);
            this.mi_quit.Text = "Выход";
            this.mi_quit.Click += new System.EventHandler(this.mi_quit_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "Карты Сокобана|*.sm";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(274, 212);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.MaximumSize = new System.Drawing.Size(626, 544);
            this.MinimumSize = new System.Drawing.Size(242, 224);
            this.Name = "Form1";
            this.Text = "Редактор карт Сокобана";
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pb_player)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_box_cont)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_container)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_box)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_wall)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pb_player;
        private System.Windows.Forms.PictureBox pb_container;
        private System.Windows.Forms.PictureBox pb_box;
        private System.Windows.Forms.PictureBox pb_wall;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem mi_file;
        private System.Windows.Forms.ToolStripMenuItem mi_new;
        private System.Windows.Forms.ToolStripMenuItem mi_open;
        private System.Windows.Forms.ToolStripMenuItem mi_save;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem mi_quit;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.PictureBox pb_box_cont;
    }
}

