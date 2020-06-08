using System;
using System.Collections.Generic;
using System.Text;

namespace 命令模式
{
    class Program
    {
        static void Main(string[] args)
        {
            Barbecuer boy = new Barbecuer();

            boy.BakeMutton();
            boy.BakeMutton();
            boy.BakeMutton();
            boy.BakeChickenWing();
            boy.BakeMutton();
            boy.BakeMutton();
            boy.BakeChickenWing();

            Console.Read();
        }
    }
    //烤肉串者
    public class Barbecuer
    {
        //烤羊肉
        public void BakeMutton()
        {
            Console.WriteLine("烤羊肉串!");
        }
        //烤鸡翅
        public void BakeChickenWing()
        {
            Console.WriteLine("烤鸡翅!");
        }
    }

}
