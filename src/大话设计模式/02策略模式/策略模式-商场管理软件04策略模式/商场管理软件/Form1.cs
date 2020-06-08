using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;

namespace 商场管理软件
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        double total = 0.0d;//用于总计
        private void btnOk_Click(object sender, EventArgs e)
        {
            CashContext cc = null;
            switch (cbxType.SelectedItem.ToString())
            {
                case "正常收费":
                    cc = new CashContext(new CashNormal());
                    break;
                case "满300返100":
                    cc = new CashContext(new CashReturn("300", "100"));
                    break;
                case "打8折":
                    cc = new CashContext(new CashRebate("0.8"));
                    break;
            }

            double totalPrices = 0d;
            totalPrices = cc.GetResult(Convert.ToDouble(txtPrice.Text) * Convert.ToDouble(txtNum.Text));
            total = total + totalPrices;
            lbxList.Items.Add("单价：" + txtPrice.Text + " 数量：" + txtNum.Text + " " + cbxType.SelectedItem + " 合计：" + totalPrices.ToString());
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

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}