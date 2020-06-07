using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.IO;
using System.Windows.Forms;
using AxWMPLib;
using WMPLib;

namespace 解释器模式
{
    public partial class Form1 : Form
    {

        string path = Application.StartupPath + "\\Sounds\\";
        MediaPlayer p;
        MediaPlayer p2;
        Expression expression;
        Expression expression2;
        PlayContext context;
        PlayContext context2;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitSound();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            context = new PlayContext();
            context.PlayText = txtMain.Text;
            context2 = new PlayContext();
            context2.PlayText = txtChord.Text;
            timerMain.Interval = 1000;
            timerChord.Interval = 1000;
            timerMain.Start();
            timerChord.Start();
        }

        private void timerMain_Tick(object sender, EventArgs e)
        {
            if (context.PlayText.Length > 0)
            {
                try
                {
                    expression = ExpressionFactory.CreateExpression(context.PlayText.Substring(0, 1),p);
                    expression.Interpret(context);
                    timerMain.Interval = p.Interval;
                            
                }
                catch (Exception ex)
                {
                    timerMain.Stop();
                    MessageBox.Show(ex.Message);
                }
                
            }
            else
            {
                timerMain.Stop();
            }
        }

        private void timerChord_Tick(object sender, EventArgs e)
        {
            if (context2.PlayText.Length > 0)
            {
                try
                {
                    expression2 = ExpressionFactory.CreateExpression(context2.PlayText.Substring(0, 1), p2);
                    expression2.Interpret(context2);
                    timerChord.Interval = p2.Interval;

                }
                catch (Exception ex)
                {
                    timerChord.Stop();
                    txtChord.Text = txtChord.Text.Replace(context2.PlayText, "");
                    MessageBox.Show(context2.PlayText);
                }

            }
            else
            {
                timerChord.Stop();
            }
        }


        private void InitSound()
        {
            p = new MediaPlayer(path, axCL2, axDL2, axEL2, axFL2, axGL2, axAL2, axBL2, axCL1, axDL1, axEL1, axFL1, axGL1, axAL1, axBL1, axC, axD, axE, axF, axG, axA, axB, axCH1, axDH1, axEH1, axFH1, axGH1, axAH1, axBH1, axCH2, axDH2, axEH2, axFH2, axGH2, axAH2, axBH2, axCH3, axDH3, axEH3);

            for (int i = 0; i < 38; i++)
                p.GetSound(i, i);
            p2 = new MediaPlayer(path, axCL2, axDL2, axEL2, axFL2, axGL2, axAL2, axBL2, axCL1, axDL1, axEL1, axFL1, axGL1, axAL1, axBL1, axC, axD, axE, axF, axG, axA, axB, axCH1, axDH1, axEH1, axFH1, axGH1, axAH1, axBH1, axCH2, axDH2, axEH2, axFH2, axGH2, axAH2, axBH2, axCH3, axDH3, axEH3);

            for (int i = 0; i < 38; i++)
                p2.GetSound(i, i);

            
        }

