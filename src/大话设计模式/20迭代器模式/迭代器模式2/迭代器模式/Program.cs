using System;
using System.Collections.Generic;
using System.Text;

namespace 迭代器模式
{
    class Program
    {
        static void Main(string[] args)
        {

            IList<string> a = new List<string>();
            a.Add("大鸟");
            a.Add("小菜");
            a.Add("行李");
            a.Add("老外");
            a.Add("公交内部员工");
            a.Add("小偷");

            foreach (string item in a)
            {
                Console.WriteLine("{0} 请买车票!", item);
            }

            IEnumerator<string> e = a.GetEnumerator();
            while (e.MoveNext())
            {
                Console.WriteLine("{0} 请买车票!", e.Current);

            }
            Console.Read();
        }
    }

}
