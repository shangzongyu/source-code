using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
    //收费策略Context
class CashContext
{
    //声明一个现金收费父类对象
    private CashSuper cs;

    //设置策略行为，参数为具体的现金收费子类（正常，打折或返利）
    public CashContext(CashSuper csuper)
    {
        this.cs = csuper;
    }

    //得到现金促销计算结果（利用了多态机制，不同的策略行为导致不同的结果）
    public double GetResult(double money)
    {
        return cs.acceptCash(money);
    }
}
}
