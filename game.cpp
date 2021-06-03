#include <iostream>
using namespace std;

void Docs();
void turn();
void Board(char [7][7]); //Print the Whole Board
int over(char [7][7]); //Check if anybody Won
int draw(char [7][7]); //Check if the Board fills-out

int a,b; //Player Inputs
char board[7][7];
int r,c; //For Loop-controls Row & Column
char player, emp = '-'; //Player's & Empty Board's Symbol

int main()
{	
	Docs();
	
	for (r=0; r<7; r++) {
		cout << "\t";
		for (c=0; c<7; c++) {
			board[r][c] = emp; //Initialize the whole Board
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	while (true) {	
		
		cout << "Player 1's Turn: ";
		player = 'X';
		
		turn();
		if (over(board)) {
				cout << "Player 1 Won! \n\n";
				break;
			}
		if (draw(board)) {
				cout << "Its a Draw! \n\n";
				break;
			}


		cout << "Player 2's Turn: ";
		player = 'O';
		
		turn();
		if (over(board)) {
			cout << "Player 2 Won! \n\n";
			break;
		}	
		if (draw(board)) {
			cout << "Its a Draw! \n\n";
			break;
		}
	}
	
	return 0;
}

void Docs()
{
	cout << endl
		<< "Welcome to the Connect-4 Board-Game. A Two-Player Turn-based Game. \n"
		<< " The Player 1 is assigned 'X'. \n"
		<< " The Player 2 is assigned 'O'. \n"
		<< endl;

	cout << "Pick the Specified Place according to the Index of the Row and Column. \n"
		<< "The First Player to Occupy any of the Four consecutive Places, would Win. \n"
		<< "You can Occupy either Horizontally, Vertically, or Diagonally. \n" 
		<< "The Override is not Allowed. \n"
		<< endl;
}		

void turn()
{
	cin >> a >> b;

	if (board[a][b] == emp) {
		board[a][b] = player;
		Board(board);
	}
	else {
		cout << "Its already Occupied, Pick Somewhere else: ";
		turn();
	}
}

void Board(char board[7][7])
{
	cout << endl;
	for (r=0; r<7; r++) {
		cout << "\t";
		for (c=0; c<7; c++)
			cout << board[r][c] << " ";
		cout << endl;
	}
	cout << endl << endl;
}

int over(char board[7][7])
{
	for (r=0; r<7; r++) {
		for (c=0; c<7; c++) {
			
			if (board[r][c] == player && board[r][c+1] == player && board[r][c+2] == player && board[r][c+3] == player)
				return true; //Horizonatlly
			
			else if (board[r][c] == player && board[r + 1][c] == player && board[r + 2][c] == player && board[r + 3][c] == player)
				return true; //Vertically
			
			else if (board[r][c] == player && board[r + 1][c + 1] == player && board[r + 2][c + 2] == player && board[r + 3][c + 3] == player)
				return true; //Diagonally-Right
			else if (board[r][c] == player && board[r + 1][c - 1] == player && board[r + 2][c - 2] == player && board[r + 3][c - 3] == player)
				return true; //Diagonally-Left
		}
	}
	return false;
}

int draw(char board[7][7])
{
	for (int r=0; r<7; r++) {
		for (int c=0; c<7; c++) {
			if (board[r][c] == emp) //false if even one space is empty
				return false;
		}
	}	
	return true;
}
