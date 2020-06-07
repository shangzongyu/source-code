using System;
using System.Collections.Generic;
using System.Text;

namespace 动物练习
{
    class Program
    {
        static void Main(string[] args)
        {
            Cat cat = new Cat("Tom");
            Mouse mouse1 = new Mouse("Jerry");
            Mouse mouse2 = new Mouse("Jack");
            cat.CatShout += new Cat.CatShoutEventHandler(mouse1.Run);
            cat.CatShout += new Cat.CatShoutEventHandler(mouse2.Run);

            cat.Shout();

            Console.Read();
        }
    }

    //无参数委托事件
    //class Cat
    //{
    //    private string name;
    //    public Cat(string name)
    //    {
    //        this.name = name;
    //    }

    //    public delegate void CatShoutEventHandler();
    //    public event CatShoutEventHandler CatShout;

    //    public void Shout()
    //    {
    //        Console.WriteLine("喵,我是{0}.", name);

    //        if (CatShout != null)
    //        {
    //            CatShout();
    //        }
    //    }
    //}

    //class Mouse
    //{
    //    private string name;
    //    public Mouse(string name)
    //    {
    //        this.name = name;
    //    }

    //    public void Run()
    //    {
    //        Console.WriteLine("老猫来了，{0}快跑！", name);
    //    }
    //}

    //有参数委托事件
    class Cat
    {
        private string name;
        public Cat(string name)
        {
            this.name = name;
        }

        public delegate void CatShoutEventHandler(object sender, CatShoutEventArgs args);
        public event CatShoutEventHandler CatShout;

        public void Shout()
        {
            Console.WriteLine("喵,我是{0}.", name);

            if (CatShout != null)
            {
                CatShoutEventArgs e = new CatShoutEventArgs();
                e.Name = this.name;
                CatShout(this, e);
            }
        }
    }

    public class CatShoutEventArgs : EventArgs
    {
        private string name;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    }

    class Mouse
    {
        private string name;
        public Mouse(string name)
        {
            this.name = name;
        }

        public void Run(object sender, CatShoutEventArgs args)
        {
            Console.WriteLine("老猫{0}来了，{1}快跑！", args.Name, name);
        }
    }
}
