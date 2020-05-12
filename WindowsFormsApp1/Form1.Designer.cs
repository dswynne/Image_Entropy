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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.genKeysButton = new System.Windows.Forms.Button();
            this.outputWindow = new System.Windows.Forms.TextBox();
            this.testGenButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.welcomeTextBox = new System.Windows.Forms.TextBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.toolTip2 = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // genKeysButton
            // 
            this.genKeysButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.genKeysButton.Location = new System.Drawing.Point(1609, 55);
            this.genKeysButton.Name = "genKeysButton";
            this.genKeysButton.Size = new System.Drawing.Size(748, 162);
            this.genKeysButton.TabIndex = 0;
            this.genKeysButton.Text = "Generate Keys";
            this.genKeysButton.UseVisualStyleBackColor = true;
            this.genKeysButton.Click += new System.EventHandler(this.genKeysButton_Click);
            // 
            // outputWindow
            // 
            this.outputWindow.Location = new System.Drawing.Point(88, 431);
            this.outputWindow.Multiline = true;
            this.outputWindow.Name = "outputWindow";
            this.outputWindow.ReadOnly = true;
            this.outputWindow.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.outputWindow.Size = new System.Drawing.Size(2269, 545);
            this.outputWindow.TabIndex = 1;
            this.outputWindow.Click += new System.EventHandler(this.textBox1_TextChanged);
            this.outputWindow.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // testGenButton
            // 
            this.testGenButton.Location = new System.Drawing.Point(1609, 241);
            this.testGenButton.Name = "testGenButton";
            this.testGenButton.Size = new System.Drawing.Size(748, 162);
            this.testGenButton.TabIndex = 2;
            this.testGenButton.Text = "Test Generators";
            this.testGenButton.UseVisualStyleBackColor = true;
            this.testGenButton.Click += new System.EventHandler(this.testGenButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(82, 371);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(217, 32);
            this.label1.TabIndex = 3;
            this.label1.Text = "Output Window:";
            this.label1.Click += new System.EventHandler(this.outputWindowLabel_Click);
            // 
            // welcomeTextBox
            // 
            this.welcomeTextBox.BackColor = System.Drawing.SystemColors.Control;
            this.welcomeTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.welcomeTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.welcomeTextBox.Location = new System.Drawing.Point(88, 55);
            this.welcomeTextBox.Multiline = true;
            this.welcomeTextBox.Name = "welcomeTextBox";
            this.welcomeTextBox.ReadOnly = true;
            this.welcomeTextBox.Size = new System.Drawing.Size(1482, 291);
            this.welcomeTextBox.TabIndex = 4;
            this.welcomeTextBox.Text = resources.GetString("welcomeTextBox.Text");
            this.welcomeTextBox.TextChanged += new System.EventHandler(this.welcomeTextBox_TextChanged);
            // 
            // toolTip1
            // 
            this.toolTip1.Popup += new System.Windows.Forms.PopupEventHandler(this.toolTip1_Popup);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(2410, 1018);
            this.Controls.Add(this.welcomeTextBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.testGenButton);
            this.Controls.Add(this.outputWindow);
            this.Controls.Add(this.genKeysButton);
            this.Name = "Form1";
            this.Text = "Image Entropy App";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button genKeysButton;
        private System.Windows.Forms.TextBox outputWindow;
        private System.Windows.Forms.Button testGenButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox welcomeTextBox;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ToolTip toolTip2;
    }
}

