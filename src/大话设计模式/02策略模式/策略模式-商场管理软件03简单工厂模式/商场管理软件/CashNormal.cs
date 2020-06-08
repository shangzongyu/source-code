using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
    //正常收费，继承CashSuper
    class CashNormal : CashSuper
    {
        public override double acceptCash(double money)
        {
            return money;
        }
    }

}
