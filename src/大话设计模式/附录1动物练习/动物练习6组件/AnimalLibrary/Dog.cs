using System;
using System.Collections.Generic;
using System.Text;

namespace AnimalLibrary
{
    public class Dog : Animal
    {
        public Dog(string name)
            : base(name)
        {
        }

        protected override string getShoutSound()
        {
            return "汪";
        }
    }
}
