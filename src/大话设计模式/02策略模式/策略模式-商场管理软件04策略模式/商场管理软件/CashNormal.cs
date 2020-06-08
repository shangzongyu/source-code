using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
    class CashNormal : CashSuper
    {
        public override double acceptCash(double money)
        {
            return money;
        } 
    }
}
