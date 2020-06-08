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
        
        private FormToolbox ftb;

        private void ToolStripMenuItemToolbox_Click(object sender, EventArgs e)
        {
            openToolbox();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            openToolbox();
        }

        private void openToolbox()
        {
            if (ftb == null || ftb.IsDisposed)
            {
                ftb = new FormToolbox();
                ftb.MdiParent = this;
                ftb.Show();
            }
        }

       
    }
}