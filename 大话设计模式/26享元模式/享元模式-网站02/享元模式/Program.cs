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
            fx.Use();

            WebSite fy = f.GetWebSiteCategory("产品展示");
            fy.Use();

            WebSite fz = f.GetWebSiteCategory("产品展示");
            fz.Use();

            WebSite fl = f.GetWebSiteCategory("博客");
            fl.Use();

            WebSite fm = f.GetWebSiteCategory("博客");
            fm.Use();

            WebSite fn = f.GetWebSiteCategory("博客");
            fn.Use();

            Console.WriteLine("网站分类总数为 {0}", f.GetWebSiteCount());

            Console.Read();
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
        public abstract void Use();
    }

    //具体的网站
    class ConcreteWebSite : WebSite
    {
        private string name = "";
        public ConcreteWebSite(string name)
        {
            this.name = name;
        }

        public override void Use()
        {
            Console.WriteLine("网站分类：" + name);
        }
    }

}
