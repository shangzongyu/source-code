using System;
using System.Collections.Generic;
using System.Text;

namespace 工厂方法_雷锋工厂
{
    class Program
    {
        static void Main(string[] args)
        {

            //
            //基本方式:薛磊风代表大学生学习雷锋
            LeiFeng xueleifeng = new Undergraduate();

            xueleifeng.BuyRice();
            xueleifeng.Sweep();
            xueleifeng.Wash();


            LeiFeng student1 = new Undergraduate();
            student1.BuyRice();
            LeiFeng student2 = new Undergraduate();
            student2.Sweep();
            LeiFeng student3 = new Undergraduate();
            student3.Wash();



            //简单工厂模式
            LeiFeng studentA = SimpleFactory.CreateLeiFeng("学雷锋的大学生");
            studentA.BuyRice();
            LeiFeng studentB = SimpleFactory.CreateLeiFeng("学雷锋的大学生");
            studentB.Sweep();
            LeiFeng studentC = SimpleFactory.CreateLeiFeng("学雷锋的大学生");
            studentC.Wash();


            //工厂方法模式
            IFactory factory = new UndergraduateFactory();
            LeiFeng student = factory.CreateLeiFeng();

            student.BuyRice();
            student.Sweep();
            student.Wash();

            Console.Read();
        }
    }

    //雷锋
    class LeiFeng
    {
        public void Sweep()
        {
            Console.WriteLine("扫地");
        }

        public void Wash()
        {
            Console.WriteLine("洗衣");
        }

        public void BuyRice()
        {
            Console.WriteLine("买米");
        }
    }

    //学雷锋的大学生
    class Undergraduate : LeiFeng
    { }

    //社区志愿者
    class Volunteer : LeiFeng
    { }

    //简单雷锋工厂
    class SimpleFactory
    {
        public static LeiFeng CreateLeiFeng(string type)
        {
            LeiFeng result = null;
            switch (type)
            {
                case "学雷锋的大学生":
                    result = new Undergraduate();
                    break;
                case "社区志愿者":
                    result = new Volunteer();
                    break;

            }
            return result;
        }
    }

    //雷锋工厂
    interface IFactory
    {
        LeiFeng CreateLeiFeng();
    }

    //学雷锋的大学生工厂
    class UndergraduateFactory : IFactory
    {
        public LeiFeng CreateLeiFeng()
        {
            return new Undergraduate();
        }
    }

    //社区志愿者工厂
    class VolunteerFactory : IFactory
    {
        public LeiFeng CreateLeiFeng()
        {
            return new Volunteer();
        }
    }

}
