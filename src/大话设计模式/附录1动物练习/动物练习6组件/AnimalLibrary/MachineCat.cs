using System;
using System.Collections.Generic;
using System.Text;

namespace AnimalLibrary
{
    public class MachineCat : Cat, IChange
    {
        public MachineCat(string name)
            : base(name)
        {
        }

        public string ChangeThing(string thing)
        {
            return base.Shout() + " 我可变出：" + thing;
        }
    }
}
