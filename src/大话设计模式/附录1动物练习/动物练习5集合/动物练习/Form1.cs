using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace 动物练习
{
public partial class Form1 : Form
{
    //IList arrayAnimal = new ArrayList();
    IList<Animal> arrayAnimal;

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

        arrayAnimal = new List<Animal>();
        arrayAnimal.Add(AnimalFactory.CreateAnimal("猫", "小花", 1));
        ((Animal)arrayAnimal[0]).ShoutNum = 5;
        arrayAnimal.Add(AnimalFactory.CreateAnimal("狗", "阿毛", 2));
        arrayAnimal.Add(AnimalFactory.CreateAnimal("狗", "小黑", 3));
        arrayAnimal.Add(AnimalFactory.CreateAnimal("猫", "娇娇", 4));
        arrayAnimal.Add(AnimalFactory.CreateAnimal("猫", "咪咪", 5));
        MessageBox.Show(arrayAnimal.Count.ToString());

    }

    private void button5_Click(object sender, EventArgs e)
    {
        arrayAnimal.Add(AnimalFactory.CreateAnimal(listBox1.SelectedItem.ToString(), "小" + listBox1.SelectedItem.ToString(), 3));
    }

    private void button6_Click(object sender, EventArgs e)
    {
        IChange mcat = new MachineCat("叮噹");
        MessageBox.Show(mcat.ChangeThing("各种各样的东西！"));
    }

private void button7_Click(object sender, EventArgs e)
{
    arrayAnimal.RemoveAt(1);
    arrayAnimal.RemoveAt(2);

}
}
}