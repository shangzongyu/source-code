using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 动物练习
{
    public partial class Form1 : Form
    {
        Animal[] arrayAnimal;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Animal cat = new Cat("小咪");
            cat.ShoutNum = 5;
            MessageBox.Show(cat.Shout());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Animal dog = new Dog("旺财");
            dog.ShoutNum = 3;
            MessageBox.Show(dog.Shout());
        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (Animal item in arrayAnimal)
            {
                MessageBox.Show(item.Shout());
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            arrayAnimal = new Animal[5];
            arrayAnimal[0] = new Cat("小花");
            arrayAnimal[0].ShoutNum = 10;
            arrayAnimal[1] = new Dog("阿毛");
            arrayAnimal[2] = new Dog("小黑");
            arrayAnimal[3] = new Cat("娇娇");
            arrayAnimal[4] = new Cat("咪咪");
        }
    }
}