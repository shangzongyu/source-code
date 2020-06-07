using System;
using System.Collections.Generic;
using System.Text;

namespace 策略模式
{
    class Program
    {
        static void Main(string[] args)
        {
            Context context;

            context = new Context(new ConcreteStrategyA());
            context.ContextInterface();

            context = new Context(new ConcreteStrategyB());
            context.ContextInterface();

            context = new Context(new ConcreteStrategyC());
            context.ContextInterface();

            Console.Read();
        }
    }

    //抽象算法类
    abstract class Strategy
    {
        //算法方法
        public abstract void AlgorithmInterface();
    }
    //具体算法A
    class ConcreteStrategyA : Strategy
    {
        //算法A实现方法
        public override void AlgorithmInterface()
        {
            Console.WriteLine("算法A实现");
        }
    }
    //具体算法B
    class ConcreteStrategyB : Strategy
    {
        //算法B实现方法
        public override void AlgorithmInterface()
        {
            Console.WriteLine("算法B实现");
        }
    }
    //具体算法C
    class ConcreteStrategyC : Strategy
    {
        //算法C实现方法
        public override void AlgorithmInterface()
        {
            Console.WriteLine("算法C实现");
        }
    }
    //上下文
    class Context
    {
        Strategy strategy;

        public Context(Strategy strategy)
        {
            this.strategy = strategy;
        }
        //上下文接口
        public void ContextInterface()
        {
            strategy.AlgorithmInterface();
        }
    }

}
