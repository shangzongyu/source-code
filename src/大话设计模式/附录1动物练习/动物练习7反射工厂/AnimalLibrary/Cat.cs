using System;
using System.Collections.Generic;
using System.Text;

namespace AnimalLibrary
{
    public class Cat : Animal
    {
        public Cat(string name)
            : base(name)
        {
        }

        protected override string getShoutSound()
        {
            return "喵";
        }
    }
}
