using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 建造者模式
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {

            Pen p = new Pen(Color.Yellow);

            Graphics gThin = pictureBox1.CreateGraphics();

            PersonThinBuilder ptb = new PersonThinBuilder(gThin, p);
            ptb.Build();

            Graphics gFat = pictureBox2.CreateGraphics();

            PersonFatBuilder pfb = new PersonFatBuilder(gFat, p);
            pfb.Build();
        }
    }
}