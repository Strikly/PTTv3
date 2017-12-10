// PTTs2.cpp : Defines the entry point for the console application.
// Jared Stemeye
// Rachel Adams
// Adam Everett
//=======
//CIS150-01 - Team Purple Turtle Turtles
//Start date: 11/12/2017
//Description: 
// This game is designed to create a maze for the user to run through. The user has the possibility of
// running into concealed mines that will force a 'limb' loss. Moves grant points, and extra points are rewarded for collecting coins 
// on each level. Finishing each level will allow the user to move on to the next level, where the size of the maze and number of mines/ coins increase.
// Scores and names are saved in a .txt file. High scores are displayed in-game.

//Notes:
//5 levels, larger board, more bombs and more coins, set bomb spawn points per level so we have a kay map to use
//level 1: 5x5 maze, 2 bombs, 1 coin
//level 2: exponential increasing, number of bombs = number of coins, bomb ratio is 3 boms to 1 coin
//bombs are not displayed to user, but the number of bombs will be told to the user
//pro level: coin surrounded by bombs except on one side, one way in one way out
//potentially bombs moving with every user move
//text file: saving player names and scores in a text file, old school arcade style high score list

//**************QUICK LEVEL RUN. COPY AND PASTE INTO GAME MOVE: ssddssddsssdsddwddsssssddwdssssdddsssssdssddddddsddasssdssssdddddwwdss


#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

int points = 0;

void titleScreen();
int intro();
void displayBoard(int rows, int cols, char board[5][5]);
void displayBoard2(int rows, int cols, char board[6][6]);
void displayBoard3(int rows, int cols, char board[7][7]);
void displayBoard4(int rows, int cols, char board[8][8]);
void displayBoard5(int rows, int cols, char board[9][9]);
int downLeft(int move);
int upRight(int move);

