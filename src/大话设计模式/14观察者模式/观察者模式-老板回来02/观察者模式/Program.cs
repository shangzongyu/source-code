using System;
using System.Collections.Generic;
using System.Text;

namespace 观察者模式
{
    class Program
    {
        static void Main(string[] args)
        {
            //前台小姐童子喆
            Secretary tongzizhe = new Secretary();
            //看股票的同事
            StockObserver tongshi1 = new StockObserver("魏关姹", tongzizhe);
            //看NBA的同事
            NBAObserver tongshi2 = new NBAObserver("易管查", tongzizhe);

            //前台记下了两位同事
            tongzizhe.Attach(tongshi1);
            tongzizhe.Attach(tongshi2);
            //发现老板回来
            tongzizhe.SecretaryAction = "老板回来了！";
            //通知两个同事
            tongzizhe.Notify();


            Console.Read();
        }
    }

    //前台秘书类
    class Secretary
    {
        //同事列表
        private IList<Observer> observers = new List<Observer>();
        private string action;

        //增加
        public void Attach(Observer observer)
        {
            observers.Add(observer);
        }

        //减少
        public void Detach(Observer observer)
        {
            observers.Remove(observer);
        }

        //通知
        public void Notify()
        {
            foreach (Observer o in observers)
                o.Update();
        }

        //前台状态
        public string SecretaryAction
        {
            get { return action; }
            set { action = value; }
        }

    }

    //抽象观察者
    abstract class Observer
    {
        protected string name;
        protected Secretary sub;

        public Observer(string name, Secretary sub)
        {
            this.name = name;
            this.sub = sub;
        }

        public abstract void Update();
    }


    //看股票的同事
    class StockObserver : Observer
    {
        public StockObserver(string name, Secretary sub)
            : base(name, sub)
        {
        }

        public override void Update()
        {
            Console.WriteLine("{0} {1} 关闭股票行情，继续工作！", sub.SecretaryAction, name);
        }
    }

    //看NBA的同事
    class NBAObserver : Observer
    {
        public NBAObserver(string name, Secretary sub)
            : base(name, sub)
        {
        }

        public override void Update()
        {
            Console.WriteLine("{0} {1} 关闭NBA直播，继续工作！", sub.SecretaryAction, name);
        }
    }
}
