using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using OperationLibrary;

namespace 计算器
{
    /// <summary>
    /// 面向对象编程
    /// 1、加运算类
    /// 2、加运算子类
    /// 3、加运算类工厂
    /// 4、更改Form1
    public partial class Form1 : Form
    {
        bool bOperate = false;
        Operation oper;

        public Form1()
        {
            InitializeComponent();
        }

        private void button0_Click(object sender, EventArgs e)
        {
            if (bOperate)
            {
                txtShow.Text = "";
                bOperate = false;
            }
            
            string number = ((Button)sender).Text;

            txtShow.Text = Operation.checkNumberInput(txtShow.Text, number);
            
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            txtShow.Text = "";
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            if (txtShow.Text != "")
            {
                oper = OperationFactory.createOperate(((Button)sender).Text);
                
                oper.NumberA = Convert.ToDouble(txtShow.Text);
                
                bOperate = true;
            }
        }

        private void buttonEqual_Click(object sender, EventArgs e)
        {
            if (txtShow.Text != "")
            {
                if (((Button)sender).Text != "=")
                {
                    oper = OperationFactory.createOperate(((Button)sender).Text);
                }
                
                oper.NumberB = Convert.ToDouble(txtShow.Text);

                
                txtShow.Text = oper.GetResult().ToString();
                bOperate = true;
            }
        }

 
    }
}