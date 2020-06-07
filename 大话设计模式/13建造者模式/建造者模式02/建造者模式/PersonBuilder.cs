using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace 建造者模式
{

class PersonThinBuilder
{
    private Graphics g;
    private Pen p;

    public PersonThinBuilder(Graphics g, Pen p)
    {
        this.g = g;
        this.p = p;
    }

    public void Build()
    {
        g.DrawEllipse(p, 50, 20, 30, 30);
        g.DrawRectangle(p, 60, 50, 10, 50);
        g.DrawLine(p, 60, 50, 40, 100);
        g.DrawLine(p, 70, 50, 90, 100);
        g.DrawLine(p, 60, 100, 45, 150);
        g.DrawLine(p, 70, 100, 85, 150);
    }
}

class PersonFatBuilder
{
    private Graphics g;
    private Pen p;

    public PersonFatBuilder(Graphics g, Pen p)
    {
        this.g = g;
        this.p = p;
    }

    public void Build()
    {
        g.DrawEllipse(p, 50, 20, 30, 30);
        g.DrawEllipse(p, 45, 50, 40, 50);
        g.DrawLine(p, 50, 50, 30, 100);
        g.DrawLine(p, 80, 50, 100, 100);
        g.DrawLine(p, 60, 100, 45, 150);
        g.DrawLine(p, 70, 100, 85, 150);
    }
}
}
