using System;
using System.Collections.Generic;
using System.Text;

namespace 桥接模式
{
    class Program
    {
        static void Main(string[] args)
        {
            HandsetSoft ab;
            ab = new HandsetBrandMGame();
            ab.Run();

            ab = new HandsetBrandNGame();
            ab.Run();

            ab = new HandsetBrandMAddressList();
            ab.Run();

            ab = new HandsetBrandNAddressList();
            ab.Run();

            Console.Read();
        }
    }

    //手机软件
    class HandsetSoft
    {
        public virtual void Run()
        {
        }
    }
    //通讯录
    class HandsetAddressList : HandsetSoft
    {

    }
    //游戏
    class HandsetGame : HandsetSoft
    {

    }
    //手机品牌M的游戏
    class HandsetBrandMGame : HandsetGame
    {
        public override void Run()
        {
            Console.WriteLine("运行M品牌手机游戏");
        }
    }
    //手机品牌N的游戏
    class HandsetBrandNGame : HandsetGame
    {
        public override void Run()
        {
            Console.WriteLine("运行N品牌手机游戏");
        }
    }
    //手机品牌M的通讯录
    class HandsetBrandMAddressList : HandsetAddressList
    {
        public override void Run()
        {
            Console.WriteLine("运行M品牌手机通讯录");
        }
    }
    //手机品牌N的通讯录
    class HandsetBrandNAddressList : HandsetAddressList
    {
        public override void Run()
        {
            Console.WriteLine("运行N品牌手机通讯录");
        }
    }

}
