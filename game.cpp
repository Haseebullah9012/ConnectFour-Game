#include <iostream>
using namespace std;

void BoardSize(); //To define the Board-Size
void Difficulty(); //To define the Difficulty of the Game
void Player(); //To Assign the Player(s) Marks
void Docs(); //Print the "How to Play" Docs

void Play(); //The Main Game Sequence
void turn(); //Player's Turn
void Board(); //Print the Whole Board
int over(); //Check if anybody Won and Completed the Konnect-Goal
int draw(); //Check if the Board fills-out

char board[20][20]; //The Game Board
int rows = 7, cols = 7 ; //Total Default Rows and Columns of the Board
int r,c; //For Loop-controls Row & Column

int konnect = 4; //The Default Konnect-Number Goal of the Game
int k; // For Loop-control Konnect

char player[2], emp = '-'; //Player's & Empty Board's Mark
int p; //For Loop-control and also Player Number

int a,b; //The Player Inputs, Specific Row & Column

int main()
{	
	cout << endl
		<< "Welcome to the Konnect-Board-Game. Its a Two-Player Turn-based Game. \n"
		<< "It is Advised to Consult the Readme File, before Playing the Game. \n"
		<< endl;

	char chooseAgain;
	do {
		BoardSize();
		Difficulty();
		Player();

		cout << "The Board-Size is " << rows << "x" << cols << ", and "
			<< "The Konnect-Goal is " << konnect << ". \n"
			<< "The Player 1's Mark is " << player[1] << ", and "
			<< "The Player 2's Mark is " << player[2] << ". \n"
			<< "Is it OK (Y/N): ";
		cin >> chooseAgain;
		cout << endl << endl << endl;
	}
	while(chooseAgain == 'n' || chooseAgain == 'N');

	char playAgain;
	do {
		Docs();
		Play();

		cout << "Do You Want to Play Again (Y/N): ";
		cin >> playAgain;
		p++; //Next Time, the Next Player goes for the First Turn
		cout << endl << endl;
	}
	while(playAgain == 'y' || playAgain == 'Y');
	
	return 0;
}

void BoardSize()
{
	char board_size = 'M'; //Default
	int size_sm = 6, size_md = 8, size_lg = 10; //Predefined Sizes
	
	cout << "Choose the Board-Size (s:small, m:medium, l:large, c:custom): ";
	cin >> board_size;

	switch (board_size) 
	{
		case 's':
		case 'S':
			rows = size_sm, cols = size_sm; 
			break;
		case 'm':
		case 'M':
			rows = size_md, cols = size_md; 
			break;
		case 'l':
		case 'L':
			rows = size_lg, cols = size_lg;
			break;
		
		case 'c':
		case 'C':
			cout << "Enter the Custom Total Rows and Columns of the Board: ";
			cin >> rows >> cols;
			
			if (cin.fail()) {
				cin.clear();cin.ignore();
				cout << "Oops! Its not the legal Row-Column Numbers. \n\n";
				cout << "Again, ";
				BoardSize();
			}
			else if (!(rows >=2 && cols >=2)) {
				cout << "Oops! It's too Small to be a Board. \n\n";
				cout << "Again, ";
				BoardSize();
			}
			else if (!(rows <=20 && cols <=20)) {
				cout << "Oops! It's too Large to be a Board. \n\n";
				cout << "Again, ";
				BoardSize();
			}
			break;
		
		default:
			cout << "The Board-Size is Set to Default 7x7. \n";
			rows = 7, cols = 7;
	}

	cout << endl;
}

