using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace TICTACTOE
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        public bool makan = true; // true = X and false = O; X moves first 
        public bool computer = false; // computer is false
        public int movement = 0; // counting movements
        public int winPlayer1 = 0; //counting wins for player1 
        public int winPlayer2 = 0; //counting wins for player2 / computer 
        public int countDraw = 0; //counting draws 
        public int countGames = 0; //counting games
        public int second = 0;
        public string savePath = "";
        public string openPath = "";
        public int ss;
        public static string player1, player2; //global string for player 1 and player 2
        private void buttonClick(object sender, EventArgs e)
        {
            //You can play with computer because player2 is computer (you type computer)
            if (player2.ToUpper() == "COMPUTER")
            {
                computer = true; // computer is true
                Button button = (Button)sender; //convert sender object into button
                if (button.Text == "" && button.Enabled == true)  //if there is not text in button and button is enabled this if condition is fulfill
                {
                    if (makan) //X (player1) turn
                    {
                        button.Text = "X";
                        timer1.Start(); 
                        movement++; //count the movements 
                        makan = false; //O turn
                    }
                    else //O (player2) turn
                    {
                        button.Text = "O";
                        movement++; //count the movements 
                        makan = true;
                        computerTurn().Enabled = false;
                    }
                    if (Draw() == true) //if the draw function is fulfill the game will stop and a message box will appear 
                    {
                        MessageBox.Show("It's a draw! Try again");
                        countDraw++; //counting draws 
                        if (savePath != "") //if there is savepath it will save the file in the savepath
                        {
                            StreamWriter sw = new StreamWriter(savePath);
                            sw.WriteLine(winDrawPlayLabel.Text);
                            sw.Close();
                        }
                        reset();
                    }
                    if (Win() == true) //if the win function is fulfill the game will stop and a message box will appear showing who wins the game
                    {
                        if (button.Text == "X") //if the last button pressed is X then player 1 wins
                        {
                            MessageBox.Show(player1 + " Won !"); //show message box with player1 name and Won !
                            winPlayer1++;//counting wins for player1 
                            countGames++;//counting games
                            if (savePath != "")//if there is savepath it will save the file in the savepath
                            {
                                StreamWriter sw = new StreamWriter(savePath);
                                sw.WriteLine(winDrawPlayLabel.Text);
                                sw.Close();
                            }
                            reset(); // running function reset
                        }
                        else if (button.Text == "O") //if the last button pressed is O then player 2 (computer) wins
                        {
                            MessageBox.Show(player2 + " Won !"); //show message box with player2 (computer) name and Won !
                            winPlayer2++; //counting wins for player2 / computer
                            countGames++; //counting games
                            if (savePath != "")//if there is savepath it will save the file in the savepath
                            {
                                StreamWriter sw = new StreamWriter(savePath);
                                sw.WriteLine(winDrawPlayLabel.Text); //it will save player name , wins , draws and how many games has been played in the save path
                                sw.Close();
                            }
                            reset(); // running function reset
                        }
                    }
                    if ((makan == false) || (secLabel.Text == secTextbox.Text)) //computer turn to move
                    {
                        ss = 0;
                        computerTurn().PerformClick(); //computer perform a click on button
                        computerTurn().Enabled = true;
                    }
                }
            }
            else if (player2.ToUpper() != "COMPUTER") //When the name of player 2 is not computer the radiobutton won't be visible
            {
                easyRadioButton.Visible = false; //radiobutton1 not visible
                hardRadioButton.Visible = false; //radiobutton2 not visible
                Button button = (Button)sender; //convert sender object into button
                if (button.Text == "" && button.Enabled == true) //if there is not text in button and button is enabled this if condition is fulfill
                {
                    if (makan) //X (player1) turn
                    {
                        button.Text = "X"; //player 1 turn
                        movement++; // counting movements
                        makan = !makan; //to make O turn
                        computerTurn().Enabled = false;
                    }
                    else //O (player2) turn
                    {
                        button.Text = "O"; //player 2 turn
                        movement++; // counting movements
                        makan = true; //to make X turn
                        computerTurn().Enabled = false;
                    }
                    if (Draw() == true) //if the draw function is fulfill the game will stop and a message box will appear 
                    {
                        MessageBox.Show("It's a draw! Try again"); //show message box with text
                        countDraw++;  //counting draws 
                        if (savePath != "")//if there is savepath it will save the file in the savepath
                        {
                            StreamWriter sw = new StreamWriter(savePath);
                            sw.WriteLine(winDrawPlayLabel.Text);
                            sw.Close();
                        }
                        reset();
                    }
                    if (Win() == true) //if the win function is fulfill the game will stop and a message box will appear showing who wins the game
                    {
                        if (button.Text == "X") //if the last button pressed is X then player 1 wins
                        {
                            MessageBox.Show(player1 + " Won !"); //show message box with player1 name and Won !
                            winPlayer1++; //counting wins for player1 
                            countGames++; //counting games
                            if (savePath != "")//if there is savepath it will save the file in the savepath
                            {
                                StreamWriter sw = new StreamWriter(savePath);
                                sw.WriteLine(winDrawPlayLabel.Text);
                                sw.Close();
                            }
                            reset(); // running function reset
                        }
                        else if (button.Text == "O") //if the last button pressed is O then player 2 (human) wins
                        {
                            MessageBox.Show(player2 + " Won !"); //show message box with player2 (human) name and Won !
                            winPlayer2++; //counting wins for player2 (human)
                            countGames++; //counting games
                            if (savePath != "")//if there is savepath it will save the file in the savepath
                            {
                                StreamWriter sw = new StreamWriter(savePath);
                                sw.WriteLine(winDrawPlayLabel.Text);
                                sw.Close();
                            }
                            reset(); // running function reset
                        }
                    }
                    if (secLabel.Text == secTextbox.Text) //computer turn to move
                    {
                        ss = 0;
                        computerTurn().PerformClick(); //computer perform a click on button
                        computerTurn().Enabled = true;
                    }
                }
            }
        }
        private void save() //function save
        {
            if (MessageBox.Show("Do you want to save this game history", "Save file", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    savePath = saveFileDialog1.FileName; //user choose the safe path
                    File.WriteAllText(savePath, winDrawPlayLabel.Text); //it will save player name , wins , draws and how many games has been played in the save path
                }
            }
        }
        private void open()
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                openPath = openFileDialog1.FileName;
                StreamReader read = new StreamReader(File.OpenRead(openPath));
                winDrawPlayLabel.Text = read.ReadToEnd();
                read.Dispose();
            }
        }

        private Button computerTurn() //function for computer turn
        {
            Button move = null; 
            //The difficulty is hard
            if (hardRadioButton.Checked == true) //if hardRadioButton.Checked is true and function random will run
            {
                move = toWin("O"); //computer looks for win
                if (move == null) 
                {
                    move = toBlock("X"); // computer looks for block
                     if (move == null) 
                     move = random(); //return function random
                }
            }
            //The difficulty is easy
            else if (easyRadioButton.Checked == true) //if easyRadioButton.Checked is true and function random will run
                move = random();
            //if the player doesn't select the game difficulty. The program should select easy difficulty
            else if (easyRadioButton.Checked == false) //if easyRadioButton.Checked is false radiobutton1.Checked is True and function random will run
            { 
                easyRadioButton.Checked = true;
                move = random(); 
            }
            return move; //return move
            
        }

        private Button toBlock(string mark)
        {
            mark = "X";
            //HORIZONTAL
            if ((A1.Text == mark) && (B1.Text == mark) && (C1.Text == ""))
                return C1;
            if ((B1.Text == mark) && (C1.Text == mark) && (A1.Text == ""))
                return A1;
            if ((A1.Text == mark) && (C1.Text == mark) && (B1.Text == ""))
                return B1;

            if ((A2.Text == mark) && (B2.Text == mark) && (B3.Text == ""))
                return B3;
            if ((B2.Text == mark) && (B3.Text == mark) && (A2.Text == ""))
                return A2;
            if ((A2.Text == mark) && (B3.Text == mark) && (B2.Text == ""))
                return B2;

            if ((A2.Text == mark) && (C2.Text == mark) && (C3.Text == ""))
                return C3;
            if ((C2.Text == mark) && (C3.Text == mark) && (A2.Text == ""))
                return A2;
            if ((A2.Text == mark) && (C3.Text == mark) && (C2.Text == ""))
                return C2;

            //VERTICAL
            if ((A1.Text == mark) && (A2.Text == mark) && (A2.Text == ""))
                return A2;
            if ((A2.Text == mark) && (A2.Text == mark) && (A1.Text == ""))
                return A1;
            if ((A1.Text == mark) && (A2.Text == mark) && (A2.Text == ""))
                return A2;

            if ((B1.Text == mark) && (B2.Text == mark) && (C2.Text == ""))
                return C2;
            if ((B2.Text == mark) && (C2.Text == mark) && (B1.Text == ""))
                return B1;
            if ((B1.Text == mark) && (C2.Text == mark) && (B2.Text == ""))
                return B2;

            if ((C1.Text == mark) && (B3.Text == mark) && (C3.Text == ""))
                return C3;
            if ((B3.Text == mark) && (C3.Text == mark) && (C1.Text == ""))
                return C1;
            if ((C1.Text == mark) && (C3.Text == mark) && (B3.Text == ""))
                return B3;

            //DIAGONAL
            if ((A1.Text == mark) && (B2.Text == mark) && (C3.Text == ""))
                return C3;
            if ((B2.Text == mark) && (C3.Text == mark) && (A1.Text == ""))
                return A1;
            if ((A1.Text == mark) && (C3.Text == mark) && (B2.Text == ""))
                return B2;

            if ((C1.Text == mark) && (B2.Text == mark) && (A2.Text == ""))
                return A2;
            if ((B2.Text == mark) && (A2.Text == mark) && (C1.Text == ""))
                return C1;
            if ((C1.Text == mark) && (A2.Text == mark) && (B2.Text == ""))
                return B2;

            return null;
        }
        private Button toWin(string mark)
        {
            mark = "O";
            //HORIZONTAL
            if ((A1.Text == mark) && (B1.Text == mark) && (C1.Text == ""))
                return C1;
            if ((B1.Text == mark) && (C1.Text == mark) && (A1.Text == ""))
                return A1;
            if ((A1.Text == mark) && (C1.Text == mark) && (B1.Text == ""))
                return B1;

            if ((A2.Text == mark) && (B2.Text == mark) && (B3.Text == ""))
                return B3;
            if ((B2.Text == mark) && (B3.Text == mark) && (A2.Text == ""))
                return A2;
            if ((A2.Text == mark) && (B3.Text == mark) && (B2.Text == ""))
                return B2;

            if ((A2.Text == mark) && (C2.Text == mark) && (C3.Text == ""))
                return C3;
            if ((C2.Text == mark) && (C3.Text == mark) && (A2.Text == ""))
                return A2;
            if ((A2.Text == mark) && (C3.Text == mark) && (C2.Text == ""))
                return C2;

            //VERTICAL
            if ((A1.Text == mark) && (A2.Text == mark) && (A2.Text == ""))
                return A2;
            if ((A2.Text == mark) && (A2.Text == mark) && (A1.Text == ""))
                return A1;
            if ((A1.Text == mark) && (A2.Text == mark) && (A2.Text == ""))
                return A2;

            if ((B1.Text == mark) && (B2.Text == mark) && (C2.Text == ""))
                return C2;
            if ((B2.Text == mark) && (C2.Text == mark) && (B1.Text == ""))
                return B1;
            if ((B1.Text == mark) && (C2.Text == mark) && (B2.Text == ""))
                return B2;

            if ((C1.Text == mark) && (B3.Text == mark) && (C3.Text == ""))
                return C3;
            if ((B3.Text == mark) && (C3.Text == mark) && (C1.Text == ""))
                return C1;
            if ((C1.Text == mark) && (C3.Text == mark) && (B3.Text == ""))
                return B3;

            //DIAGONAL
            if ((A1.Text == mark) && (B2.Text == mark) && (C3.Text == ""))
                return C3;
            if ((B2.Text == mark) && (C3.Text == mark) && (A1.Text == ""))
                return A1;
            if ((A1.Text == mark) && (C3.Text == mark) && (B2.Text == ""))
                return B2;

            if ((C1.Text == mark) && (B2.Text == mark) && (A2.Text == ""))
                return A2;
            if ((B2.Text == mark) && (A2.Text == mark) && (C1.Text == ""))
                return C1;
            if ((C1.Text == mark) && (A2.Text == mark) && (B2.Text == ""))
                return B2;

            return null;
        }
        private void Form1_Load(object sender, EventArgs e) //Form 1
        {
            Form2 fm = new Form2(); 
            fm.ShowDialog(); //shows form 2
            winDrawPlayLabel.Text = player1 + " : " + winPlayer1 + "     "+ player2 + " : " + winPlayer2 + Environment.NewLine + "Draws: " + countDraw + "    " + "Played: " + countGames;
            save();
        }
        bool Draw() //function doaw
        {
            if ((movement == 9) && Win() == false) //if the movement reach 9 times and win is false function draw is true
                return true;
            else //function draw is false
                return false;
        }
        bool Win()//function win
        {
            //HORIZANTAL
            if ((A1.Text == B1.Text) && (B1.Text == C1.Text) && A1.Text != "") //if text in button A1 is equal to text in button B1 adn C1 and A1.text is not equal to nothing function win is true.
                return true;
            else if ((A2.Text == B2.Text) && (B2.Text == C2.Text) && A2.Text != "")
                return true;
            else if ((A3.Text == B3.Text) && (B3.Text == C3.Text) && A3.Text != "")
                return true;
            //VERTICAL
            if ((A1.Text == A2.Text) && (A2.Text == A3.Text) && A1.Text != "")
                return true;
            else if ((B1.Text == B2.Text) && (B2.Text == B3.Text) && B1.Text != "")
                return true;
            else if ((C1.Text == C2.Text) && (C2.Text == C3.Text) && C1.Text != "")
                return true;
            //DIAGONAL
            if ((A1.Text == B2.Text) && (B2.Text == C3.Text) && A1.Text != "")
                return true;
            else if ((A3.Text == B2.Text) && (B2.Text == C1.Text) && A3.Text != "")
                return true;

            else
                return false; //if none of the if condition is fulfill this fuction is false
        }
        public Button random() //fuction random
        {
            Button button = null;
            foreach(Control C in Controls)
            {
                button = C as Button;
                if(button!=null) //button is not null
                {
                    if (button.Text == "") //if the button that has nothing (no X or O)
                        return button; //computer will make move in the button that has nothing (no X or O)
                }
            }
            return null;
        }

        public static void playerName(String name1, String name2) //to give player name using Form 2
        {
            player1 = name1; //player 1 is equal to name 
            player2 = name2; //player 1 is equal to name 
        }

        void reset() //to reset the game
        {
            makan = true; // true = X and false = O; X moves first 
            movement = 0; // counting movements
            A1.Text = B1.Text = C1.Text = A2.Text = B2.Text = C2.Text = A3.Text = B3.Text = C3.Text = ""; //clear all button
            winDrawPlayLabel.Text = player1 + " : " + winPlayer1 + "     " + player2 + " : " + winPlayer2 + Environment.NewLine + "Draws: " + countDraw + "     " +" Played: " + countGames;
        }

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e) //to create new game
        {
            Form2 fm = new Form2();
            fm.Show(); //shows form 2
            winPlayer1 = winPlayer2 = countDraw = countGames = 0; //all counts will be set to 0
            reset(); // function reset will run
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e) //to close the current form
        {
            this.Close(); //close
        }

        private void resetToolStripMenuItem_Click(object sender, EventArgs e) //to reset the game
        {
            reset(); //to reset the game
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e) //inside  help --> about
        {
            MessageBox.Show("This is Project 1 (Tic-Tac-Toe) created by Alvin", "About"); //show message box an text
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (savePath == "") //there isn't safepath so user choose the safepath
            {
                save(); //function save
            }
            else if (savePath != "") //if there is safepath it will save the file in the safepath
            {
                StreamWriter sw = new StreamWriter(savePath); 
                sw.WriteLine(winDrawPlayLabel.Text); //it will save player name , wins , draws and how many games has been played in the save path
                sw.Close(); //close
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            save(); //function save
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            ss++;
            secLabel.Text = ss.ToString();
            if (secLabel.Text == secTextbox.Text)
            {
                computerTurn().PerformClick();
                ss = 0;      
            }
        }
        private void openHistoryToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            open(); // function open
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
        }
    }
}