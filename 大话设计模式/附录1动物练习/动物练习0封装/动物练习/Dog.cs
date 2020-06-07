using System;
using System.Collections.Generic;
using System.Text;

namespace 动物练习
{
    class Dog
    {
        private string name = "";
        public Dog(string name)
        {
            this.name = name;
        }

        public Dog()
        {
            this.name = "无名";
        }

        private int shoutNum = 3;
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
            {
                result += "汪　";
            }
            return "我的名字叫" + name + " " + result;
        }
    }

}
