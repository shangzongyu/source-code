using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace 享元模式
{
    class Program
    {
        static void Main(string[] args)
        {

            WebSiteFactory f = new WebSiteFactory();

            WebSite fx = f.GetWebSiteCategory("产品展示");
            fx.Use(new User("小菜"));

            WebSite fy = f.GetWebSiteCategory("产品展示");
            fy.Use(new User("大鸟"));

            WebSite fz = f.GetWebSiteCategory("产品展示");
            fz.Use(new User("娇娇"));

            WebSite fl = f.GetWebSiteCategory("博客");
            fl.Use(new User("老顽童"));

            WebSite fm = f.GetWebSiteCategory("博客");
            fm.Use(new User("桃谷六仙"));

            WebSite fn = f.GetWebSiteCategory("博客");
            fn.Use(new User("南海鳄神"));

            Console.WriteLine("得到网站分类总数为 {0}", f.GetWebSiteCount());

            //string titleA = "大话设计模式";
            //string titleB = "大话设计模式";

            //Console.WriteLine(Object.ReferenceEquals(titleA, titleB));


            Console.Read();
        }
    }

    //用户
    public class User
    {
        private string name;

        public User(string name)
        {
            this.name = name;
        }

        public string Name
        {
            get { return name; }
        }
    }


    //网站工厂
    class WebSiteFactory
    {
        private Hashtable flyweights = new Hashtable();

        //获得网站分类
        public WebSite GetWebSiteCategory(string key)
        {
            if (!flyweights.ContainsKey(key))
                flyweights.Add(key, new ConcreteWebSite(key));
            return ((WebSite)flyweights[key]);
        }

        //获得网站分类总数
        public int GetWebSiteCount()
        {
            return flyweights.Count;
        }
    }

    //网站
    abstract class WebSite
    {
        public abstract void Use(User user);
    }

    //具体的网站
    class ConcreteWebSite : WebSite
    {
        private string name = "";
        public ConcreteWebSite(string name)
        {
            this.name = name;
        }

        public override void Use(User user)
        {
            Console.WriteLine("网站分类：" + name + " 用户：" + user.Name);
        }
    }

}
