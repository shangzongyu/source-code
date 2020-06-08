using System;
using System.Collections.Generic;
using System.Text;

namespace 职责链模式
{
    class Program
    {
        static void Main(string[] args)
        {

            CommonManager jinli = new CommonManager("金利");
            Majordomo zongjian = new Majordomo("宗剑");
            GeneralManager zhongjingli = new GeneralManager("钟精励");
            jinli.SetSuperior(zongjian);
            zongjian.SetSuperior(zhongjingli);

            Request request = new Request();
            request.RequestType = "请假";
            request.RequestContent = "小菜请假";
            request.Number = 1;
            jinli.RequestApplications(request);

            Request request2 = new Request();
            request2.RequestType = "请假";
            request2.RequestContent = "小菜请假";
            request2.Number = 4;
            jinli.RequestApplications(request2);

            Request request3 = new Request();
            request3.RequestType = "加薪";
            request3.RequestContent = "小菜请求加薪";
            request3.Number = 500;
            jinli.RequestApplications(request3);

            Request request4 = new Request();
            request4.RequestType = "加薪";
            request4.RequestContent = "小菜请求加薪";
            request4.Number = 1000;
            jinli.RequestApplications(request4);

            Console.Read();

        }
    }

    //管理者
    abstract class Manager
    {
        protected string name;
        //管理者的上级
        protected Manager superior;

        public Manager(string name)
        {
            this.name = name;
        }

        //设置管理者的上级
        public void SetSuperior(Manager superior)
        {
            this.superior = superior;
        }

        //申请请求
        abstract public void RequestApplications(Request request);
    }

    //经理
    class CommonManager : Manager
    {
        public CommonManager(string name)
            : base(name)
        { }
        public override void RequestApplications(Request request)
        {

            if (request.RequestType == "请假" && request.Number <= 2)
            {
                Console.WriteLine("{0}:{1} 数量{2} 被批准", name, request.RequestContent, request.Number);
            }
            else
            {
                if (superior != null)
                    superior.RequestApplications(request);
            }

        }
    }

    //总监
    class Majordomo : Manager
    {
        public Majordomo(string name)
            : base(name)
        { }
        public override void RequestApplications(Request request)
        {

            if (request.RequestType == "请假" && request.Number <= 5)
            {
                Console.WriteLine("{0}:{1} 数量{2} 被批准", name, request.RequestContent, request.Number);
            }
            else
            {
                if (superior != null)
                    superior.RequestApplications(request);
            }

        }
    }

    //总经理
    class GeneralManager : Manager
    {
        public GeneralManager(string name)
            : base(name)
        { }
        public override void RequestApplications(Request request)
        {

            if (request.RequestType == "请假")
            {
                Console.WriteLine("{0}:{1} 数量{2} 被批准", name, request.RequestContent, request.Number);
            }
            else if (request.RequestType == "加薪" && request.Number <= 500)
            {
                Console.WriteLine("{0}:{1} 数量{2} 被批准", name, request.RequestContent, request.Number);
            }
            else if (request.RequestType == "加薪" && request.Number > 500)
            {
                Console.WriteLine("{0}:{1} 数量{2} 再说吧", name, request.RequestContent, request.Number);
            }
        }
    }

    //申请
    class Request
    {
        //申请类别
        private string requestType;
        public string RequestType
        {
            get { return requestType; }
            set { requestType = value; }
        }

        //申请内容
        private string requestContent;
        public string RequestContent
        {
            get { return requestContent; }
            set { requestContent = value; }
        }

        //数量
        private int number;
        public int Number
        {
            get { return number; }
            set { number = value; }
        }
    }


}
