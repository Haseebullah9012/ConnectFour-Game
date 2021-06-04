#include <iostream>
using namespace std;

void Docs(); //Print the "How to Play" Docs
void BoardSize(); //To define the Board-Size
void Difficulty(); //To define the Difficulty of the Game
void turn(); //Player's Turn
void Board(); //Print the Whole Board
int over(); //Check if anybody Won and Completed the Konnect-Goal
int draw(); //Check if the Board fills-out

char board[20][20];
int rows = 7, cols = 7 ; //Total Default Rows and Columns of the Board
int r,c; //For Loop-controls Row & Column

int konnect = 4; //The Default Konnect-Number Goal of the Game
int k; // For Loop-control Konnect

int a,b; //Player Inputs
char player, emp = '-'; //Player's & Empty Board's Symbol

int main()
{	
	Docs();
	
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
	
	int p = 1; //Player Number (First-Turn = Player 1)
		
	while (true) {
		
		if(p%2 == 1)
			player = 'X', p = 1;
		else
			player = 'O', p = 2;
		
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
	
	return 0;
}

void Docs()
{
	cout << endl
		<< "Welcome to the Connect-Four Board-Game. A Two-Player Turn-based Game. \n"
		<< " The Player 1 is assigned 'X'. \n"
		<< " The Player 2 is assigned 'O'. \n"
		<< endl;

	BoardSize();
	Difficulty();

	cout << "The First Player to Occupy any of the " << konnect << " consecutive Places, would Win. \n"
		<< "You can Occupy either Horizontally, Vertically, or Diagonally. \n" 
		<< "The Override is not Allowed. \n"
		<< endl;

	cout << "Pick the Specified Place according to the Index of the Row and Column. \n"
		<< endl;
}		

void BoardSize()
{
	char board_size;
	int size_sm = 6, size_md = 8, size_lg = 10; //Predefined Sizes
	
	cout << "Choose the Board-Size (s:small, m:medium, l:large, c:custom): ";
	cin >> board_size;

	if (board_size == 's' || board_size == 'S') {
		rows = size_sm, cols = size_sm; 
	}
	else if (board_size == 'm' || board_size == 'M') {
		rows = size_md, cols = size_md; 
	}
	else if (board_size == 'l' || board_size == 'L') {
		rows = size_lg, cols = size_lg;
	}
	else if (board_size == 'c' || board_size == 'C') {
		cout << "Enter the Custom Total Rows and Columns of the Board: ";
		cin >> rows >> cols;
		
		if (!(rows >=1 && cols >=1)) {
			cout << "Oops! It's too Small to be a Board. \n\n";
			rows = 7, cols = 7; //Make it Default-Size, just to make sure of no Errors
			BoardSize();
		}
		else if (!(rows <=20 && cols <=20)) {
			cout << "Oops! It's too Large to be a Board. \n\n";
			rows = 7, cols = 7; //Make it Default-Size, just to make sure of no Errors
			BoardSize();
		}
	}
	else {
		cout << "Please Enter the legal Board-Size, or Choose Custom! \n\n";
		board_size = 'm'; //Make it Default-Size, just to make sure of no Errors
		BoardSize();
	}
	
	cout << endl;
}

void Difficulty()
{
	char difficulty;
	int easy = 3, inter = 4, hard = 5; //Predefined Difficulties
	
	cout << "Choose the Game-Difficulty (e:easy, i:intermediate, h:hard, c:custom): ";
	cin >> difficulty;

	if (difficulty == 'e' || difficulty == 'E') {
		konnect = easy;
	}
	else if (difficulty == 'i' || difficulty == 'I') {
		konnect = inter;
	}
	else if (difficulty == 'h' || difficulty == 'H') {
		konnect = hard;
	}
	else if (difficulty == 'c' || difficulty == 'C') {
		cout << "Enter the Custom Konnect-Number Goal of the Game: ";
		cin >> konnect;
		
		if (!(konnect>=2)) {
			cout << "Oops! It's too Easy to be a Game. \n\n";
			konnect = 4; //Make it Default-Size, just to make sure of no Errors
			Difficulty();
		}
		else if (!(konnect<=15)) {
			cout << "Oops! It's too Difficult to be a Game. \n\n";
			konnect = 4; //Make it Default-Size, just to make sure of no Errors
			Difficulty();
		}
	}
	else {
		cout << "Please Enter the legal Difficulty, or Choose Custom! \n\n";
		difficulty = 'I'; //Make it Default-Size, just to make sure of no Errors
		Difficulty();
	}
	
	cout << endl;
}

void turn()
{
	cin >> a >> b;

	if (a>=1 && a<=rows && b>=1 && b<=cols) {
		
		if (board[a-1][b-1] == emp) {
			board[a-1][b-1] = player;
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
			
			for(k=0; k<=konnect; k++) {
				if (board[r][c+k] != player)
					break;
			}
			if(k==konnect)
				return true; //Horizonatlly
			
			for(k=0; k<=konnect; k++)
				if (board[r+k][c] != player)
					break;

			if(k==konnect)
				return true; //Vertically
			
			for(k=0; k<=konnect; k++)
				if (board[r+k][c+k] != player)
					break;
			
			if(k==konnect)
				return true; //Diagonally-Right

			for(k=0; k<=konnect; k++)
				if (board[r+k][c-k] != player)
					break;
				
			if(k==konnect)
				return true; //Diagonally-Left
		}
	}
	
	return false;
}

int draw()
{
	for (int r=0; r<rows; r++) {
		for (int c=0; c<cols; c++) {
			if (board[r][c] == emp) //false if even one space is empty
				return false;
		}
	}	
	return true;
}
