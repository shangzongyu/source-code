using System;
using System.Collections.Generic;
using System.Text;

namespace 抽象工厂模式
{
    class Program
    {
        static void Main(string[] args)
        {
            User user = new User();

            SqlserverUser su = new SqlserverUser();
            su.Insert(user);
            su.GetUser(1);

            Console.Read();
        }
    }

    class User
    {
        private int _id;
        public int ID
        {
            get { return _id; }
            set { _id = value; }
        }

        private string _name;
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
    }

    class SqlserverUser
    {
        public void Insert(User user)
        {
            Console.WriteLine("在Sqlserver中给User表增加一条记录");
        }

        public User GetUser(int id)
        {
            Console.WriteLine("在Sqlserver中根据ID得到User表一条记录");
            return null;
        }
    }
}
