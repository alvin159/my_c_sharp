namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.Box1 = new System.Windows.Forms.TextBox();
            this.Double = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(59, 97);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Number";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // Box1
            // 
            this.Box1.Location = new System.Drawing.Point(125, 97);
            this.Box1.Name = "Box1";
            this.Box1.Size = new System.Drawing.Size(100, 20);
            this.Box1.TabIndex = 1;
            this.Box1.TextChanged += new System.EventHandler(this.Box1_TextChanged);
            // 
            // Double
            // 
            this.Double.Location = new System.Drawing.Point(232, 97);
            this.Double.Name = "Double";
            this.Double.Size = new System.Drawing.Size(75, 23);
            this.Double.TabIndex = 2;
            this.Double.Text = "Double";
            this.Double.UseVisualStyleBackColor = true;
            this.Double.Click += new System.EventHandler(this.Double_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Double);
            this.Controls.Add(this.Box1);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Box1;
        private System.Windows.Forms.Button Double;
    }
}

