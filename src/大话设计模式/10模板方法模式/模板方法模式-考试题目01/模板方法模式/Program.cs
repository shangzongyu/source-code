using System;
using System.Collections.Generic;
using System.Text;

namespace 模板方法模式
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("学生甲抄的试卷：");
            TestPaperA studentA = new TestPaperA();
            studentA.TestQuestion1();
            studentA.TestQuestion2();
            studentA.TestQuestion3();

            Console.WriteLine("学生乙抄的试卷：");
            TestPaperB studentB = new TestPaperB();
            studentB.TestQuestion1();
            studentB.TestQuestion2();
            studentB.TestQuestion3();

            Console.Read();
        }
    }

    //学生甲抄的试卷
    class TestPaperA
    {
        //试题1
        public void TestQuestion1()
        {
            Console.WriteLine(" 杨过得到，后来给了郭靖，炼成倚天剑、屠龙刀的玄铁可能是[ ] a.球磨铸铁 b.马口铁 c.高速合金钢 d.碳素纤维 ");
            Console.WriteLine("答案：b");
        }
        //试题2
        public void TestQuestion2()
        {
            Console.WriteLine(" 杨过、程英、陆无双铲除了情花，造成[ ] a.使这种植物不再害人 b.使一种珍稀物种灭绝 c.破坏了那个生物圈的生态平衡 d.造成该地区沙漠化  ");
            Console.WriteLine("答案：a");
        }
        //试题3
        public void TestQuestion3()
        {
            Console.WriteLine(" 蓝凤凰的致使华山师徒、桃谷六仙呕吐不止,如果你是大夫,会给他们开什么药[ ] a.阿司匹林 b.牛黄解毒片 c.氟哌酸 d.让他们喝大量的生牛奶 e.以上全不对   ");
            Console.WriteLine("答案：c");
        }


    }

    //学生乙抄的试卷
    class TestPaperB
    {
        //试题1
        public void TestQuestion1()
        {
            Console.WriteLine(" 杨过得到，后来给了郭靖，炼成倚天剑、屠龙刀的玄铁可能是[ ] a.球磨铸铁 b.马口铁 c.高速合金钢 d.碳素纤维 ");
            Console.WriteLine("答案：d");
        }
        //试题2
        public void TestQuestion2()
        {
            Console.WriteLine(" 杨过、程英、陆无双铲除了情花，造成[ ] a.使这种植物不再害人 b.使一种珍稀物种灭绝 c.破坏了那个生物圈的生态平衡 d.造成该地区沙漠化  ");
            Console.WriteLine("答案：b");
        }
        //试题3
        public void TestQuestion3()
        {
            Console.WriteLine(" 蓝凤凰的致使华山师徒、桃谷六仙呕吐不止,如果你是大夫,会给他们开什么药[ ] a.阿司匹林 b.牛黄解毒片 c.氟哌酸 d.让他们喝大量的生牛奶 e.以上全不对   ");
            Console.WriteLine("答案：a");
        }

    }
}
