using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Box1_TextChanged(object sender, EventArgs e)
        {
            int a = 0;
            Console.Write(a);
        }

        private void Double_Click(object sender, EventArgs e)
        {
            if (Box1.Text == "")
                Box1.Text = "0";
            int sum = int.Parse(Box1.Text)* int.Parse(Box1.Text);
            Box1.Text = sum.ToString();
        }
    }
}