        private void btnSHT_Click(object sender, EventArgs e)
        {
            txtMain.Text = "T 500 " +
            "O 3 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 4 C 1 O 3 A 0.5 G 1 C 0.5 E 0.5 D 3 " +
            "D 0.5 E 0.5 G 3 D 0.5 E 0.5 O 2 A 3 A 0.5 O 3 C 0.5 D 1.5 E 0.5 D 0.5 O 2 B 0.5 A 0.5 O 3 C 0.5 O 2 G 3 " +

            "O 3 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 4 C 1 O 3 A 0.5 G 1 C 0.5 E 0.5 D 3 " +
            "D 0.5 E 0.5 G 3 D 0.5 E 0.5 O 2 A 3 A 0.5 O 3 C 0.5 D 1.5 E 0.5 D 0.5 O 2 B 0.5 A 0.5 G 0.5 O 3 C 3 " +

            "P 0.5 O 4 C 0.5 C 0.5 O 3 A 0.5 O 4 C 2 P 0.5 O 3 A 0.5 O 4 C 0.5 O 3 A 0.5 G 2.5 G 0.5 E 0.5 A 1.5 G 0.5 C 1 D 0.25 C 0.25 D 0.5 E 2.5 "+
            "E 0.5 E 0.5 D 0.5 E 2.5 O 4 C 0.5 C 0.5 O 3 B 0.5 A 3 E 0.5 E 0.5 D 1.5 E 0.5 O 4 C 0.5 O 3 B 0.5 A 0.5 E 0.5 G 2.5 "+

            "O 3 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 4 C 1 O 3 A 0.5 G 1 C 0.5 E 0.5 D 3 " +
            "D 0.5 E 0.5 G 3 D 0.5 E 0.5 O 2 A 3 A 0.5 O 3 C 0.5 D 1.5 E 0.5 D 0.5 O 2 B 0.5 A 0.5 G 0.5 O 3 C 3 ";


            txtChord.Text = "T 500 " +
            "P 1 O 1 F 0.5 O 2 C 0.5 A 0.5 C 0.5 A 1 P 1 O 1 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 O 2 G 1 " +
            "P 1 O 1 F 0.5 O 2 C 0.5 A 0.5 C 0.5 O 0 A 0.5 O 1 E 0.5 " +
            "O 2 C 1 O 1 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 O 2 G 0.5 O 1 B 0.5 " +
            "O 2 G 0.5 O 1 B 0.5 C 0.5 G 0.5 O 2 E 0.5 O 1 G 0.5 O 2 E 0.5 O 1 G 0.5 O 2 E 0.5 O 1 G 0.5 F 0.5 C 0.5 F 0.5 C 0.5 F 0.5 C 0.5 F 0.5 C 0.5 O 0 E 0.5 B 0.5 O 1 G 0.5 B 0.5 G 0.5 O 0 B 0.5 P 0.5 O 1 E 0.5 E 0.5 E 0.5 E 0.5 E 0.5 E 1 " +

            "P 1 O 1 F 0.5 O 2 C 0.5 A 0.5 C 0.5 A 1 P 1 O 1 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 O 2 G 1 " +
            "P 1 O 1 F 0.5 O 2 C 0.5 A 0.5 C 0.5 O 0 A 0.5 O 1 E 0.5 " +
            "O 2 C 1 O 1 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 O 2 G 0.5 O 1 B 0.5 " +
            "O 2 G 0.5 O 1 B 0.5 C 0.5 G 0.5 O 2 E 0.5 O 1 G 0.5 O 2 E 0.5 O 1 G 0.5 O 2 E 0.5 O 1 G 0.5 F 0.5 C 0.5 F 0.5 C 0.5 F 0.5 C 0.5 F 0.5 C 0.5 O 0 E 0.5 B 0.5 O 1 G 0.5 B 0.5 G 0.5 O 0 B 0.5 P 0.5 O 1 E 0.5 E 0.5 E 0.5 E 0.5 E 0.5 E 1 " +

            "P 2 O 1 D 0.5 A 0.5 O 2 F 0.5 O 1 A 0.5 P 2 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 P 2 F 0.25 O 2 C 0.25 F 0.25 A 0.25 O 3 C 0.25 O 2 A 0.25 F 0.25 C 0.25 " +
            "O 0 A 0.25 O 1 E 0.25 A 0.25 O 2 C 0.25 E 0.25 C 0.25 O 1 A 0.25 E 0.25 O 0 A 0.25 O 1 E 0.25 A 0.25 O 2 C 0.25 E 0.25 C 0.25 O 1 A 0.25 E 0.25 " +
            "P 2 O 1 C 0.5 G 0.5 O 2 E 0.5 O 1 G 0.5 P 2 D 0.5 A 0.5 O 2 F 0.5 O 1 A 0.5 " +
            "P 2 O 1 E 0.25 B 0.25 O 2 E 0.25 G 0.25 B 0.25 G 0.25 E 0.25 O 1 B 0.25 " +
            "D 0.25 A 0.25 O 2 D 0.25 F 0.25 A 0.25 F 0.25 D 0.25 O 1 A 0.25 E 0.25 G 0.25 O 2 B 0.25 E 0.25 G 0.25 E 0.25 B 0.25 O 1 G 0.25 "+

            "P 1 O 1 F 0.5 O 2 C 0.5 A 0.5 C 0.5 A 1 P 1 O 1 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 O 2 G 1 " +
            "P 1 O 1 F 0.5 O 2 C 0.5 A 0.5 C 0.5 O 0 A 0.5 O 1 E 0.5 " +
            "O 2 C 1 O 1 E 0.5 B 0.5 O 2 G 0.5 O 1 B 0.5 O 2 G 0.5 O 1 B 0.5 " +
            "O 2 G 0.5 O 1 B 0.5 C 0.5 G 0.5 O 2 E 0.5 O 1 G 0.5 O 2 E 0.5 O 1 G 0.5 O 2 E 0.5 O 1 G 0.5 F 0.5 C 0.5 F 0.5 C 0.5 F 0.5 C 0.5 F 0.5 C 0.5 O 0 E 0.5 B 0.5 O 1 G 0.5 B 0.5 G 0.5 O 0 B 0.5 P 0.5 O 1 E 0.5 E 0.5 E 0.5 E 0.5 E 0.5 E 1 ";
            
        }

