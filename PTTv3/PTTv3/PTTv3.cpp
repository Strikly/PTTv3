
// PTTs2.cpp : Defines the entry point for the console application.
// Jared Stemeye
// Rachel Adams
// Adam Everett
//=======
//CIS150-01 - Team Purple Turtle Turtles
//Start date: 11/12/2017
//Description: This game is designed to create a maze for the user to run through. The maze walls will be invisibile, and the
// user has the posibility of running into bombs that will end their life and extra lifes which will add an addition life
// to their life counter. Finishing the first level will allow the user to move on to the next level, where the size of the
// maze and number of items increases.


//10 levels in difficulty, more bombs and more coins, set bomb spawn points per level so we have a kay map to use
//level 1: 5x5 maze, 2 bombs, 1 coin
//level 2: exponential increaming, number of bombs = number of coins, bomb ratio is 3 boms to 1 coin
//bombs are not displayed to user, but the number of bombs will be told to the user
//pro level: coin surrounded by bombs except on one side, one way in one way out
//potentially bombs moving with every user move
//text file: saving player names and scores in a text file, old school arcade style high score list


#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

void intro() //Written by Rachel

{
	const int coin = 233;
	const int bomb = 235;
	char selection;

	cout << setw(60) << "The Maze" << endl; //centered and bigger text, to add later. 
	cout << setw(62) << "Menu Options" << endl; //centered and slightly bigger text, classic video game style
	cout << setw(68) << "Press 1 to Start the Maze" << endl;
	cout << setw(69) << "Press 2 to view High Scores" << endl;
	cout << setw(74) << "Press 3 to view Intro and Instructions" << endl;
	cout << setw(59) << "Press 4" << endl; //maybe include this in black text or text to match the background, easter egg of a graphic and a meme song?
	cin >> selection;

	if (selection == '1')
	{
		cout << "You Have Chosen Option 1!" << endl;
		system("CLS");
		
	}

	if (selection == '2')
	{
		cout << "You Have Chosen Option 2!" << endl;
		//view high score file

	}

	if (selection == '3')
	{
		cout << "Welcome to The Maze! The obvective is to get from the enterance to the exit alive. Sound simple, right?" << endl;
		cout << "Maybe, maybe not." << endl;
		cout << "You see, there will be obstacles in your way, ones that might be invisible. Well, yeah, they're invisible." << endl;
		cout << "They're bombs." << endl;
		cout << "Oops." << endl;
		cout << (char)bomb << " " << (char)bomb << " " << (char)bomb << " " << (char)bomb << " " << (char)bomb << " " << (char)bomb << endl;
		cout << "The good news though, is that there are non-invisible coins to make your journey worthwhile." << endl;
		cout << "For every coin you collect, 100 points are added to your score." << endl;
		cout << (char)coin << " " << (char)coin << " " << (char)coin << " " << (char)coin << " " << (char)coin << " " << (char)coin << endl;
		cout << "Speaking of scores, taking less steps can also help you out. Make a lot of unnessary moves and your score" << endl;
		cout << "might not be as high as you'd like it. Be efficient and collect your coins and you might just find your name" << endl;
		cout << "on our high score list.";
		cout << endl;
		cout << "Use WASD to move: W will take you up, S will take you down, A and D will take you left and right." << endl;
		cout << "Watch out for those bombs, and Good Luck!" << endl;
		cout << endl;

		cout << setw(68) << "Press 1 to Start the Maze" << endl;
		cout << setw(69) << "Press 2 to view High Scores" << endl;
		cout << setw(74) << "Press 3 to view Intro and Instructions" << endl;
		cout << setw(59) << "Press 4" << endl;
		cin >> selection;
	}

	if (selection == '4')
	{

		//cout << "3";
		//memeing it, memeing it so hard
	}

	if (selection != '1' && selection != '2' && selection != '3' && selection != '4')
	{
		cout << "That doesn't work, pick a valid option." << endl;
		cin >> selection;
	}

}

