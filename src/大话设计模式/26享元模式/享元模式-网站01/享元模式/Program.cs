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


            WebSite fx = new WebSite("产品展示");
            fx.Use();

            WebSite fy = new WebSite("产品展示");
            fy.Use();

            WebSite fz = new WebSite("产品展示");
            fz.Use();

            WebSite fl = new WebSite("博客");
            fl.Use();

            WebSite fm = new WebSite("博客");
            fm.Use();

            WebSite fn = new WebSite("博客");
            fn.Use();


            Console.Read();
        }
    }

    //网站
    class WebSite
    {
        private string name = "";
        public WebSite(string name)
        {
            this.name = name;
        }

        public void Use()
        {
            Console.WriteLine("网站分类：" + name);
        }
    }

}
