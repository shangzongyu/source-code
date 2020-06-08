using System;
using System.Collections.Generic;
using System.Text;

namespace 访问者模式
{
    class Program
    {
        static void Main(string[] args)
        {
            ObjectStructure o = new ObjectStructure();
            o.Attach(new Man());
            o.Attach(new Woman());

            Success v1 = new Success();
            o.Display(v1);

            Failing v2 = new Failing();
            o.Display(v2);

            Amativeness v3 = new Amativeness();
            o.Display(v3);

            Marriage v4 = new Marriage();
            o.Display(v4);

            Console.Read();
        }
    }

    //状态
    abstract class Action
    {
        //得到男人结论或反应
        public abstract void GetManConclusion(Man concreteElementA);
        //得到女人结论或反应
        public abstract void GetWomanConclusion(Woman concreteElementB);
    }


    //成功
    class Success : Action
    {
        public override void GetManConclusion(Man concreteElementA)
        {
            Console.WriteLine("{0}{1}时，背后多半有一个伟大的女人。", concreteElementA.GetType().Name, this.GetType().Name);
        }

        public override void GetWomanConclusion(Woman concreteElementB)
        {
            Console.WriteLine("{0}{1}时，背后大多有一个不成功的男人。", concreteElementB.GetType().Name, this.GetType().Name);
        }
    }
    //失败
    class Failing : Action
    {
        public override void GetManConclusion(Man concreteElementA)
        {
            Console.WriteLine("{0}{1}时，闷头喝酒，谁也不用劝。", concreteElementA.GetType().Name, this.GetType().Name);
        }

        public override void GetWomanConclusion(Woman concreteElementB)
        {
            Console.WriteLine("{0}{1}时，眼泪汪汪，谁也劝不了。", concreteElementB.GetType().Name, this.GetType().Name);
        }
    }
    //恋爱
    class Amativeness : Action
    {
        public override void GetManConclusion(Man concreteElementA)
        {
            Console.WriteLine("{0}{1}时，凡事不懂也要装懂。", concreteElementA.GetType().Name, this.GetType().Name);
        }

        public override void GetWomanConclusion(Woman concreteElementB)
        {
            Console.WriteLine("{0}{1}时，遇事懂也装作不懂", concreteElementB.GetType().Name, this.GetType().Name);
        }
    }
    //结婚
    class Marriage : Action
    {
        public override void GetManConclusion(Man concreteElementA)
        {
            Console.WriteLine("{0}{1}时，感慨道：恋爱游戏终结时，‘有妻徒刑’遥无期。", concreteElementA.GetType().Name, this.GetType().Name);
        }

        public override void GetWomanConclusion(Woman concreteElementB)
        {
            Console.WriteLine("{0}{1}时，欣慰曰：爱情长跑路漫漫，婚姻保险保平安。", concreteElementB.GetType().Name, this.GetType().Name);
        }
    }

    //人
    abstract class Person
    {
        //接受
        public abstract void Accept(Action visitor);
    }

    //男人
    class Man : Person
    {
        public override void Accept(Action visitor)
        {
            visitor.GetManConclusion(this);
        }
    }

    //女人
    class Woman : Person
    {
        public override void Accept(Action visitor)
        {
            visitor.GetWomanConclusion(this);
        }
    }
    //对象结构
    class ObjectStructure
    {
        private IList<Person> elements = new List<Person>();

        //增加
        public void Attach(Person element)
        {
            elements.Add(element);
        }
        //移除
        public void Detach(Person element)
        {
            elements.Remove(element);
        }
        //查看显示
        public void Display(Action visitor)
        {
            foreach (Person e in elements)
            {
                e.Accept(visitor);
            }
        }
    }
}
