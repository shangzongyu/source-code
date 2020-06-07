using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 商场管理软件
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //声明一个double变量total来计算总计
        double total = 0.0d;
        private void btnOk_Click(object sender, EventArgs e)
        {
            //声明一个double变量totalPrices来计算每个商品的单价（txtPrice）*数量(txtNum)后的合计
            double totalPrices=Convert.ToDouble(txtPrice.Text) * Convert.ToDouble(txtNum.Text);
            //将每个商品合计计入总计
            total = total + totalPrices;
            //在列表框中显示信息
            lbxList.Items.Add("单价："+txtPrice.Text+" 数量："+txtNum.Text+" 合计："+totalPrices.ToString());
            //在lblResult标签上显示总计数
            lblResult.Text = total.ToString();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            total = 0d;
            txtPrice.Text = "0.00";
            txtNum.Text = "1";
            lbxList.Items.Clear();
            lblResult.Text = "0.00";
        }
    }
}