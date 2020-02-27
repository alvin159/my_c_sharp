using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp2
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

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            int a = int.Parse(textBox1.Text) - 32;
            double sum = a*5/9 ;
            label4.Text = sum.ToString();
        }


        private void label4_Click(object sender, EventArgs e)
        {

        }
    }
}
