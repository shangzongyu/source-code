using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
    class CashContext
    {
        private CashSuper cs;

        public void setBehavior(CashSuper csuper)
        {
            this.cs = csuper;
        }

        public double GetResult(double money)
        {
            return cs.acceptCash(money);
        }
    }
}
