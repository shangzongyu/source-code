using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Reflection;

namespace 建造者模式
{
    abstract class PersonBuilder
    {
        protected Graphics g;
        protected Pen p;

        public PersonBuilder(Graphics g, Pen p)
        {
            this.g = g;
            this.p = p;
        }

        public abstract void BuildHead();
        public abstract void BuildBody();
        public abstract void BuildArmLeft();
        public abstract void BuildArmRight();
        public abstract void BuildLegLeft();
        public abstract void BuildLegRight();
    }

    class PersonThinBuilder : PersonBuilder
    {
        public PersonThinBuilder(Graphics g, Pen p)
            : base(g, p)
        { }

        public override void BuildHead()
        {
            g.DrawEllipse(p, 50, 20, 30, 30);
        }

        public override void BuildBody()
        {
            g.DrawRectangle(p, 60, 50, 10, 50);
        }

        public override void BuildArmLeft()
        {
            g.DrawLine(p, 60, 50, 40, 100);
        }

        public override void BuildArmRight()
        {
            g.DrawLine(p, 70, 50, 90, 100);
        }

        public override void BuildLegLeft()
        {
            g.DrawLine(p, 60, 100, 45, 150);
        }

        public override void BuildLegRight()
        {
            g.DrawLine(p, 70, 100, 85, 150);
        }
    }

    class PersonFatBuilder : PersonBuilder
    {
        public PersonFatBuilder(Graphics g, Pen p)
            : base(g, p)
        { }

        public override void BuildHead()
        {
            g.DrawEllipse(p, 50, 20, 30, 30);
        }

        public override void BuildBody()
        {
            g.DrawEllipse(p, 45, 50, 40, 50);
        }

        public override void BuildArmLeft()
        {
            g.DrawLine(p, 50, 50, 30, 100);
        }

        public override void BuildArmRight()
        {
            g.DrawLine(p, 80, 50, 100, 100);
        }

        public override void BuildLegLeft()
        {
            g.DrawLine(p, 60, 100, 45, 150);
        }

        public override void BuildLegRight()
        {
            g.DrawLine(p, 70, 100, 85, 150);
        }
    }

    class PersonDirector
    {
        private PersonBuilder pb;
        public PersonDirector(string type, Graphics g, Pen p)
        {
            string assemblyName="建造者模式";
            object[] args = new object[2];
            args[0] = g;
            args[1] = p;

            this.pb = (PersonBuilder)Assembly.Load(assemblyName).CreateInstance(assemblyName+".Person" + type + "Builder", false, BindingFlags.Default, null, args, null, null);
        }

        public void CreatePerson()
        {
            pb.BuildHead();
            pb.BuildBody();
            pb.BuildArmLeft();
            pb.BuildArmRight();
            pb.BuildLegLeft();
            pb.BuildLegRight();
        }
    }
}
