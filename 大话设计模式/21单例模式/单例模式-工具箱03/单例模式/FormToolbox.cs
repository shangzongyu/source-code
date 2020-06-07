using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 单例模式
{
public partial class FormToolbox : Form
{
    private static FormToolbox ftb = null;

    private  FormToolbox()
    {
        InitializeComponent();
    }

    public static FormToolbox GetInstance()
    {
        if (ftb == null || ftb.IsDisposed)
        {
            ftb = new FormToolbox();
            ftb.MdiParent=Form1.ActiveForm;
        }
        return ftb;
    }
}
}