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

        DataSet ds;//用于存放配置文件信息
        double total = 0.0d;//用于总计

        private void Form1_Load(object sender, EventArgs e)
        {
            //读配置文件
            ds = new DataSet();
            ds.ReadXml(Application.StartupPath + "\\CashAcceptType.xml");
            //将读取到的记录绑定到下拉列表框中
            foreach (DataRowView dr in ds.Tables[0].DefaultView)
            {
                cbxType.Items.Add(dr["name"].ToString());
            }
            cbxType.SelectedIndex = 0;
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            CashContext cc = new CashContext();
            //根据用户的选项，查询用户选择项的相关行
            DataRow dr = ((DataRow[])ds.Tables[0].Select("name='" + cbxType.SelectedItem.ToString()+"'"))[0];
            //声明一个参数的对象数组
            object[] args =null;
            //若有参数，则将其分割成字符串数组，用于实例化时所用的参数
            if (dr["para"].ToString() != "")
                args = dr["para"].ToString().Split(',');
            //通过反射实例化出相应的算法对象
            cc.setBehavior((CashSuper)Assembly.Load("商场管理软件").CreateInstance("商场管理软件." + dr["class"].ToString(), false, BindingFlags.Default, null, args, null, null));
            
            double totalPrices = 0d;
            totalPrices = cc.GetResult(Convert.ToDouble(txtPrice.Text) * Convert.ToDouble(txtNum.Text));
            total = total + totalPrices;
            lbxList.Items.Add("单价：" + txtPrice.Text + " 数量：" + txtNum.Text + " "+cbxType.SelectedItem+ " 合计：" + totalPrices.ToString());
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