int main()
{
	// Coded by Rachel.
	const int wall = 178;
	const int vertGrid = 179;
	const int horGrid = 196;
	const int player = 206;
	const int exit = 175;
	const int coin = 233;
	int lives = 10;
	int moveCount;
	int nextLevel = 1;
	int inc = 0, inc2 = 0;
	char input;
	bool contP = true;
	bool play = true;
	int sel = 0;
	int sel2 = 0;
	int levelDiff;

	ifstream fileUsers;
	ifstream fileHighscores;
	string usersFile = "Users.txt";
	string highscoresFile = "Highscores.txt";
	vector<string> usersList;
	vector<int>    highscoresList;
	ofstream outFileUsers("Users.txt", ios::app);
	ofstream outFileUsers2("Highscores.txt", ios::app);
	string inputUsername;
	string user;

	system("Color 89");

	titleScreen();

	while (contP && play)
	{
		contP = true;
		lives = 10;
		nextLevel = 1;
		points = 0;

		sel = intro();

		while (contP && sel == 1 && lives == 10)
		{
			sel = intro();
			cout << setw(60) << "1:   EASY" << endl;
			cout << setw(61) << "2:  MEDIUM" << endl;
			cout << setw(60) << "3:   HARD" << endl;
			cout << setw(62) << "0: GOD MODE" << endl;
			cout << setw(70) << endl << "Choose Your Difficulty: ";
			cin >> levelDiff;

			if (levelDiff == 1)
			{
				lives = 8;
				cout << setw(50) << "You have " << lives << " limbs. You are the Spider!";
				Sleep(2500);
				system("cls");
			}
			else if (levelDiff == 2)
			{
				lives = 6;
				cout << setw(50) << "You have " << lives << " limbs. You are the Grasshopper!";
				Sleep(2500);
				system("cls");
			}
			else if (levelDiff == 3)
			{
				lives = 4;
				cout << setw(50) << "You have " << lives << " limbs. You are the Human!";
				Sleep(2500);
				system("cls");
			}
			else if (levelDiff == 0)
			{
				lives = 9999;
				cout << setw(50) << "You have " << lives << " limbs. You are a God!";
				Sleep(2500);
				system("cls");
			}
			else
			{
				lives = 0;
				cout << setw(65) << "Invalid input!" << endl;
				
			}

		}

	//===================================== Level 1 ========================================================================== Coded by Jared, Adam and Rachel.
	while (contP && lives > 0 && nextLevel == 1 && sel == 1)
	{
		moveCount = 15;
		int r = 0, c = 0;
		int mineNum = 2;
		const int rows = 5;
		const int cols = 5;
		int arraySize = rows*cols;
		nextLevel = 1;

		// Parallel arrays build. Jared.
		char bombBoard[rows][cols] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ '  ' , '  ' , 'c' , '  ', 'x' },
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ 'x' , '  ' , '  ' , '  ', (char)exit }
		};

		char board[rows][cols] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' },
			{ '  ' , '  ' , '  ' , '  ', (char)exit }
		};
		board[2][2] = (char)coin;
		board[r][c] = (char)player;

		//Game mechanics. Jared and Adam.
		while (contP && lives > 0 && nextLevel == 1)
		{

			cout << "LEVEL " << nextLevel << endl;
			cout << "Total Points: " << points << endl;
			cout << "Limbs: " << lives << "    Mine Count: " << mineNum << endl;

			displayBoard(rows, cols, board);

			//cout << "r = " << r << " and c = " << c << endl;
			cout << moveCount << " moves left. Enter a move: ";
			cin >> input;
			system("CLS");

			if (input == 's' || input == 'S')
			{
				downLeft(r);
				r = downLeft(r);
				board[r][c] = (char)player;
				board[r - 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard[r][c] = 'd';
				}
				if (bombBoard[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard[r][c] = 'n';
					board[r][c] = (char)player;
				}
			}
			else if (input == 'w' || input == 'W')
			{
				upRight(r);
				r = upRight(r);
				board[r][c] = (char)player;
				board[r + 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard[r][c] = 'd';
				}
				if (bombBoard[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard[r][c] = 'n';
					board[r][c] = (char)player;
				}
			}
			else if (input == 'd' || input == 'D')
			{
				downLeft(c);
				c = downLeft(c);
				board[r][c] = (char)player;
				board[r][c - 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard[r][c] = 'd';
				}
				if (bombBoard[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard[r][c] = 'n';
					board[r][c] = (char)player;
				}
			}
			else if (input == 'a' || input == 'A')
			{
				upRight(c);
				c = upRight(c);
				board[r][c] = (char)player;
				board[r][c + 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard[r][c] = 'd';
				}
				if (bombBoard[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard[r][c] = 'n';
					board[r][c] = (char)player;
				}
			}
			else if (input == 'p' || input == 'P')
			{
				contP = false;
			}
			else if (input == 'm' || input == 'M')
			{
				nextLevel = 0;
				sel = 0;
				intro();
			}
			else
			{
				cout << "Invalid input. " << endl;
			}
			if (bombBoard[r][c] == 'x')
			{
				lives--;
				mineNum--;
				cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
			}
			if (moveCount <= 0)
			{
				cout << "You ran out of moves! On to the next level!" << endl;
				Sleep(2000);
				system("CLS");
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}
				nextLevel++;
			}
			for (int i = 0; i < arraySize; i++)
			{
				if (board[r][c] == board[rows - 1][cols - 1])
				{
					system("CLS");
					cout << "You reached the Exit! On to the next level!. " << endl;
					cout << "Total Points: " << points << endl;
					Sleep(2000);
					system("CLS");
					while (r > 0)
					{
						r--;
					}
					while (c > 0)
					{
						c--;
					}
					nextLevel++;
				}
				else
				{

				}
			}
			// Out of Bounds Checks. Adam.
			while (r <= -1)
			{
				cout << "You hit a Wall. Oops." << endl;
				r++;
				board[r][c] = (char)player;
				board[r - 1][c] = '  ';
			}
			while (c <= -1)
			{
				cout << "You hit a Wall. Oops." << endl;
				c++;
				board[r][c] = (char)player;
				board[r][c - 1] = '  ';
			}
			while (r >= rows)
			{
				cout << "You hit a Wall. Oops." << endl;
				r--;
				board[r][c] = (char)player;
				board[r + 1][c] = '  ';
			}
			while (c >= rows)
			{
				cout << "You hit a Wall. Oops." << endl;
				c--;
				board[r][c] = (char)player;
				board[r][c + 1] = '  ';
			}
		}
		//=================================================== Level 2 ==========================================================
		moveCount = 20;
		int mineNum2 = 4;
		const int rows2 = 6;
		const int cols2 = 6;
		int arraySize2 = rows2 * cols2;

		char bombBoard2[rows2][cols2] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , 'c' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', 'x' , '  ' },
			{ '  ' , 'c' , 'x' , 'c', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , 'x' , '  ' , '  ', 'x' , (char)exit }
		};

		char board2[rows2][cols2] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , (char)exit }
		};

		board2[0][5] = (char)coin;
		board2[3][1] = (char)coin;
		board2[3][3] = (char)coin;
		board2[r][c] = (char)player;
		while (contP && lives > 0 && nextLevel == 2)
		{
			cout << "LEVEL " << nextLevel << endl;
			cout << "Total Points: " << points << endl;
			cout << "Limbs: " << lives << "    Mine Count: " << mineNum2 << endl;

			displayBoard2(rows2, cols2, board2);

			cout << moveCount << " moves left. enter a move: ";
			cin >> input;
			system("cls");

			if (input == 's' || input == 's')
			{
				downLeft(r);
				r = downLeft(r);
				board2[r][c] = (char)player;
				board2[r - 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard2[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard2[r][c] = 'd';
				}
				if (bombBoard2[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard2[r][c] = 'n';
					board2[r][c] = (char)player;
				}
			}
			else if (input == 'w' || input == 'w')
			{
				upRight(r);
				r = upRight(r);
				board2[r][c] = (char)player;
				board2[r + 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard2[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard2[r][c] = 'd';
				}
				if (bombBoard2[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard2[r][c] = 'n';
					board2[r][c] = (char)player;
				}
			}
			else if (input == 'd' || input == 'd')
			{
				downLeft(c);
				c = downLeft(c);
				board2[r][c] = (char)player;
				board2[r][c - 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard2[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard2[r][c] = 'd';
				}
				if (bombBoard2[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard2[r][c] = 'n';
					board2[r][c] = (char)player;
				}
			}
			else if (input == 'a' || input == 'a')
			{
				upRight(c);
				c = upRight(c);
				board2[r][c] = (char)player;
				board2[r][c + 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard2[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard2[r][c] = 'd';
				}
				if (bombBoard2[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard2[r][c] = 'n';
					board2[r][c] = (char)player;
				}
			}
			else if (input == 'p' || input == 'p')
			{
				contP = false;
			}
			else
			{
				cout << "Invalid input. " << endl;
			}
			if (bombBoard2[r][c] == 'x')
			{
				lives--;
				mineNum--;
				cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
			}
			if (moveCount <= 0)
			{
				cout << "You ran out of moves! On to the next level!" << endl;
				Sleep(2000);
				system("CLS");
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}

				nextLevel++;
			}
			// Exit Level Loop - Adam
			for (int i = 0; i < arraySize2; i++)
			{
				if (board2[r][c] == board2[rows2 - 1][cols2 - 1])
				{
					system("cls");
					cout << "You reached the exit. On to the next level!. " << endl;
					cout << "Total points: " << points << endl;
					Sleep(2000);
					system("CLS");
					while (r > 0)
					{
						r--;
					}
					while (c > 0)
					{
						c--;
					}
					nextLevel++;
				}
				else
				{

				}
				// Out of Bounds Checks. Adam.
				while (r <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					r++;
					board2[r][c] = (char)player;
					board2[r - 1][c] = '  ';
				}
				while (c <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					c++;
					board2[r][c] = (char)player;
					board2[r][c - 1] = '  ';
				}
				while (r >= rows2)
				{
					cout << "You hit a Wall. Oops." << endl;
					r--;
					board2[r][c] = (char)player;
					board2[r + 1][c] = '  ';
				}
				while (c >= rows2)
				{
					cout << "You hit a Wall. Oops." << endl;
					c--;
					board2[r][c] = (char)player;
					board2[r][c + 1] = '  ';
				}
			}
		}
		//=================================================== Level 3 ==========================================================
		//Reformated by Jared and Rachel (11/29/2017)
		moveCount = 25;
		int mineNum3 = 5;
		const int rows3 = 7;
		const int cols3 = 7;
		int arraySize3 = rows3 * cols3;

		char bombBoard3[rows3][cols3] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , 'x' , '  ' , '  ', 'c' , '  ' , 'x' },
			{ '  ' , '  ' , 'c' , '  ', '  ' , '  ' , '  ' },
			{ 'c' , '  ' , '  ' , '  ', '  ' , 'x' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', 'x' , '  ' , '  ' },
			{ '  ' , 'x' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , 'c', '  ', '  ' , (char)exit }
		};

		char board3[rows3][cols3] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ', '  ' , (char)exit }
		};

		board3[1][4] = (char)coin;
		board3[2][2] = (char)coin;
		board3[3][0] = (char)coin;
		board3[6][3] = (char)coin;
		board3[r][c] = (char)player;
		while (contP && lives > 0 && nextLevel == 3)
		{
			cout << "LEVEL " << nextLevel << endl;
			cout << "Total Points: " << points << endl;
			cout << "Limbs: " << lives << "    Mine Count: " << mineNum3 << endl;

			displayBoard3(rows3, cols3, board3);

			cout << moveCount << " moves left. enter a move: ";
			cin >> input;
			system("cls");

			if (input == 's' || input == 's')
			{
				downLeft(r);
				r = downLeft(r);
				board3[r][c] = (char)player;
				board3[r - 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard3[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard3[r][c] = 'd';
				}
				if (bombBoard3[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard3[r][c] = 'n';
					board3[r][c] = (char)player;
				}
			}
			else if (input == 'w' || input == 'w')
			{
				upRight(r);
				r = upRight(r);
				board3[r][c] = (char)player;
				board3[r + 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard3[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard3[r][c] = 'd';
				}
				if (bombBoard3[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard3[r][c] = 'n';
					board3[r][c] = (char)player;
				}
			}
			else if (input == 'd' || input == 'd')
			{
				downLeft(c);
				c = downLeft(c);
				board3[r][c] = (char)player;
				board3[r][c - 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard3[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard3[r][c] = 'd';
				}
				if (bombBoard3[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard3[r][c] = 'n';
					board3[r][c] = (char)player;
				}
			}
			else if (input == 'a' || input == 'a')
			{
				upRight(c);
				c = upRight(c);
				board3[r][c] = (char)player;
				board3[r][c + 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard3[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard3[r][c] = 'd';
				}
				if (bombBoard3[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard3[r][c] = 'n';
					board3[r][c] = (char)player;
				}
			}
			else if (input == 'p' || input == 'p')
			{
				contP = false;
			}
			else
			{
				cout << "Invalid input. " << endl;
			}
			if (bombBoard3[r][c] == 'x')
			{
				lives--;
				mineNum--;
				cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
			}
			if (moveCount <= 0)
			{
				cout << "You ran out of moves! On to the next level!" << endl;
				Sleep(2000);
				system("CLS");
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}

				nextLevel++;
			}
			// Exit Level Loop - Adam
			for (int i = 0; i < arraySize3; i++)
			{
				if (board3[r][c] == board3[rows3 - 1][cols3 - 1])
				{
					system("cls");
					cout << "You reached the exit. On to the next level!. " << endl;
					cout << "Total points: " << points << endl;
					Sleep(2000);
					system("CLS");
					while (r > 0)
					{
						r--;
					}
					while (c > 0)
					{
						c--;
					}
					nextLevel++;
				}
				else
				{

				}
				// Out of Bounds Checks. Adam.
				while (r <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					r++;
					board3[r][c] = (char)player;
					board3[r - 1][c] = '  ';
				}
				while (c <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					c++;
					board3[r][c] = (char)player;
					board3[r][c - 1] = '  ';
				}
				while (r >= rows3)
				{
					cout << "You hit a Wall. Oops." << endl;
					r--;
					board3[r][c] = (char)player;
					board3[r + 1][c] = '  ';
				}
				while (c >= rows3)
				{
					cout << "You hit a Wall. Oops." << endl;
					c--;
					board3[r][c] = (char)player;
					board3[r][c + 1] = '  ';
				}
			}
		}
		//=================================================== Level 4 ==========================================================
		//Reformated by Rachel (11/29/2017)
		moveCount = 30;
		int mineNum4 = 6;
		const int rows4 = 8;
		const int cols4 = 8;
		int arraySize4 = rows4 * cols4;

		char bombBoard4[rows4][cols4] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , 'x' , '  ' },
			{ 'c' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , 'c' },
			{ '  ' , '  ' , '  ' , '  ', 'c' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , 'x' , '  ', '  ' , 'x' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , 'x' , '  ', '  ' , '  ' , 'x' , '  ' },
			{ 'x' , 'c' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', 'c', '  ' , '  ' , (char)exit }
		};

		char board4[rows4][cols4] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ', '  ' , '  ' , (char)exit }
		};

		board4[1][0] = (char)coin;
		board4[1][7] = (char)coin;
		board4[2][4] = (char)coin;
		board4[6][1] = (char)coin;
		board4[7][4] = (char)coin;
		board4[r][c] = (char)player;
		while (contP && lives > 0 && nextLevel == 4)
		{
			cout << "LEVEL " << nextLevel << endl;
			cout << "Total Points: " << points << endl;
			cout << "Limbs: " << lives << "    Mine Count: " << mineNum4 << endl;

			displayBoard4(rows4, cols4, board4);

			cout << moveCount << " moves left. enter a move: ";
			cin >> input;
			system("cls");

			if (input == 's' || input == 's')
			{
				downLeft(r);
				r = downLeft(r);
				board4[r][c] = (char)player;
				board4[r - 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard4[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard4[r][c] = 'd';
				}
				if (bombBoard4[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard4[r][c] = 'n';
					board4[r][c] = (char)player;
				}
			}
			else if (input == 'w' || input == 'w')
			{
				upRight(r);
				r = upRight(r);
				board4[r][c] = (char)player;
				board4[r + 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard4[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard4[r][c] = 'd';
				}
				if (bombBoard4[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard4[r][c] = 'n';
					board4[r][c] = (char)player;
				}
			}
			else if (input == 'd' || input == 'd')
			{
				downLeft(c);
				c = downLeft(c);
				board4[r][c] = (char)player;
				board4[r][c - 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard4[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard4[r][c] = 'd';
				}
				if (bombBoard4[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard4[r][c] = 'n';
					board4[r][c] = (char)player;
				}
			}
			else if (input == 'a' || input == 'a')
			{
				upRight(c);
				c = upRight(c);
				board4[r][c] = (char)player;
				board4[r][c + 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard4[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard4[r][c] = 'd';
				}
				if (bombBoard4[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard4[r][c] = 'n';
					board4[r][c] = (char)player;
				}
			}
			else if (input == 'p' || input == 'p')
			{
				contP = false;
			}
			else
			{
				cout << "Invalid input. " << endl;
			}
			if (bombBoard4[r][c] == 'x')
			{
				lives--;
				mineNum--;
				cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
			}
			if (moveCount <= 0)
			{
				cout << "You ran out of moves! On to the next level!" << endl;
				Sleep(2000);
				system("CLS");
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}

				nextLevel++;
			}
			// Exit Level Loop - Adam
			for (int i = 0; i < arraySize4; i++)
			{
				if (board4[r][c] == board4[rows4 - 1][cols4 - 1])
				{
					system("cls");
					cout << "You reached the exit. On to the next level!. " << endl;
					cout << "Total points: " << points << endl;
					Sleep(2000);
					system("CLS");
					while (r > 0)
					{
						r--;
					}
					while (c > 0)
					{
						c--;
					}
					nextLevel++;
				}
				else
				{

				}
				// Out of Bounds Checks. Adam.
				while (r <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					r++;
					board4[r][c] = (char)player;
					board4[r - 1][c] = '  ';
				}
				while (c <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					c++;
					board4[r][c] = (char)player;
					board4[r][c - 1] = '  ';
				}
				while (r >= rows4)
				{
					cout << "You hit a Wall. Oops." << endl;
					r--;
					board4[r][c] = (char)player;
					board4[r + 1][c] = '  ';
				}
				while (c >= rows4)
				{
					cout << "You hit a Wall. Oops." << endl;
					c--;
					board4[r][c] = (char)player;
					board4[r][c + 1] = '  ';
				}
			}
		}

		//=================================================== Level 5 ==========================================================
		//Reformated by Rachel (11/29/2017)
		moveCount = 35;
		int mineNum5 = 7;
		const int rows5 = 9;
		const int cols5 = 9;
		int arraySize5 = rows5 * cols5;

		char bombBoard5[rows5][cols5] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , 'c' , '  ' , 'x' },
			{ '  ' , '  ' , 'c' , 'x', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , 'x' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , 'c' , '  ' , '  ', '  ' , 'c' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , 'x' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , 'c' , '  ' },
			{ 'x' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ 'x' , '  ' , 'c' , '  ', '  ', 'x' , '  ' , '  ' , (char)exit }
		};

		char board5[rows5][cols5] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' , '  ' , '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ', '  ' , '  ' , '  ' , (char)exit }
		};

		board5[0][6] = (char)coin;
		board5[1][2] = (char)coin;
		board5[4][1] = (char)coin;
		board5[4][5] = (char)coin;
		board5[6][7] = (char)coin;
		board5[8][2] = (char)coin;
		board5[r][c] = (char)player;
		while (contP && lives > 0 && nextLevel == 5)
		{
			cout << "LEVEL " << nextLevel << endl;
			cout << "Total Points: " << points << endl;
			cout << "Limbs: " << lives << "    Mine Count: " << mineNum5 << endl;

			displayBoard5(rows5, cols5, board5);

			cout << moveCount << " moves left. enter a move: ";
			cin >> input;
			system("cls");

			if (input == 's' || input == 's')
			{
				downLeft(r);
				r = downLeft(r);
				board5[r][c] = (char)player;
				board5[r - 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard5[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard5[r][c] = 'd';
				}
				if (bombBoard5[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard5[r][c] = 'n';
					board5[r][c] = (char)player;
				}
			}
			else if (input == 'w' || input == 'w')
			{
				upRight(r);
				r = upRight(r);
				board5[r][c] = (char)player;
				board5[r + 1][c] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard5[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard5[r][c] = 'd';
				}
				if (bombBoard5[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard5[r][c] = 'n';
					board5[r][c] = (char)player;
				}
			}
			else if (input == 'd' || input == 'd')
			{
				downLeft(c);
				c = downLeft(c);
				board5[r][c] = (char)player;
				board5[r][c - 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard5[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard5[r][c] = 'd';
				}
				if (bombBoard5[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard5[r][c] = 'n';
					board5[r][c] = (char)player;
				}
			}
			else if (input == 'a' || input == 'a')
			{
				upRight(c);
				c = upRight(c);
				board5[r][c] = (char)player;
				board5[r][c + 1] = '  ';
				moveCount--;
				points += 10;
				if (bombBoard5[r][c] == 'x')
				{
					lives--;
					mineNum--;
					cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
					bombBoard5[r][c] = 'd';
				}
				if (bombBoard5[r][c] == 'c')
				{
					cout << "Coin acquired!" << endl;
					points = points + 100;
					bombBoard5[r][c] = 'n';
					board5[r][c] = (char)player;
				}
			}
			else if (input == 'p' || input == 'P')
			{
				contP = false;
			}
			else
			{
				cout << "Invalid input. " << endl;
			}
			if (bombBoard5[r][c] == 'x')
			{
				lives--;
				mineNum--;
				cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
			}
			if (moveCount <= 0)
			{
				cout << "You ran out of moves!" << endl;
				Sleep(2000);
				system("CLS");
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}

				nextLevel++;
			}
			// Exit Level Loop - Adam
			for (int i = 0; i < arraySize5; i++)
			{
				if (board5[r][c] == board5[rows5 - 1][cols5 - 1])
				{
					system("cls");
					cout << "You reached the end with " << lives << " limbs attached!" << endl;
					cout << "Total points: " << points << endl;
					Sleep(3000);
					system("CLS");
					while (r > 0)
					{
						r--;
					}
					while (c > 0)
					{
						c--;
					}
					nextLevel++;
				}
				else
				{

				}
				// Out of Bounds Checks. Adam.
				while (r <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					r++;
					board5[r][c] = (char)player;
					board5[r - 1][c] = '  ';
				}
				while (c <= -1)
				{
					cout << "You hit a Wall. Oops." << endl;
					c++;
					board5[r][c] = (char)player;
					board5[r][c - 1] = '  ';
				}
				while (r >= rows5)
				{
					cout << "You hit a Wall. Oops." << endl;
					r--;
					board5[r][c] = (char)player;
					board5[r + 1][c] = '  ';
				}
				while (c >= rows5)
				{
					cout << "You hit a Wall. Oops." << endl;
					c--;
					board5[r][c] = (char)player;
					board5[r][c + 1] = '  ';
				}
			}		
		}
		
		if (contP)
		{
			int savedPoints = points;



			cout << "Your score was: " << points << " points." << endl;
			cout << "Enter your initials: ";
			cin >> inputUsername;

			outFileUsers << endl << inputUsername;
			outFileUsers2 << endl << savedPoints;

			usersList.push_back(inputUsername);
			highscoresList.push_back(savedPoints);
		}
	}

	}
	outFileUsers.close();
	outFileUsers2.close();
	cout << endl << "You're finished Buddy! " << endl << endl;

	system("pause");
	return 0;
}

void titleScreen() // Added by Jared. ASCII art generated using: patorjk.com/software/taag/
{
	system("Color 89");
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout <<
		R"(                   _______  _________  _         _______     _______   _______   _______    _______  
	          (       ) \__   __/ ( (    /| (  ____ \   (       ) (  ___  ) /  ___  )  ( ____  \ 
	          | () () |    ) (    |  \  ( | | (    \/   | () () | | (   ) | \/   )  |  | (    \/
	          | || || |    | |    |   \ | | | (__       | || || | | (___) |     /   )  | (__    
	          | |(_)| |    | |    | (\ \) | |  __)      | |(_)| | |  ___  |    /   /   |  __)   
                  | |   | |    | |    | | \   | | (         | |   | | | (   ) |   /   /    | (      
	          | )   ( | ___) (___ | )  \  | | (____/\   | )   ( | | )   ( |  /   (_/\  | (____/\ 
	          |/     \| \_______/ |/    )_) (_______/   |/     \| |/     \| (_______/  (_______/ )" << endl << endl;

	cout << R"(                                                      BY: 
                                                      RACHEL ADAMS
                                                      ADAM EVERETT
                                                      JARED STEMEYE)" << endl;
	Sleep(3500);
	system("cls");
}

int intro() //Written by Rachel

{
	// Borrowed ifstream variables from CIS150_FileReadingForGames by Prof. Moore. - Jared
	ifstream fileUsers;
	ifstream fileHighscores;
	string usersFile = "Users.txt";
	string highscoresFile = "Highscores.txt";
	string user;
	vector<string> usersList;
	vector<int>    highscoresList;
	const int coin = 233;
	const int bomb = 235;
	const int player = 206;
	int selection = 0;
	//int sel = 0;
	bool contP = true;


	while (contP && selection == 0)
	{
		system("Color 89");
		cout << endl;
		cout << setw(69) << "Welcome To Mine Maze" << endl; //centered and bigger text, to add later. 
		cout << endl;
		cout << setw(65) << "Menu Options" << endl; //centered and slightly bigger text, classic video game style
		cout << setw(71) << "Enter 1 to Start the Maze" << endl;
		cout << setw(72) << "Enter 2 to View High Scores" << endl;
		cout << setw(75) << "Enter 3 to View the Instructions" << endl;
		cout << setw(77) << "Enter P to Exit The Program At Any Time" << endl;
		cout << endl << setw(69) << "Enter your selection: ";
		cin >> selection;
		cout << endl;

		if (contP && selection == 1)
		{
			cout << "You Have Chosen Option 1!" << endl;
			selection = 1;
			Sleep(900);
			system("CLS");
			return selection;
			
		}

		if (contP && selection == 2)
		{
			cout << "You Have Chosen Option 2!" << endl;
			Sleep(900);
			system("CLS");
			fileUsers.open(usersFile);
			fileHighscores.open(highscoresFile);
			int savedPoints = points;

			cout << setw(67) << "TOP HIGH SCORES:" << endl;
			cout << endl;
			if (fileUsers)
			{
				while (fileUsers >> user)
				{
					usersList.push_back(user);
				}
				fileUsers.close();
			}
			else
			{
				cout << "Users.txt did not open correctly" << endl;
			}

			if (fileHighscores)
			{
				while (fileHighscores >> savedPoints)
				{
					highscoresList.push_back(savedPoints);
				}
				fileUsers.close();
			}
			else
			{
				cout << "Highscores.txt did not open correctly" << endl;
			}


			for (int i = 0; i < 10; i++)
			{
				cout << setw(55) << usersList.at(i) << setw(10) << highscoresList.at(i) << endl;
			}			
		}

		else if (contP && selection == 3)
		{
			cout << "You Have Chosen Option 3!" << endl;
			Sleep(900);
			system("CLS");
			cout << setw(100) << "The objective of Mine Maze is to get from the entrance to the exit alive." << endl << endl;
			cout << setw(68) << "This is you --> " << (char)player << endl;
			cout << setw(74) << "Use WASD to move your player:" << endl;
			cout << setw(100) << "W will take you up, S will take you down, A and D will take you left and right." << endl;
			cout << endl;
			cout << setw(80) << "There are concealed mines on each level. " << endl;
			cout << setw(90) << "If your player come into contact with a mine, a limb is lost." << endl;
			cout << setw(77) << "Lose all limbs and the game is over." << endl;
			cout << endl;
			cout << setw(105) << "The good news though, is that there are coins on the map to make your journey worthwhile." << endl;
			cout << setw(46) << "For every coin (" << char(coin) << ") you collect, 100 points is added to your score. " << endl;
			cout << endl;
			cout << setw(100) << "Speaking of scores, paying attention to your Moves Left can also help you out. " << endl;
			cout << setw(95) << "Be efficient and collect your coins and you might just find your name" << endl;
			cout << setw(70) << "on our high score list!";
			cout << endl;
			cout << endl;
			
			cout << setw(80) << "Watch out for those mines, and Good Luck!" << endl;
			cout << endl;		
		}
		if (contP && selection == 'p' || selection == 'P');
		{
			contP = false;
			selection = -1;
		}

		if (contP && selection != 1 && selection != 2 && selection != 3 && selection != 'p' && selection != 'P')
		{
			cout << "That doesn't work, pick a valid option." << endl;
			cin >> selection;
		}
	}
}

// displayBoard (Jared and Adam)
void displayBoard(int rows, int cols, char board[5][5])
{
	HANDLE  console;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int wall = 178;
	for (int i = 0; i < (rows + 26); i++)
	{
		cout << (char)wall;
	}
	for (int i = 0; i < rows; i++)
	{
		// cell divider
		cout << endl << (char)wall;
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] == char(233))
			{
				
				cout << " _";
				SetConsoleTextAttribute(console, 142);
				cout << board[i][j];
				SetConsoleTextAttribute(console, 137);
				cout << "_ ";
				
			}
			else
			{
				cout << " _" << board[i][j] << "_ ";
			}
			
			if (j < (cols - 1))
			{
				cout << "|";
			}
		
		}
		if (i != rows - 1)
		{
			cout << (char)wall;
		}
		else
		{
			//cout << " _ ";
		}
	}
	cout << endl;
	for (int i = 0; i < (rows + 26); i++)
	{
		cout << (char)wall;
	}
	cout << endl;
}

// displayBoard2 (Pasted and edited by Jared) 
void displayBoard2(int rows, int cols, char board[6][6])
{
	HANDLE  console;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int wall = 178;
	for (int i = 0; i < (rows + 31); i++)
	{
		cout << (char)wall;
	}
	for (int i = 0; i < rows; i++)
	{
		// cell divider
		cout << endl << (char)wall;
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] == char(233))
			{

				cout << " _";
				SetConsoleTextAttribute(console, 142);
				cout << board[i][j];
				SetConsoleTextAttribute(console, 137);
				cout << "_ ";

			}
			else
			{
				cout << " _" << board[i][j] << "_ ";
			}

			if (j < (cols - 1))
			{
				cout << "|";
			}

		}
		if (i != rows - 1)
		{
			cout << (char)wall;
		}
		else
		{
			//cout << " _ ";
		}
	}
	cout << endl;
	for (int i = 0; i < (rows + 31); i++)
	{
		cout << (char)wall;
	}
	cout << endl;
}
// displayBoard3 (Pasted and edited by Jared) 
void displayBoard3(int rows, int cols, char board[7][7])
{
	HANDLE  console;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int wall = 178;
	for (int i = 0; i < (rows + 36); i++)
	{
		cout << (char)wall;
	}
	for (int i = 0; i < rows; i++)
	{
		// cell divider
		cout << endl << (char)wall;
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] == char(233))
			{

				cout << " _";
				SetConsoleTextAttribute(console, 142);
				cout << board[i][j];
				SetConsoleTextAttribute(console, 137);
				cout << "_ ";

			}
			else
			{
				cout << " _" << board[i][j] << "_ ";
			}

			if (j < (cols - 1))
			{
				cout << "|";
			}

		}
		if (i != rows - 1)
		{
			cout << (char)wall;
		}
		else
		{
			//cout << " _ ";
		}
	}
	cout << endl;
	for (int i = 0; i < (rows + 36); i++)
	{
		cout << (char)wall;
	}
	cout << endl;
}

//Display board pasted and edited by Rachel (11/29/2017)
void displayBoard4(int rows, int cols, char board[8][8])
{
	HANDLE  console;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int wall = 178;
	for (int i = 0; i < (rows + 41); i++)
	{
		cout << (char)wall;
	}
	for (int i = 0; i < rows; i++)
	{
		// cell divider
		cout << endl << (char)wall;
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] == char(233))
			{

				cout << " _";
				SetConsoleTextAttribute(console, 142);
				cout << board[i][j];
				SetConsoleTextAttribute(console, 137);
				cout << "_ ";

			}
			else
			{
				cout << " _" << board[i][j] << "_ ";
			}

			if (j < (cols - 1))
			{
				cout << "|";
			}

		}
		if (i != rows - 1)
		{
			cout << (char)wall;
		}
		else
		{
			//cout << " _ ";
		}
	}
	cout << endl;
	for (int i = 0; i < (rows + 41); i++)
	{
		cout << (char)wall;
	}
	cout << endl;
}
//Display board pasted and edited by Rachel (11/29/2017)
void displayBoard5(int rows, int cols, char board[9][9])
{
	HANDLE  console;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int wall = 178;
	for (int i = 0; i < (rows + 46); i++)
	{
		cout << (char)wall;
	}
	for (int i = 0; i < rows; i++)
	{
		// cell divider
		cout << endl << (char)wall;
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] == char(233))
			{

				cout << " _";
				SetConsoleTextAttribute(console, 142);
				cout << board[i][j];
				SetConsoleTextAttribute(console, 137);
				cout << "_ ";

			}
			else
			{
				cout << " _" << board[i][j] << "_ ";
			}

			if (j < (cols - 1))
			{
				cout << "|";
			}

		}
		if (i != rows - 1)
		{
			cout << (char)wall;
		}
		else
		{
			//cout << " _ ";
		}
	}
	cout << endl;
	for (int i = 0; i < (rows + 46); i++)
	{
		cout << (char)wall;
	}
	cout << endl;
}

// Move Functions (Adam and Jared)

int downLeft(int move)
{
	move = move + 1;
	return move;

}

int upRight(int move)
{
	move = move - 1;
	return move;
}