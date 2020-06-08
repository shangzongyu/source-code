using System;
using System.Collections.Generic;
using System.Text;

namespace 访问者模式
{
    class Program
    {
        static void Main(string[] args)
        {
            IList<Person> persons = new List<Person>();

            Person man1 = new Man();
            man1.Action = "成功";
            persons.Add(man1);
            Person woman1 = new Woman();
            woman1.Action = "成功";
            persons.Add(woman1);

            Person man2 = new Man();
            man2.Action = "失败";
            persons.Add(man2);
            Person woman2 = new Woman();
            woman2.Action = "失败";
            persons.Add(woman2);

            Person man3 = new Man();
            man3.Action = "恋爱";
            persons.Add(man3);
            Person woman3 = new Woman();
            woman3.Action = "恋爱";
            persons.Add(woman3);

            foreach (Person item in persons)
            {
                item.GetConclusion();
            }

            Console.Read();
        }
    }

    //人
    abstract class Person
    {
        protected string action;
        public string Action
        {
            get { return action; }
            set { action = value; }
        }
        //得到结论或反应
        public abstract void GetConclusion();
    }
    //男人
    class Man : Person
    {
        //得到结论或反应
        public override void GetConclusion()
        {
            if (action == "成功")
            {
                Console.WriteLine("{0}{1}时，背后多半有一个伟大的女人。", this.GetType().Name, action);
            }
            else if (action == "失败")
            {
                Console.WriteLine("{0}{1}时，闷头喝酒，谁也不用劝。", this.GetType().Name, action);
            }
            else if (action == "恋爱")
            {
                Console.WriteLine("{0}{1}时，凡事不懂也要装懂。", this.GetType().Name, action);
            }
        }
    }
    //女人
    class Woman : Person
    {
        //得到结论或反应
        public override void GetConclusion()
        {
            if (action == "成功")
            {
                Console.WriteLine("{0}{1}时，背后大多有一个不成功的男人。", this.GetType().Name, action);
            }
            else if (action == "失败")
            {
                Console.WriteLine("{0}{1}时，眼泪汪汪，谁也劝不了。", this.GetType().Name, action);
            }
            else if (action == "恋爱")
            {
                Console.WriteLine("{0}{1}时，遇事懂也装作不懂。", this.GetType().Name, action);
            }
        }
    }
}
