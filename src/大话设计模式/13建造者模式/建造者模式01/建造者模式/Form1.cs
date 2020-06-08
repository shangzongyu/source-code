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
            
            gThin.DrawEllipse(p, 50, 20, 30, 30);
            gThin.DrawRectangle(p, 60, 50, 10, 50);
            gThin.DrawLine(p, 60, 50, 40, 100);
            gThin.DrawLine(p, 70, 50, 90, 100);
            gThin.DrawLine(p, 60, 100, 45, 150);
            gThin.DrawLine(p, 70, 100, 85, 150);

            Graphics gFat = pictureBox2.CreateGraphics();

            gFat.DrawEllipse(p, 50, 20, 30, 30);
            gFat.DrawEllipse(p, 45, 50, 40, 50);
            gFat.DrawLine(p, 50, 50, 30, 100);
            gFat.DrawLine(p, 80, 50, 100, 100);
            gFat.DrawLine(p, 60, 100, 45, 150);
            gFat.DrawLine(p, 70, 100, 85, 150);


        }
    }
}