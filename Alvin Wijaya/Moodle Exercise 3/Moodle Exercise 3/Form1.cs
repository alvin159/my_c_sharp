using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Moodle_Exercise_3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                textBox2.Text = "Text is missing";
            }
            else if (textBox1.Text.Length > 30)
            {
                textBox2.Text = "Too long";
            }
            else { textBox2.Text = textBox1.Text.ToUpper(); }
        }
    }
}