// displayBoard (Jared and Adam)
void displayBoard(int rows, int cols, char board[5][5])
{
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
			cout << " _" << board[i][j] << "_ ";
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

// displayBoard (Pasted and edited by Jared) 
void displayBoard2(int rows, int cols, char board[6][6])
{
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
			cout << " _" << board[i][j] << "_ ";
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

int main()
{
	// Coded by Rachel.
	const int wall = 178;
	const int vertGrid = 179;
	const int horGrid = 196;
	const int player = 206;
	const int exit = 175;
	const int coin = 233;
	int points = 0;
	int lives = 3;
	int moveCount;
	int nextLevel = 1;

	int inc = 0;
	char input;
	char mine = 255;
	bool contP = true;

	intro();

	//===================================== Level 1 ========================================================================== Coded by Jared, Adam and Rachel.
	moveCount = 15;
	int r = 0, c = 0;
	const int rows = 5;
	const int cols = 5;
	int mineNum = 2;
	
	// Parallel arrays build. Jared.
	char bombBoard[rows][cols] = {
		{ '  ' , '  ' , '  ' , '  ', '  ' },
		{ '  ' , '  ' , '  ' , '  ', '  ' },
		{ '  ' , '  ' , 'c' , '  ', 'x' },
		{ '  ' , '  ' , '  ' , '  ', '  ' },
		{ 'x' , '  ' , '  ' , '  ', (char)exit }
	};

	int arraySize = rows*cols;
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
		cout << "Mine Count: " << mineNum << endl;

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
		else
		{
			cout << "Invalid input. " << endl;
		}
		if (bombBoard[r][c] == 'x')
		{
			lives--;
			cout << "You hit a mine! Limb lost! " << endl << lives << " left! " << endl;
		}
		if (moveCount <= -1)
		{
			cout << "You ran out and moves and lost a limb. " << endl;
			lives--;
			cout << lives << " limbs left. On to the next Level" << endl;
			while (r > 0)
			{
				r--;
			}
			while (c > 0)
			{
				c--;
			}
			moveCount = 15;
			nextLevel++;
		}
		for (int i = 0; i < arraySize; i++)
		{
			if (board[r][c] == board[rows - 1][cols - 1])
			{
				system("CLS");
				cout << "You reached the Exit! On to the next Level. " << endl;
				cout << "Total Points: " << points << endl;
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}
				moveCount = 15;
				nextLevel++;
			}
			else
			{

			}
		}
		// Out of Bounds Checks. Adam.
		while (r <= -1)
		{
			cout << "You hit a Wall." << endl;
			r++;
			board[r][c] = (char)player;
			board[r - 1][c] = '  ';
		}
		while (c <= -1)
		{
			cout << "You hit a Wall." << endl;
			c++;
			board[r][c] = (char)player;
			board[r][c - 1] = '  ';
		}
		while (r >= rows)
		{
			cout << "You hit a Wall." << endl;
			r--;
			board[r][c] = (char)player;
			board[r + 1][c] = '  ';
		}
		while (c >= rows)
		{
			cout << "You hit a Wall." << endl;
			c--;
			board[r][c] = (char)player;
			board[r][c + 1] = '  ';
		}

	}
	//=================================================== Level 2 ==========================================================
	const int rows2 = 6;
	const int cols2 = 6;
	while (contP && lives > 0 && nextLevel == 2)
	{
		cout << "Level " << nextLevel << endl;
		int arraySize = rows2*cols2;
		char board2[rows2][cols2] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , (char)exit }
		};

		char bombBoard2[rows2][cols2] = {
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , '  ' },
			{ '  ' , '  ' , '  ' , '  ', '  ' , (char)exit }
		};

		board2[2][2] = (char)coin;
		board2[r][c] = (char)player;


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
			if (bombBoard2[r][c] == ' x ')
			{
				lives--;
				cout << "you hit a mine! limb lost! " << endl << lives << " left! " << endl;
			}
			cout << "total points: " << points << endl;
		}
		else if (input == 'w' || input == 'w')
		{
			upRight(r);
			r = upRight(r);
			board2[r][c] = (char)player;
			board2[r + 1][c] = '  ';
			moveCount--;
			points += 10;
			if (bombBoard2[r][c] == ' x ')
			{
				lives--;
				cout << "you hit a mine! limb lost! " << endl << lives << " left! " << endl;
			}
			cout << "total points: " << points << endl;
		}
		else if (input == 'd' || input == 'd')
		{
			downLeft(c);
			c = downLeft(c);
			board2[r][c] = (char)player;
			board2[r][c - 1] = '  ';
			moveCount--;
			points += 10;
			if (bombBoard2[r][c] == ' x ')
			{
				lives--;
				cout << "you hit a mine! limb lost! " << endl << lives << " left! " << endl;
			}
			cout << "total points: " << points << endl;
		}
		else if (input == 'a' || input == 'a')
		{
			upRight(c);
			c = upRight(c);
			board2[r][c] = (char)player;
			board2[r][c + 1] = '  ';
			moveCount--;
			points += 10;
			if (bombBoard2[r][c] == ' x ')
			{
				lives--;
				cout << "you hit a mine! limb lost! " << endl << lives << " left! " << endl;
			}
			cout << "total points: " << points << endl;
		}
		else if (input == 'p' || input == 'p')
		{
			contP = false;
		}
		else
		{
			cout << "invalid input. " << endl;
			cout << "total points: " << points << endl;
		}
		if (bombBoard2[r][c] == ' x ')
		{
			lives--;
			cout << "you hit a mine! limb lost! " << endl << lives << " left! " << endl;
		}
		if (moveCount <= 0)
		{
			cout << "You ran out and moves and lost a limb. " << endl;
			lives--;
			cout << lives << " limbs left. On to the next level" << endl;
			while (r > 0)
			{
				r--;
			}
			while (c > 0)
			{
				c--;
			}
			moveCount = 15;
			nextLevel++;
		}
		for (int i = 0; i < arraySize; i++)
		{
			if (board2[r][c] == board2[rows - 1][cols - 1])
			{
				system("cls");
				cout << "You reached the exit. On to the next level. " << endl;
				cout << "Total points: " << points << endl;
				while (r > 0)
				{
					r--;
				}
				while (c > 0)
				{
					c--;
				}
				moveCount = 15;
				nextLevel++;
			}
			else
			{

			}
		}
	}


	cout << endl << "You're done Buddy! " << endl;


	system("pause");
	return 0;
}