using System;
using System.Collections.Generic;
using System.Text;

namespace AnimalLibrary
{
    public abstract class Animal
    {
        string name = "";
        public Animal(string name)
        {
            this.name = name;
        }

        int shoutNum = 3;

        protected internal int ShoutNum
        {
            get
            {
                return shoutNum;
            }
            set
            {
                shoutNum = value;
            }
        }

        public string Shout()
        {
            string result = "";
            for (int i = 0; i < shoutNum; i++)
                result += getShoutSound() + "，";

            return "我的名字叫" + name + " " + result;
        }

        protected abstract string getShoutSound();

    }
}
