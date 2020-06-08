using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
    //打折收费，继承CashSuper
    class CashRebate : CashSuper
    {
        private double moneyRebate = 1d;
        //初始化时，必需要输入折扣率,如八折，就是0.8
        public CashRebate(string moneyRebate)
        {
            this.moneyRebate = double.Parse(moneyRebate);
        }

        public override double acceptCash(double money)
        {
            return money * moneyRebate;
        }
    }
}
