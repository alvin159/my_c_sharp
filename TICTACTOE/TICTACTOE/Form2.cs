using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TICTACTOE
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Form1.playerName(textBox1.Text, textBox2.Text); //playerName function is called from Form 1
            this.Close(); //close the current form
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
