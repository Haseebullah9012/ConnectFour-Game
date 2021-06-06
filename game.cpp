#include <iostream>
using namespace std;

void configuration(); //The Game's Configuration Options
void BoardSize(); //To define the Board-Size
void Difficulty(); //To define the Difficulty of the Game
void Player(); //To Assign the Player(s) Marks

void Docs(); //Print the "How to Play" Docs
void Play(); //The Main Game Sequence
void turn(); //Player's Turn
void Board(); //Print the Whole Board
int over(); //Check if anybody Won and Completed the Konnect-Goal
int draw(); //Check if the Board fills-out

char configure = 'N'; //The Default Configuration Options Display
int max_cIgnore = 30; //MaxCharacters to be Ignored in the Buffer

char board[30][30]; //The Game Board
int rows = 7, cols = 7 ; //Total Default Rows and Columns of the Board
int r,c; //For Loop-controls Row & Column

int konnect = 4; //The Default Konnect-Number Goal of the Game
int k; // For Loop-control Konnect

char emp = '-'; //Empty Board's Mark
int players = 2 +1; //Total Default Number of Players + 1
char player[3] = {emp,'X','O'}; //The Player's Default Marks
int p; //For Loop-control and also Player Number

int a,b; //The Player Inputs, for Specific Row & Column

int main()
{	
	cout << endl
		<< "Welcome to the Konnect-Board-Game. Its a Two-Player Turn-based Game. \n"
		<< "You are Advised to Consult the Readme File, before Playing the Game. \n"
		<< endl;

	configuration();

	char playAgain;
	do {	
		Docs();
		Play();

		cout << "Do You Want to Play Again (Y/N): ";
		cin >> playAgain;
		playAgain = toupper(playAgain);
		cin.ignore(max_cIgnore, '\n');

		if(playAgain == 'Y') {
			cout << "Do You Want to Configure the Options (Y/N): ";	
			cin >> configure;
			configure = toupper(configure);
			cin.ignore(max_cIgnore, '\n');
			
			cout << endl << endl;
			if(configure == 'Y') {
				configuration();
			}
			
			p = rand() % 4 + 1; //Next Time, the Random Player goes for the First Turn
		}
	}
	while(playAgain == 'Y');
	
	cout << endl << endl;
	return 0;
}

void configuration() {
	do {	
		if(configure == 'Y') {
			BoardSize();
			Difficulty();
			Player();
		}
		
		cout << "The Board-Size is (" << rows << "x" << cols << "). \n"
			<< "The Konnect-Goal is to Occupy " << konnect << " Consecutive Places. \n";
		
		for(p=1; p<players; p++)
			cout << " The Player " << p << "'s Mark is '" << player[p] << "'. \n";
		
		cout << "   Do you want to Configure them (Y/N): ";
		
		cin >> configure;
		configure = toupper(configure);
		cin.ignore(max_cIgnore, '\n');
		
		p = 1; //First-Turn for Player 1
		cout << endl << endl;
	}
	while(configure == 'Y');
}

