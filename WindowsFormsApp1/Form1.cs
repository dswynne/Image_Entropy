using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        // Get current working directory
        string curDir = Directory.GetCurrentDirectory();

        public Form1()
        {
            InitializeComponent();
            toolTip1.SetToolTip(genKeysButton, "Your outputs will print to the Output Window.");
            toolTip2.SetToolTip(testGenButton,
                "Your results will print to the Output Window. For more detailed results see blockFrequency.txt, " +
                "\nfrequency.txt, longestRun.txt, and runs.txt which should be in the same directory this application " +
                "\nwas run from.");
        }

        private void genKeysButton_Click(object sender, EventArgs e)
        {
            // Launch the file explorer
            int size = -1;

            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            DialogResult result = openFileDialog1.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string file = openFileDialog1.FileName;

                // Check the file extension to make sure it is a valid image type
                // .jpg , .jpeg , .jpe .jif , .jfif , .jfi
                int extension = file.LastIndexOf(".");
                if (file.Substring(extension) == ".jpg" || file.Substring(extension) == ".jpeg" ||
                    file.Substring(extension) == ".jpe" || file.Substring(extension) == ".jif" ||
                    file.Substring(extension) == ".jfif" || file.Substring(extension) == ".jfi")
                {
                    // Valid file extension
                    outputWindow.Text = "Starting the generator..." + Environment.NewLine;

                    // Run the generator
                    int first = curDir.IndexOf("Image_Entropy") + "Image_Entropy".Length;
                    string exec = curDir.Substring(0, first) + "\\x64\\Release\\Image_Entropy.exe";

                    ProcessStartInfo startInfo = new ProcessStartInfo();
                    startInfo.CreateNoWindow = true;
                    startInfo.UseShellExecute = false;
                    startInfo.FileName = exec;
                    startInfo.WindowStyle = ProcessWindowStyle.Hidden;
                    startInfo.Arguments = file + " -o";
                    //startInfo.Arguments = file;
                    try
                    {
                        using (Process exeProcess = Process.Start(startInfo))
                        {
                            exeProcess.WaitForExit();
                        }
                    }
                    catch
                    {
                        // Log error.
                        outputWindow.Text += "Error. Could not launch generator." + Environment.NewLine;
                    }

                    // Opening the output text file
                    string outputText = curDir + "\\output.txt";
                    using (StreamReader sr = new StreamReader(outputText))
                    {
                        // Read the stream to a string
                        string s = "";
                        while ((s = sr.ReadLine()) != null)
                        {
                            outputWindow.Text += s + Environment.NewLine;
                        }
                    }
                }
                else
                {
                    // Invalid file extension
                    outputWindow.Text = "Not a valid image. Please try again.\n";
                }
            }
            else
            {
                // Invalid file extension
                outputWindow.Text = "Not a valid image. Please try again.\n";
            }
            
        }

        private void testGenButton_Click(object sender, EventArgs e)
        {
            // Inform the user the test suite is starting
            outputWindow.Text = "Starting the test suite...This will take a few minutes to run." + Environment.NewLine;

            // Run the test suite
            int first = curDir.IndexOf("Image_Entropy") + "Image_Entropy".Length;
            string exec = curDir.Substring(0, first) + "\\x64\\Release\\testing.exe";

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = true;
            startInfo.UseShellExecute = false;
            startInfo.FileName = exec;
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            try
            {
                using (Process exeProcess = Process.Start(startInfo))
                {
                    exeProcess.WaitForExit();
                }
            }
            catch
            {
                // Log error.
                outputWindow.Text += "Error. Could not run the test suite." + Environment.NewLine;
            }

            // Opening the results text file
            string outputText = curDir + "\\results.txt";
            using (StreamReader sr = new StreamReader(outputText))
            {
                // Read the stream to a string
                string s = "";
                while ((s = sr.ReadLine()) != null)
                {
                    outputWindow.Text += s + Environment.NewLine;
                }
            }
        }

        private void outputWindowLabel_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void welcomeTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {
            
        }
    }
}
