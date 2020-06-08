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
            PersonDirector pdThin = new PersonDirector("Thin",pictureBox1.CreateGraphics(),p);
            pdThin.CreatePerson();

            PersonDirector pdFat = new PersonDirector("Fat", pictureBox2.CreateGraphics(), p);
            pdFat.CreatePerson();
        }
    }
}