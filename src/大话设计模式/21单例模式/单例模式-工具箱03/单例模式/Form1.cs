using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 单例模式
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.IsMdiContainer = true;
        }


        private void ToolStripMenuItemToolbox_Click(object sender, EventArgs e)
        {
            FormToolbox.GetInstance().Show();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            FormToolbox.GetInstance().Show();
        }
    }
}