        private void btnYXDCB_Click(object sender, EventArgs e)
        {
            //textBox1.Text = "T 1000 O 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 E 1 D 0.5 C 0.5 C 0.5 C 0.5 C 0.5 O 1 A 0.25 G 0.25 G 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 1 A 0.5 G 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 E 0.5 D 0.5 C 0.5 C 0.25 D 0.25 O 1 A 1 G 0.5 A 0.5 O 2 C 1.5 D 0.25 E 0.25 D 1 E 0.5 C 0.5 C 3 O 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 E 1 D 0.5 C 0.5 C 0.5 C 0.5 C 0.5 O 1 A 0.25 G 0.25 G 1 G 0.5 O 2 C 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 1 A 0.5 G 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 E 0.5 D 0.5 C 0.5 C 0.25 D 0.25 O 1 A 1 G 0.5 A 0.5 O 2 C 1.5 D 0.25 E 0.25 D 1 E 0.5 C 0.5 C 3 E 0.5 G 0.5 O 3 C 1.5 O 2 B 0.25 O 3 C 0.25 O 2 B 1 A 0.5 G 0.5 A 0.5 O 3 C 0.5 O 2 E 0.5 D 0.5 C 1 C 0.5 C 0.5 C 0.5 O 3 C 1 O 2 G 0.25 A 0.25 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 3 E 0.5 G 0.5 O 3 C 1.5 O 2 B 0.25 O 3 C 0.25 O 2 B 1 A 0.5 G 0.5 A 0.5 O 3 C 0.5 O 2 E 0.5 D 0.5 C 1 C 0.5 C 0.5 C 0.5 O 3 C 1 O 2 G 0.25 A 0.25 G 0.5 D 0.25 E 0.25 D 0.5 C 0.5 C 3 ";
            txtMain.Text = "T 1000 O 2 G 0.5 O 3 C 0.5 E 1.5 G 0.5 E 1 D 0.5 C 0.5 C 0.5 C 0.5 C 0.5 O 2 A 0.25 G 0.25 G 1 G 0.5 O 3 C 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 1 A 0.5 G 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 E 0.5 D 0.5 C 0.5 C 0.25 D 0.25 O 2 A 1 G 0.5 A 0.5 O 3 C 1.5 D 0.25 E 0.25 D 1 E 0.5 C 0.5 C 3 O 2 G 0.5 O 3 C 0.5 E 1.5 G 0.5 E 1 D 0.5 C 0.5 C 0.5 C 0.5 C 0.5 O 2 A 0.25 G 0.25 G 1 G 0.5 O 3 C 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 1 A 0.5 G 0.5 E 1.5 G 0.5 G 0.5 G 0.5 A 0.5 G 0.5 E 0.5 D 0.5 C 0.5 C 0.25 D 0.25 O 2 A 1 G 0.5 A 0.5 O 3 C 1.5 D 0.25 E 0.25 D 1 E 0.5 C 0.5 C 3 E 0.5 G 0.5 O 4 C 1.5 O 3 B 0.25 O 4 C 0.25 O 3 B 1 A 0.5 G 0.5 A 0.5 O 4 C 0.5 O 3 E 0.5 D 0.5 C 1 C 0.5 C 0.5 C 0.5 O 4 C 1 O 3 G 0.25 A 0.25 G 0.5 D 0.25 E 0.25 D 0.5 C 0.25 D 0.25 D 3 E 0.5 G 0.5 O 4 C 1.5 O 3 B 0.25 O 4 C 0.25 O 3 B 1 A 0.5 G 0.5 A 0.5 O 4 C 0.5 O 3 E 0.5 D 0.5 C 1 C 0.5 C 0.5 C 0.5 O 4 C 1 O 3 G 0.25 A 0.25 G 0.5 D 0.25 E 0.25 D 0.5 C 0.5 C 3 ";
            txtChord.Text = "";
        }

        
    }

    class PlayContext
    {
        private string text;
        public string PlayText
        {
            get { return text; }
            set { text = value; }
        }
    }
    /// <summary>
    /// 表达式工厂
    /// </summary>
    class ExpressionFactory
    {
        public static Expression CreateExpression(string letter, MediaPlayer p)
        {
            Expression result = null;
            switch (letter)
            {
                case "O":
                    result = new Scale(p);
                    break;
                case "T":
                    result = new Speed(p);
                    break;
                case "C":
                case "D":
                case "E":
                case "F":
                case "G":
                case "A":
                case "B":
                case "P":
                    result = new Note(p);
                    break;

            }

            return result;
        }
    }
    /// <summary>
    /// 表达式
    /// </summary>
    abstract class Expression
    {
        protected MediaPlayer p;
        
        public Expression(MediaPlayer p)
        {
            this.p = p;
        }

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

        public abstract void Excute(string key,double value);
    }
    //音符
    class Note : Expression
    {
        public Note(MediaPlayer p):base(p)
        {}
        public override void Excute(string key, double value)
        {
            p.Note = key;
            p.test += value;
            //System.Console.WriteLine("test{0}:{1}",p.GetType().FullName, p.test);

            p.Interval = Convert.ToInt32(value * p.Speed);//音长为获得的值乘以音速，也就是timer控件的单次interval值
            p.Play();
        }
    }
    //音阶
    class Scale : Expression
    {
        public Scale(MediaPlayer p)
            : base(p)
        { }

        public override void Excute(string key, double value)
        {
            p.Scale=Convert.ToInt32(value);
            p.Interval = 1;//在设置音阶时，timer不需要时间间隔，所以为1表示1毫秒
        }
    }
    //音符
    class Speed : Expression
    {
        public Speed(MediaPlayer p)
            : base(p)
        { }

        public override void Excute(string key, double value)
        {
            p.Speed = Convert.ToInt32(value);
            p.Interval = 1;//在设置音速时，timer不需要时间间隔，所以为1表示1毫秒
        }
    }

    //播放器
    class MediaPlayer
    {
        public double test = 0;

        private AxWindowsMediaPlayer[] awm;
        private string path;
        public MediaPlayer(string path, params AxWindowsMediaPlayer[] arr)
        {
            awm = arr;
            this.path = path;
        }

        /// <summary>
        /// 给具体的MediaPlayer控件设置声音文件
        /// </summary>
        /// <param name="index"></param>
        /// <param name="num"></param>
        public void GetSound(int index, int num)
        {
            awm[index].URL = path + num.ToString() + ".mp3";
        }

        //音阶
        private int scale=2;
        public int Scale
        {
            get { return scale; }
            set { scale = value; }
        }
        //音速
        private int speed=500;
        public int Speed
        {
            get { return speed; }
            set { speed = value; }
        }
        //音符
        private string note;
        public string Note
        {
            get { return note; }
            set { note = value; }
        }
        //音长
        private int interval=1;
        public int Interval
        {
            get { return interval; }
            set { interval = value; }
        }
        //播放
        public void Play()
        {
            int index = 0;
            //选择音阶
            switch (scale)
            {
                case 0:
                    index = 0;
                    break;
                case 1:
                    index = 7;
                    break;
                case 2:
                    index = 14;
                    break;
                case 3:
                    index = 21;
                    break;
                case 4:
                    index = 28;
                    break;
                case 5:
                    index = 35;
                    break;

            }
            //选择音符
            switch (note)
            {
                case "C":
                    index += 0;
                    break;
                case "D":
                    index += 1;
                    break;
                case "E":
                    index += 2;
                    break;
                case "F":
                    index += 3;
                    break;
                case "G":
                    index += 4;
                    break;
                case "A":
                    index += 5;
                    break;
                case "B":
                    index += 6;
                    break;
                case "P":
                    return;
            }

            //停止原来播放的声音。相当于钢琴某个键按过后还在余音，此时再此按到此键，则原有余音结束
            awm[index].Ctlcontrols.stop();
            //播放
            awm[index].Ctlcontrols.play();
        }

        
    }
}