using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
    //现金收取工厂
class CashContext
{
    CashSuper cs = null;

    //根据条件返回相应的对象
    public CashContext(string type)
    {
        switch (type)
        {
            case "正常收费":
                CashNormal cs0 = new CashNormal();
                cs = cs0;
                break;
            case "满300返100":
                CashReturn cr1 = new CashReturn("300", "100");
                cs = cr1;
                break;
            case "打8折":
                CashRebate cr2 = new CashRebate("0.8");
                cs = cr2;
                break;
        }
    }

    public double GetResult(double money)
    {
        return cs.acceptCash(money);
    }
}
}