void BoardSize()
{
	char board_size = 'M'; //Default
	int size_sm = 6, size_md = 8, size_lg = 10; //Predefined Sizes
	
	cout << "Choose the Board-Size (s:small, m:medium, l:large, c:custom): ";
	cin >> board_size;
	board_size = toupper(board_size);
	cin.ignore(max_cIgnore, '\n');

	switch (board_size) 
	{
		case 'S':
			rows = size_sm, cols = size_sm; 
			break;
		case 'M':
			rows = size_md, cols = size_md; 
			break;
		case 'L':
			rows = size_lg, cols = size_lg;
			break;
		
		case 'C':
			cout << "   Enter the Custom Total Rows and Columns of the Board: ";
			cin >> rows >> cols;
			cin.ignore(max_cIgnore,'\n');
			
			if (cin.fail()) {
				cin.clear(); cin.ignore(max_cIgnore,'\n');
				cout << "   Oops! Its not the legal Row-Column Numbers. \n\n";
				cout << "Again, ";
				BoardSize();
			}
			else if (!(rows>=2 && cols>=2)) {
				cout << "   Oops! It's too Small to be a Board. \n\n";
				cout << "Again, ";
				BoardSize();
			}
			else if (!(rows<=30 && cols<=30)) {
				cout << "   Oops! It's too Large to be a Board. \n\n";
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
	difficulty = toupper(difficulty);
	cin.ignore(max_cIgnore, '\n');

	switch (difficulty) 
	{
		case 'E':
			konnect = easy;
			break;
		case 'I':
			konnect = inter;
			break;
		case 'H':
			konnect = hard;
			break;
		
		case 'C':
			cout << "   Enter the Custom Konnect-Number Goal of the Game: ";
			cin >> konnect;
			cin.ignore(max_cIgnore,'\n');
			
			if (cin.fail()) {
				cin.clear(); cin.ignore(max_cIgnore, '\n');
				cout << "   Oops! Its not the legal Konnect-Goal Number. \n\n";
				cout << "Again, ";
				Difficulty();
			}
			else if (!(konnect>=2)) {
				cout << "   Oops! It's too Easy to be a Game. \n\n";
				cout << "Again, ";
				Difficulty();
			}
			else if (!(konnect<=30)) {
				cout << "   Oops! It's too Difficult to be a Game. \n\n";
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
	cout << "How Many Players are there to Play: ";
	cin >> players;
	cin.ignore(max_cIgnore, '\n');
	players++;

	if (cin.fail()) {
		cin.clear();cin.ignore(max_cIgnore,'\n');
		cout << "It's Set to Default 2-Player. \n";
		players = 2 +1;
	}
	else if (!(players-1>=2)) {
		cout << "   Oops! It's too Less Players to Play a Game. \n\n";
		cout << "Again, ";
		Player();
	}
	else if (!(players-1<=4)) {
		cout << "   Oops! It's too Many Players. \n\n";
		cout << "Again, ";
		Player();
	}
	cout << endl;
	
	char customMark = 'D'; //Default
	cout << "Do you Want to Customize the Player's Mark (Y/N): ";
	cin >> customMark;
	customMark = toupper(customMark);
	cin.ignore(max_cIgnore, '\n');

	if(customMark == 'Y') {
		for(p=1; p<players; p++) {
			cout << "   Enter the Custom Identification-Mark for Player " << p << ": ";
			cin >> player[p]; //player[0] is Empty
			cin.ignore(max_cIgnore, '\n');
		}
	}
	else {
		cout << "The Player Marks are Set to Default. \n";
		player[1] = 'X', player[2] = 'O';
		
		if(players-1 >= 3)
			player[3] = 'I';
		if(players-1 >= 4)
			player[4] = 'H';
	}
	
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
		
		switch(players-1) 
		{
			case 2:
				if(p%(players-1) == 1)
					p = 1;
				else
					p = 2;
				break;

			case 3:
				if(p%(players-1) == 1)
					p = 1;
				else if(p%(players-1) == 2)
					p = 2;
				else
					p = 3;
				break;

			case 4:
				if(p%(players-1) == 1)
					p = 1;
				else if(p%(players-1) == 2)
					p = 2;
				else if(p%(players-1) == 3)
					p = 3;
				else
					p = 4;
				break;
		}

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
		cin.clear(); cin.ignore(max_cIgnore, '\n');
		cout << "Oops! Its not Legal. \n"
			<< "Pick Again, (Rows 1 to " << rows << ") & "
						<< "(Columns 1 to " << cols << "): ";
		turn();
	}
	else if (a>=1 && a<=rows && b>=1 && b<=cols) {
		
		if (board[a-1][b-1] == emp) {
			board[a-1][b-1] = player[p];
			cin.ignore(max_cIgnore,'\n');
			Board();
		}
		else {
			cout << "Its already Occupied, Pick Somewhere else: ";
			cin.ignore(max_cIgnore,'\n');
			turn();
		}
	}
	else {
		cout << "Oops! Its Outside the Board. \n"
			<< "Pick Again, (Rows 1 to " << rows << ") & "
						<< "(Columns 1 to " << cols << "): ";
		cin.ignore(max_cIgnore,'\n');
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
