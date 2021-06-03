#include <iostream>
using namespace std;

//removed the Class 
//changed Function names
//Change the Variable names, and Loop-control names

void Docs();
void Board(char [7][7]);
int over(char [7][7], int);
int draw(char [7][7]);
int r,c; //For Loop-controls Row & Column

int main()
{
	int a,b;
	char board[7][7];
	
	Docs();
	for (r=0; r<7; r++) {
		cout << "\t";
		for (c=0; c<7; c++) {
			board[r][c] = '*'; //Initialize the whole Board
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	while (true) {	
		
		cout << "Player 1's Turn: ";
	error1:
		cin >> a >> b;
		
		if (board[a][b] == '*') {
			board[a][b] = 'X';
			Board(board);
			
			if (over(board, 'X') == true) { 
				cout << "Player 1 Won! \n\n";
				break;
			}
			
			if (draw(board) == true) {
				cout << "Its a Draw! \n\n";
				break;
			}
		}
		else {
			cout << "Its already Occupied, Pick Somewhere else: ";
			goto error1;
		}
		

		cout << "Player 2's Turn: ";
	error2:
		cin >> a >> b;
		
		if (board[a][b] == '*') {
			board[a][b] = 'O';
			Board(board);
			
			if (over(board, 'O') == true) { 
				cout << "Player 2 Won! \n\n";
				break;
			}
			
			if (draw(board) == true) {
				cout << "Its a Draw! \n\n";
				break;
			}
		}
		else {
			cout << "Its already Occupied, Pick Somewhere else: ";
			goto error2;
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

int over(char board[7][7], int p)
{
	for (r=0; r<7; r++) {
		for (c=0; c<7; c++) {
			
			if (board[r][c] == p && board[r][c+1] == p && board[r][c+2] == p && board[r][c+3] == p)
				return true; //Horizonatlly
			
			else if (board[r][c] == p && board[r + 1][c] == p && board[r + 2][c] == p && board[r + 3][c] == p)
				return true; //Vertically
			
			else if (board[r][c] == p && board[r + 1][c + 1] == p && board[r + 2][c + 2] == p && board[r + 3][c + 3] == p)
				return true; //Diagonally-Right
			else if (board[r][c] == p && board[r + 1][c - 1] == p && board[r + 2][c - 2] == p && board[r + 3][c - 3] == p)
				return true; //Diagonally-Left
		}
	}
	return false;
}

int draw(char board[7][7])
{
	for (int r=0; r<7; r++) {
		for (int c=0; c<7; c++) {
			if (board[r][c] == '*')
				return false;
		}
	}	
	return true;
}
