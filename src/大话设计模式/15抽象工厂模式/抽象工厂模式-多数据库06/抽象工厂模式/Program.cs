using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Configuration;

namespace 抽象工厂模式
{
    class Program
    {
        static void Main(string[] args)
        {
            User user = new User();
            Department dept = new Department();

            IUser iu = DataAccess.CreateUser();

            iu.Insert(user);
            iu.GetUser(1);

            IDepartment id = DataAccess.CreateDepartment();
            id.Insert(dept);
            id.GetDepartment(1);

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

    class Department
    {
        private int _id;
        public int ID
        {
            get { return _id; }
            set { _id = value; }
        }

        private string _deptName;
        public string DeptName
        {
            get { return _deptName; }
            set { _deptName = value; }
        }
    }

    interface IUser
    {
        void Insert(User user);

        User GetUser(int id);
    }

    class SqlserverUser : IUser
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

    class AccessUser : IUser
    {
        public void Insert(User user)
        {
            Console.WriteLine("在Access中给User表增加一条记录");
        }

        public User GetUser(int id)
        {
            Console.WriteLine("在Access中根据ID得到User表一条记录");
            return null;
        }
    }

    interface IDepartment
    {
        void Insert(Department department);

        Department GetDepartment(int id);
    }

    class SqlserverDepartment : IDepartment
    {
        public void Insert(Department department)
        {
            Console.WriteLine("在Sqlserver中给Department表增加一条记录");
        }

        public Department GetDepartment(int id)
        {
            Console.WriteLine("在Sqlserver中根据ID得到Department表一条记录");
            return null;
        }
    }

    class AccessDepartment : IDepartment
    {
        public void Insert(Department department)
        {
            Console.WriteLine("在Access中给Department表增加一条记录");
        }

        public Department GetDepartment(int id)
        {
            Console.WriteLine("在Access中根据ID得到Department表一条记录");
            return null;
        }
    }

    class DataAccess
    {
        private static readonly string AssemblyName = "抽象工厂模式";
        private static readonly string db = ConfigurationManager.AppSettings["DB"];
        
        public static IUser CreateUser()
        {
            string className = AssemblyName + "." + db + "User";
            return (IUser)Assembly.Load(AssemblyName).CreateInstance(className);
        }

        public static IDepartment CreateDepartment()
        {
            string className = AssemblyName + "." + db + "Department";
            return (IDepartment)Assembly.Load(AssemblyName).CreateInstance(className);
        }
    }

}