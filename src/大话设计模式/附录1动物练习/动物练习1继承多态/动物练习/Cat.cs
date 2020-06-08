using System;
using System.Collections.Generic;
using System.Text;

namespace 动物练习
{
class Cat : Animal
{
    public Cat()
        : base()
    { }

    public Cat(string name)
        : base(name)
    { }

    public override string Shout()
    {
        string result = "";
        for (int i = 0; i < shoutNum; i++)
            result += "喵 ";

        return "我的名字叫" + name + " " + result;
    }
}
}
