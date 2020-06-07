using System;
using System.Collections.Generic;
using System.Text;

namespace 原型模式
{
    class Program
    {
        static void Main(string[] args)
        {
            Resume a = new Resume("大鸟");
            a.SetPersonalInfo("男", "29");
            a.SetWorkExperience("1998-2000", "XX公司");

            Resume b = new Resume("大鸟");
            b.SetPersonalInfo("男", "29");
            b.SetWorkExperience("1998-2000", "XX公司");

            Resume c = new Resume("大鸟");
            c.SetPersonalInfo("男", "29");
            c.SetWorkExperience("1998-2000", "XX公司");


            a.Display();
            b.Display();
            c.Display();

            Console.Read();
        }
    }

    //简历
    class Resume
    {
        private string name;
        private string sex;
        private string age;
        private string timeArea;
        private string company;

        public Resume(string name)
        {
            this.name = name;
        }

        //设置个人信息
        public void SetPersonalInfo(string sex, string age)
        {
            this.sex = sex;
            this.age = age;
        }

        //设置工作经历
        public void SetWorkExperience(string timeArea, string company)
        {
            this.timeArea = timeArea;
            this.company = company;
        }

        //显示
        public void Display()
        {
            Console.WriteLine("{0} {1} {2}", name, sex, age);
            Console.WriteLine("工作经历：{0} {1}", timeArea, company);
        }

    }

}
