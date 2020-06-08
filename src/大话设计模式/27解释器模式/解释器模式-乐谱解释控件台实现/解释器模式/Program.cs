using System;
using System.Collections.Generic;
using System.Text;

namespace 解释器模式
{
    class Program
    {
        static void Main(string[] args)
        {
            PlayContext context = new PlayContext();
            //音乐-上海滩
            Console.WriteLine("上海滩：");
            //context.演奏文本 = "T 500 O 2 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 3 C 1 O 2 A 0.5 G 1 C 0.5 E 0.5 D 3 D 0.5 E 0.5 G 3 D 0.5 E 0.5 O 1 A 3 A 0.5 O 2 C 0.5 D 1.5 E 0.5 D 0.5 O 1 B 0.5 A 0.5 O 2 C 0.5 O 1 G 3 P 0.5 O 2 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 3 C 1 O 2 A 0.5 G 1 C 0.5 E 0.5 D 3 D 0.5 E 0.5 G 3 D 0.5 E 0.5 O 1 A 3 A 0.5 O 2 C 0.5 D 1.5 E 0.5 D 0.5 O 1 B 0.5 A 0.5 G 0.5 O 2 C 3 P 0.5 O 3 C 0.5 C 0.5 O 2 A 0.5 O 3 C 2 P 0.5 O 2 A 0.5 O 3 C 0.5 O 2 A 0.5 G 2.5 G 0.5 E 0.5 A 1.5 G 0.5 C 1 D 0.25 C 0.25 D 0.5 E 2.5 E 0.5 E 0.5 D 0.5 E 2.5 O 3 C 0.5 C 0.5 O 2 B 0.5 A 3 E 0.5 E 0.5 D 1.5 E 0.5 O 3 C 0.5 O 2 B 0.5 A 0.5 E 0.5 G 2 P 0.5 O 2 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 3 C 1 O 2 A 0.5 G 1 C 0.5 E 0.5 D 3 D 0.5 E 0.5 G 3 D 0.5 E 0.5 O 1 A 3 A 0.5 O 2 C 0.5 D 1.5 E 0.5 D 0.5 O 1 B 0.5 A 0.5 G 0.5 O 2 C 3 ";
            context.PlayText = "T 500 O 2 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 3 C 1 O 2 A 0.5 G 1 C 0.5 E 0.5 D 3 ";
            //音乐-隐形的翅膀
            //Console.WriteLine("隐形的翅膀："); 
            //context.演奏文本 = "T 1000 O 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 E 1 D 0.5 C 0.5 C 0.5 C 0.5 C 0.5 O 1 A 0.25 G 0.25 G 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 1 A 0.5 G 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 E 0.5 D 0.5 C 0.5 C 0.25 D 0.25 O 1 A 1 G 0.5 A 0.5 O 2 C 1.5 D 0.25 E 0.25 D 1 E 0.5 C 0.5 C 3 O 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 E 1 D 0.5 C 0.5 C 0.5 C 0.5 C 0.5 O 1 A 0.25 G 0.25 G 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 1 A 0.5 G 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 E 0.5 D 0.5 C 0.5 C 0.25 D 0.25 O 1 A 1 G 0.5 A 0.5 O 2 C 1.5 D 0.25 E 0.25 D 1 E 0.5 C 0.5 C 3 E 0.5 G 0.5 O 3 C 1.5 O 2 B 0.25 O 3 C 0.25 O 2 B 1 A 0.5 G 0.5 A 0.5 O 3 C 0.5 O 2 E 0.5 D 0.5 C 1 C 0.5 C 0.5 C 0.5 O 3 C 1 O 2 G 0.25 A 0.25 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 3 E 0.5 G 0.5 O 3 C 1.5 O 2 B 0.25 O 3 C 0.25 O 2 B 1 A 0.5 G 0.5 A 0.5 O 3 C 0.5 O 2 E 0.5 D 0.5 C 1 C 0.5 C 0.5 C 0.5 O 3 C 1 O 2 G 0.25 A 0.25 G 0.5 D 0.25 E 0.25 D 0.5 C 0.5 C 3 ";
            Expression expression = null;
            try
            {
                while (context.PlayText.Length > 0)
                {
                    string str = context.PlayText.Substring(0, 1);
                    switch (str)
                    {
                        case "O":
                            expression = new Scale();
                            break;
                        case "T":
                            expression = new Speed();
                            break;
                        case "C":
                        case "D":
                        case "E":
                        case "F":
                        case "G":
                        case "A":
                        case "B":
                        case "P":
                            expression = new Note();
                            break;

                    }
                    expression.Interpret(context);

                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            Console.Read();
        }
    }
    //演奏内容
    class PlayContext
    {
        //演奏文本
        private string text;
        public string PlayText
        {
            get { return text; }
            set { text = value; }
        }
    }

    //表达式
    abstract class Expression
    {
        //解释器
        public void Interpret(PlayContext context)
        {
            if (context.PlayText.Length == 0)
            {
                return;
            }
            else
            {
                string playKey = context.PlayText.Substring(0, 1);
                context.PlayText = context.PlayText.Substring(2);
                double playValue = Convert.ToDouble(context.PlayText.Substring(0, context.PlayText.IndexOf(" ")));
                context.PlayText = context.PlayText.Substring(context.PlayText.IndexOf(" ") + 1);

                Excute(playKey, playValue);

            }
        }
        //执行
        public abstract void Excute(string key, double value);
    }

    //音符
    class Note : Expression
    {
        public override void Excute(string key, double value)
        {
            string note = "";
            switch (key)
            {
                case "C":
                    note = "1";
                    break;
                case "D":
                    note = "2";
                    break;
                case "E":
                    note = "3";
                    break;
                case "F":
                    note = "4";
                    break;
                case "G":
                    note = "5";
                    break;
                case "A":
                    note = "6";
                    break;
                case "B":
                    note = "7";
                    break;

            }
            Console.Write("{0} ", note);
        }
    }

    //音阶
    class Scale : Expression
    {
        public override void Excute(string key, double value)
        {
            string scale = "";
            switch (Convert.ToInt32(value))
            {
                case 1:
                    scale = "低音";
                    break;
                case 2:
                    scale = "中音";
                    break;
                case 3:
                    scale = "高音";
                    break;

            }
            Console.Write("{0} ", scale);
        }
    }

    //音速
    class Speed : Expression
    {
        public override void Excute(string key, double value)
        {
            string speed;
            if (value < 500)
                speed = "快速";
            else if (value >= 1000)
                speed = "慢速";
            else
                speed = "中速";

            Console.Write("{0} ", speed);
        }
    }
}