void Difficulty()
{
	char difficulty = 'I'; //Default
	int easy = 3, inter = 5, hard = 6; //Predefined Difficulties
	
	cout << "Choose the Game-Difficulty (e:easy, i:intermediate, h:hard, c:custom): ";
	cin >> difficulty;

	switch (difficulty) 
	{
		case 'e':
		case 'E':
			konnect = easy;
			break;
		case 'i':
		case 'I':
			konnect = inter;
			break;
		case 'h':
		case 'H':
			konnect = hard;
			break;
		
		case 'c':
		case 'C':
			cout << "Enter the Custom Konnect-Number Goal of the Game: ";
			cin >> konnect;
			
			if (cin.fail()) {
				cin.clear(); cin.ignore();
				cout << "Oops! Its not the legal Konnect-Goal Number. \n\n";
				cout << "Again, ";
				Difficulty();
			}
			else if (!(konnect>=2)) {
				cout << "Oops! It's too Easy to be a Game. \n\n";
				cout << "Again, ";
				Difficulty();
			}
			else if (!(konnect<=20)) {
				cout << "Oops! It's too Difficult to be a Game. \n\n";
				cout << "Again, ";
				Difficulty();
			}
			break;
		
		default:
			cout << "The Konnect-Goal Difficulty is Set to Default 4. \n";
			konnect = 4;
	}

	if(konnect > rows && konnect > cols) {
		cout << "Oops! It isn't Possible to Complete this Goal on that Small Board Size. \n";
		cout << "Choose Again! \n\n";
		Difficulty();
	}

	cout << endl;
}

void Player()
{
	char playerMark = 'D'; //Default
	
	cout << "Customize the Player's Mark (d:default, c:custom): ";
	cin >> playerMark;

	switch (playerMark) 
	{
		case 'c':
		case 'C':
			for(p=1; p<=2; p++) {
				cout << "Enter the Custom Identification-Mark for Player " << p << ": ";
				cin >> player[p]; //player[0] is Empty
			}
			break;
		
		default:
			cout << "The Player(s) Marks are Set to Default 'X' and 'O'. \n";
			player[1] = 'X', player[2] = 'O';
	}

	p = 1; //First-Turn for Player 1
	cout << endl;
}

void Docs()
{
	cout << "So, Lets Begin! \n\n";
	cout << "Pick the Specified Place according to the Index of the Row and Column. \n\n";
	
	//Initialize the whole Board
	for (r=0; r<rows; r++) {
		cout << "\t";
		for (c=0; c<cols; c++) {
			board[r][c] = emp;
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;
}		


void Play()
{
	while (true) {
		
		if(p%2 == 1)
			p = 1;
		else
			p = 2;
		
		cout << "Player " << p << "'s Turn: ";
		turn();
		
		if (over()) {
			cout << "Player " << p << " Won! \n\n";
			break;
		}
		if (draw()) {
			cout << "Its a Draw! \n\n";
			break;
		}

		p++;
	}
}

void turn()
{
	cin >> a >> b;
	
	if (cin.fail()) {
		cin.clear(); cin.ignore();
		cout << "Oops! Its not Legal. \n"
			<< "Pick Again, (Rows 1 to " << rows << ") & "
						<< "(Columns 1 to " << cols << "): ";
		turn();
	}
	else if (a>=1 && a<=rows && b>=1 && b<=cols) {
		
		if (board[a-1][b-1] == emp) {
			board[a-1][b-1] = player[p];
			Board();
		}
		else {
			cout << "Its already Occupied, Pick Somewhere else: ";
			turn();
		}
	}
	else {
		cout << "Oops! Its Outside the Board. \n"
			<< "Pick Again, (Rows 1 to " << rows << ") & "
						<< "(Columns 1 to " << cols << "): ";
		turn();
	}
}

void Board()
{
	cout << endl;
	for (r=0; r<rows; r++) {
		cout << "\t";
		for (c=0; c<cols; c++)
			cout << board[r][c] << " ";
		cout << endl;
	}
	cout << endl << endl;
}

int over()
{
	for (r=0; r<rows; r++) {
		for (c=0; c<cols; c++) {
			
			for(k=0; k<=konnect; k++)
				if (board[r][c+k] != player[p])
					break;
			if(k==konnect)
				return true; //Horizonatlly
			
			for(k=0; k<=konnect; k++)
				if (board[r+k][c] != player[p])
					break;
			if(k==konnect)
				return true; //Vertically
			
			for(k=0; k<=konnect; k++)
				if (board[r+k][c+k] != player[p])
					break;
			if(k==konnect)
				return true; //Diagonally-Right

			for(k=0; k<=konnect; k++)
				if (board[r+k][c-k] != player[p])
					break;
			if(k==konnect)
				return true; //Diagonally-Left
		}
	}
	
	return false;
}

int draw()
{
	for (r=0; r<rows; r++)
		for (c=0; c<cols; c++)
			if (board[r][c] == emp) //false if even one space is empty
				return false;
	return true;
}
