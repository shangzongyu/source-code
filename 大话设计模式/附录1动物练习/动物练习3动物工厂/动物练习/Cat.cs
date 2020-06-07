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

        public Cat(string name):base(name)
        {
        }

        protected override string getShoutSound()
        {
            return "喵";
        }
    }
}
