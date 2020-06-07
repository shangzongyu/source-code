using System;
using System.Collections.Generic;
using System.Text;

namespace 状态模式
{
    class Program
    {
        static void Main(string[] args)
        {
            //紧急项目
            Work emergencyProjects = new Work();
            emergencyProjects.Hour = 9;
            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 10;
            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 12;
            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 13;
            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 14;
            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 17;

            //emergencyProjects.WorkFinished = true;
            emergencyProjects.TaskFinished = false;

            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 19;
            emergencyProjects.WriteProgram();
            emergencyProjects.Hour = 22;
            emergencyProjects.WriteProgram();

            Console.Read();
        }
    }

    //工作
    public class Work
    {
        //钟点
        private int hour;
        public int Hour
        {
            get { return hour; }
            set { hour = value; }
        }

        //任务完成
        private bool finish = false;
        public bool TaskFinished
        {
            get { return finish; }
            set { finish = value; }
        }


        public void WriteProgram()
        {
            if (hour < 12)
            {
                Console.WriteLine("当前时间：{0}点 上午工作，精神百倍", hour);
            }
            else if (hour < 13)
            {
                Console.WriteLine("当前时间：{0}点 饿了，午饭；犯困，午休。", hour);
            }
            else if (hour < 17)
            {
                Console.WriteLine("当前时间：{0}点 下午状态还不错，继续努力", hour);
            }
            else
            {
                if (finish)
                {
                    Console.WriteLine("当前时间：{0}点 下班回家了", hour);
                }
                else
                {
                    if (hour < 21)
                    {
                        Console.WriteLine("当前时间：{0}点 加班哦，疲累之极", hour);
                    }
                    else
                    {
                        Console.WriteLine("当前时间：{0}点 不行了，睡着了。", hour);
                    }
                }
            }
        }
    }

}
