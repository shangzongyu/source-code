using System;
using System.Collections.Generic;
using System.Text;

namespace 适配器模式
{
    class Program
    {
        static void Main(string[] args)
        {
            Target target = new Adapter();
            target.Request();

            Console.Read();

        }
    }

    class Target
    {
        public virtual void Request()
        {
            Console.WriteLine("普通请求");
        }
    }

    class Adaptee
    {
        public void SpecificRequest()
        {
            Console.WriteLine("特殊请求");
        }
    }

    class Adapter : Target
    {
        private Adaptee adaptee = new Adaptee();

        public override void Request()
        {
            adaptee.SpecificRequest();
        }
    }
}
