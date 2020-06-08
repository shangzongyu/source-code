using System;
using System.Collections.Generic;
using System.Text;

namespace 桥接模式
{
    class Program
    {
        static void Main(string[] args)
        {
            HandsetBrand ab;
            ab = new HandsetBrandMAddressList();
            ab.Run();

            ab = new HandsetBrandMGame();
            ab.Run();

            ab = new HandsetBrandNAddressList();
            ab.Run();

            ab = new HandsetBrandNGame();
            ab.Run();

            Console.Read();
        }
    }

    //手机品牌
    class HandsetBrand
    {
        public virtual void Run()
        {
        }
    }
    //手机品牌M
    class HandsetBrandM : HandsetBrand
    {

    }
    //手机品牌N
    class HandsetBrandN : HandsetBrand
    {

    }
    //手机品牌M的游戏
    class HandsetBrandMGame : HandsetBrandM
    {
        public override void Run()
        {
            Console.WriteLine("运行M品牌手机游戏");
        }
    }
    //手机品牌N的游戏
    class HandsetBrandNGame : HandsetBrandN
    {
        public override void Run()
        {
            Console.WriteLine("运行N品牌手机游戏");
        }
    }
    //手机品牌M的通讯录
    class HandsetBrandMAddressList : HandsetBrandM
    {
        public override void Run()
        {
            Console.WriteLine("运行M品牌手机通讯录");
        }
    }
    //手机品牌N的通讯录
    class HandsetBrandNAddressList : HandsetBrandN
    {
        public override void Run()
        {
            Console.WriteLine("运行N品牌手机通讯录");
        }
    }

}
