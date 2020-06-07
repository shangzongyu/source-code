using System;
using System.Collections.Generic;
using System.Text;

namespace 职责链模式
{
    enum ManagerLevel { 经理,总监,总经理}

    class Program
    {
        static void Main(string[] args)
        {

            Manager jinli = new Manager("金利");
            Manager zongjian = new Manager("宗剑");
            Manager zhongjingli = new Manager("钟精励");

            Request request = new Request();
            request.RequestType = "加薪";
            request.RequestContent = "小菜请求加薪";
            request.Number = 1000;

            jinli.GetResult(ManagerLevel.经理, request);
            zongjian.GetResult(ManagerLevel.总监, request);
            zhongjingli.GetResult(ManagerLevel.总经理, request);

            Request request2 = new Request();
            request2.RequestType = "请假";
            request2.RequestContent = "小菜请假";
            request2.Number = 3;

            jinli.GetResult(ManagerLevel.经理, request2);
            zongjian.GetResult(ManagerLevel.总监, request2);
            zhongjingli.GetResult(ManagerLevel.总经理, request2);

            Console.Read();


        }
    }

    
    //管理者
    class Manager
    {
        
        protected string name;

        public Manager(string name)
        {
            this.name = name;
        }

        //得到结果
        public void GetResult(ManagerLevel managerLevel, Request request)
        {
            if (managerLevel == ManagerLevel.经理)
            {
                if (request.RequestType == "请假" && request.Number <= 2)
                {
                    Console.WriteLine("{0}:{1} 数量{2} 被批准", name, request.RequestContent, request.Number);
                }
                else
                {
                    Console.WriteLine("{0}:{1} 数量{2} 我无权处理", name, request.RequestContent, request.Number);
                }

            }
            else if (managerLevel == ManagerLevel.总监)
            {
                if (request.RequestType == "请假" && request.Number <= 5)
                {
                    Console.WriteLine("{0}:{1} 数量{2} 被批准", name, request.RequestContent, request.Number);
                }
                else
                {
                    Console.WriteLine("{0}:{1} 数量{2} 我无权处理", name, request.RequestContent, request.Number);
                }
            }
            else if (managerLevel == ManagerLevel.总经理)
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
