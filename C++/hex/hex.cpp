/* CSCI1540
*
* Assignment: 5
* Student ID: 1155028934
* Name      : SHU HAORAN
* E-mail adr: henryshu1994@gmail.com
*
* Please insert your personal particulars in this format in all CSCI1540
* assignment submissions.
*
*/


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int N = 11;

void displayBoard(char board[][N]) {
	cout << "  A B C D E F G H I J K" << endl;
	for (int i = 0; i <= N - 1; i++) {
		cout << setw(2) << i;
		for (int j = 0; j < i; j++)
			cout << " ";
		for (int k = 0; k <= N - 1; k++)
			cout << " " << board[i][k];
		cout << endl;
	}
}

void spreadReach(char board[][N], bool reach[][N], int col, int row, char player) {
	if (row + 1 <= N - 1) {
		if (board[row + 1][col] == player)
			reach[row + 1][col] = true;
		if (col - 1 >= 0) {
			if (board[row + 1][col - 1] == player) {
				reach[row + 1][col - 1] = true;
			}
		}
	}
	if (row - 1 >= 0) {
		if (board[row - 1][col] == player)
			reach[row - 1][col] = true;
		if (col + 1 <= N - 1) {
			if (board[row - 1][col + 1] == player) {
				reach[row - 1][col + 1] = true;
			}
		}
	}
	if (col - 1 >= 0)
		if (board[row][col - 1] == player)
			reach[row][col - 1] = true;
	if (col + 1 <= N - 1)
		if (board[row][col + 1] == player)
			reach[row][col + 1] = true;
}

int cntArray(bool reach[][N]) {
	int cnt = 0;
	for (int i = 0; i <= N - 1; i++)
		for (int j = 0; j <= N - 1; j++)
			if (reach[i][j] == true)
				cnt += 1;
	return cnt;
}

bool updateAndCheckWin(char board[][N], int col, int row, char player) {
	bool reach[N][N] = { 0 };
	board[row][col] = player;
	spreadReach(board, reach, col, row, player);
	int cntNew = cntArray(reach), cntOld = 0;
	while (cntOld != cntNew) {
		cntOld = cntNew;
		for (int k = 0; k <= N - 1; k++)
			for (int l = 0; l <= N - 1; l++)
				if (reach[k][l] == true)
					spreadReach(board, reach, l, k, player);
		cntNew = cntArray(reach);
	}

	int cnt = 0;
	bool result = false;
	if (player == 'X') {
		for (int i = 0; i <= N - 1; i++, cnt++) {
			if (reach[0][i] == true) {
				for (int j = 0; j <= N - 1; j++, cnt++) {
					if (reach[N - 1][j] == true)
						result = true;
				}
			}
		}
	}
	else {
		for (int i = 0; i <= N - 1; i++, cnt++) {
			if (reach[i][0] == true) {
				for (int j = 0; j <= N - 1; j++, cnt++) {
					if (reach[j][N - 1] == true)
						result = true;
				}
			}
		}
	}

	return result;
}

void alterPlayer(char &player) {
	if (player == 'O')
		player = 'X';
	else
		player = 'O';
}

int convertLetter(char x) {
	if (x == 'A')
		return 1;
	else if (x == 'B')
		return 2;
	else if (x == 'C')
		return 3;
	else if (x == 'D')
		return 4;
	else if (x == 'E')
		return 5;
	else if (x == 'F')
		return 6;
	else if (x == 'G')
		return 7;
	else if (x == 'H')
		return 8;
	else if (x == 'I')
		return 9;
	else if (x == 'J')
		return 10;
	else if (x == 'K')
		return 11;
	else
		return 0;
}

int main() {
	char boardReal[N][N];
	for (int k = 0; k <= N - 1; k++)
		for (int l = 0; l <= N - 1; l++)
			boardReal[k][l] = '.';
	char playerReal = 'X';
	char col = 'Z';
	int row = -1;
	while (!updateAndCheckWin(boardReal, convertLetter(col) - 1, row, playerReal)) {
		alterPlayer(playerReal);
		displayBoard(boardReal);

		cout << "Player " << playerReal << ", make your move: ";
		cin >> col >> row;

		while ((col != 'A' && col != 'B' && col != 'C' && col != 'D' && col != 'E' && col != 'F' && col != 'G' && col != 'H' && col != 'I' && col != 'J' && col != 'K') || (row > 10 || row < 0) || boardReal[row][convertLetter(col) - 1] != '.') {
			cout << "Invalid move. Enter again!" << endl;
			cout << "Player " << playerReal << ", make your move: ";
			cin >> col >> row;
		}
	}

	displayBoard(boardReal);
	cout << "Player " << playerReal << " wins!" << endl;

	return 0;
}