using System;
using System.Collections.Generic;
using System.Text;

namespace 商场管理软件
{
//现金收取父类
abstract class CashSuper
{
    //抽象方法：收取现金，参数为原价，返回为当前价
    public abstract double acceptCash(double money);
}

}
