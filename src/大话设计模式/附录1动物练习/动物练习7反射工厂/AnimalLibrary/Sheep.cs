using System;
using System.Collections.Generic;
using System.Text;

namespace AnimalLibrary
{
    public class Sheep : Animal
    {
        public Sheep(string name)
            : base(name)
        {
        }

        protected override string getShoutSound()
        {
            return "咩";
        }
    }
}
