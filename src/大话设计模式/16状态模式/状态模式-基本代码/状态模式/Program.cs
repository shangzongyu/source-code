using System;
using System.Collections.Generic;
using System.Text;

namespace 状态模式
{
    class Program
    {
        static void Main(string[] args)
        {
            Context c = new Context(new ConcreteStateA());

            c.Request();
            c.Request();
            c.Request();
            c.Request();

            Console.Read();
        }
    }

    class Context
    {
        private State state;

        public Context(State state)
        {
            this.state = state;
        }

        public State State
        {
            get
            {
                return state;
            }
            set
            {
                state = value;
                Console.WriteLine("当前状态:" + state.GetType().Name);
            }
        }

        public void Request()
        {
            state.Handle(this);
        }
    }

    abstract class State
    {
        public abstract void Handle(Context context);
    }

    class ConcreteStateA : State
    {
        public override void Handle(Context context)
        {
            context.State = new ConcreteStateB();
        }
    }

    class ConcreteStateB : State
    {
        public override void Handle(Context context)
        {
            context.State = new ConcreteStateA();
        }
    }

}
