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
            ab = new HandsetBrandN();

            ab.SetHandsetSoft(new HandsetGame());
            ab.Run();

            ab.SetHandsetSoft(new HandsetAddressList());
            ab.Run();

            ab = new HandsetBrandM();

            ab.SetHandsetSoft(new HandsetGame());
            ab.Run();

            ab.SetHandsetSoft(new HandsetAddressList());
            ab.Run();

            Console.Read();
        }
    }

    //手机品牌
    abstract class HandsetBrand
    {
        protected HandsetSoft soft;

        //设置手机软件
        public void SetHandsetSoft(HandsetSoft soft)
        {
            this.soft = soft;
        }
        //运行
        public abstract void Run();
        

    }

    //手机品牌N
    class HandsetBrandN : HandsetBrand
    {
        public override void Run()
        {
            soft.Run();
        }
    }

    //手机品牌M
    class HandsetBrandM : HandsetBrand
    {
        public override void Run()
        {
            soft.Run();
        }
    }

    //手机品牌S
    class HandsetBrandS : HandsetBrand
    {
        public override void Run()
        {
            soft.Run();
        }
    }


    //手机软件
    abstract class HandsetSoft
    {

        public abstract void Run();
    }

    //手机游戏
    class HandsetGame : HandsetSoft
    {
        public override void Run()
        {
            Console.WriteLine("运行手机游戏");
        }
    }

    //手机通讯录
    class HandsetAddressList : HandsetSoft
    {
        public override void Run()
        {
            Console.WriteLine("运行手机通讯录");
        }
    }

    //手机MP3播放
    class HandsetMP3 : HandsetSoft
    {
        public override void Run()
        {
            Console.WriteLine("运行手机MP3播放");
        }
    }

}
