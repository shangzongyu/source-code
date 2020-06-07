using System;
using System.Collections.Generic;
using System.Text;

namespace 状态模式
{
    class Program
    {
        static int Hour = 0;
        static bool WorkFinished = false;

        static void Main(string[] args)
        {

            Hour = 9;
            WriteProgram();
            Hour = 10;
            WriteProgram();
            Hour = 12;
            WriteProgram();
            Hour = 13;
            WriteProgram();
            Hour = 14;
            WriteProgram();
            Hour = 17;

            WorkFinished = true;
            //WorkFinished = false;

            WriteProgram();
            Hour = 19;
            WriteProgram();
            Hour = 22;
            WriteProgram();

            Console.Read();
        }

        public static void WriteProgram()
        {
            if (Hour < 12)
            {
                Console.WriteLine("当前时间：{0}点 上午工作，精神百倍", Hour);
            }
            else if (Hour < 13)
            {
                Console.WriteLine("当前时间：{0}点 饿了，午饭；犯困，午休。", Hour);
            }
            else if (Hour < 17)
            {
                Console.WriteLine("当前时间：{0}点 下午状态还不错，继续努力", Hour);
            }
            else
            {
                if (WorkFinished)
                {
                    Console.WriteLine("当前时间：{0}点 下班回家了", Hour);
                }
                else
                {
                    if (Hour < 21)
                    {
                        Console.WriteLine("当前时间：{0}点 加班哦，疲累之极", Hour);
                    }
                    else
                    {
                        Console.WriteLine("当前时间：{0}点 不行了，睡着了。", Hour);
                    }
                }
            }
        }
    }
}
