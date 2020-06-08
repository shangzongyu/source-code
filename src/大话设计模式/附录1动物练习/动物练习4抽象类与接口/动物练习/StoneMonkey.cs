using System;
using System.Collections.Generic;
using System.Text;

namespace 动物练习
{
    class StoneMonkey:Monkey,IChange
    {
        public StoneMonkey()
            : base()
        { }
        public StoneMonkey(string name)
            : base(name)
        {
        }

        public string ChangeThing(string thing)
        {
            return base.Shout() + " 我会七十二变，可变出" + thing;
        }
    }
}
