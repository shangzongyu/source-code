using System;
using System.Collections.Generic;
using System.Text;

namespace 动物练习
{
    class Animal
    {
        string name = "";
        protected Animal(string name)
        {
            this.name = name;
        }

        public Animal()
        {
            this.name = "无名";
        }


        int shoutNum = 3;

        public int ShoutNum
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

        protected virtual string getShoutSound()
        {
            return "";
        }
    }
}
