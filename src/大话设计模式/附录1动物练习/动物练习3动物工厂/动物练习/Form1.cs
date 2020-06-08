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
        Animal[] arrayAnimal = new Animal[10];
        int index = 0;  

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
                if (item!=null)
                    MessageBox.Show(item.Shout());
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            arrayAnimal[0] = AnimalFactory.CreateAnimal("猫", "小花", 1);
            arrayAnimal[1] = AnimalFactory.CreateAnimal("狗", "阿毛", 2);
            arrayAnimal[2] = AnimalFactory.CreateAnimal("狗", "小黑", 3);
            arrayAnimal[3] = AnimalFactory.CreateAnimal("猫", "娇娇", 4);
            arrayAnimal[4] = AnimalFactory.CreateAnimal("猫", "咪咪", 5);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (index < 10)
            {
                arrayAnimal[index] = AnimalFactory.CreateAnimal(listBox1.SelectedItem.ToString(), "小" + listBox1.SelectedItem.ToString(), 3);
                index++;
            }
        }
    }
}