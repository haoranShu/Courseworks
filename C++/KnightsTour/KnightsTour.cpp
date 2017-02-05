/* CSCI1540
*
* Assignment: 6
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
#include "KnightsTour.h"
using namespace std;

KnightsTour::KnightsTour(int x, int y) {
	for (int i = 0; i <= 5; i++)
		for (int j = 0; j <= 5; j++)
			board[i][j] = 0;
	posX = x; posY = y;
	board[posX][posY] = 1;
}

void KnightsTour::print() {
	// Print first line
	cout << "  0 1 2 3 4 5\n";
	for (int i = 0; i <= 5; i++) {
		// Print first column
		cout << i;
		// Print according to board
		for (int j = 0; j <= 5; j++) {
			// Print noncurrent positions
			if ((i != posX) || (j != posY)) {
				if (board[i][j])
					cout << " O";
				else
					cout << " .";
			}
			// Print the current position
			else
				cout << " K";
		}
		cout << endl;
	}
}

bool KnightsTour::hasMoreMoves() {
	// Set up an array to store possible future positions
	int NextMoveR[8] = { posX - 2, posX - 2, posX - 1, posX - 1, posX + 1, posX + 1, posX + 2, posX + 2 };
	int NextMoveC[8] = { posY - 1, posY + 1, posY - 2, posY + 2, posY - 2, posY + 2, posY - 1, posY + 1 };
	int PossibleMove = 0;

	// Check whether these steps fall onto the board
	for (int i = 0; i <= 7; i++) {
		if ((NextMoveR[i] >= 0) && (NextMoveC[i] >= 0) && (NextMoveR[i] <= 5) && (NextMoveC[i] <= 5) && (board[NextMoveR[i]][NextMoveC[i]] != 1))
			PossibleMove++;
	}
	return PossibleMove;
}

bool KnightsTour::isSolved() {
	// Simply check for every position
	for (int i = 0; i <= 5; i++)
		for (int j = 0; j <= 5; j++)
			if (board[i][j] == 0)
				return false;
	return true;
}

bool KnightsTour::move(int x, int y) {
	if ((x < 0) || (x > 5) || (y < 0) || (y > 5))
		return false;
	if (((((x == posX - 1) && (y == posY - 2)) || ((x == posX - 1) && (y == posY + 2)) || ((x == posX + 1) && (y == posY - 2)) || ((x == posX + 1) && (y == posY + 2)) || ((x == posX - 2) && (y == posY - 1)) || ((x == posX - 2) && (y == posY + 1)) || ((x == posX + 2) && (y == posY - 1)) || ((x == posX + 2) && (y == posY + 1)))) && (board[x][y] != 1)) {
		posX = x;
		posY = y;
		board[posX][posY] = 1;
		return true;
	}
	else
		return false;
}

void KnightsTour::lookAhead(int &r, int &c) {
	//identify possible steps
	int NextMoveR[8] = { r - 2, r - 2, r - 1, r - 1, r + 1, r + 1, r + 2, r + 2 };
	int NextMoveC[8] = { c - 1, c + 1, c - 2, c + 2, c - 2, c + 2, c - 1, c + 1 };
	int PossibleStps = 9;

	for (int i = 0; i <= 7; i++) {
		// Check whether these positions fall on the board and whether it has been visited
		if ((NextMoveR[i] >= 0) && (NextMoveC[i] >= 0) && (NextMoveR[i] <= 5) && (NextMoveC[i] <= 5) && (board[NextMoveR[i]][NextMoveC[i]] != 1)) {
			// Indentidy the points to be visited from this new position
			int NNMoveR[8] = { NextMoveR[i] - 2, NextMoveR[i] - 2, NextMoveR[i] - 1, NextMoveR[i] - 1, NextMoveR[i] + 1, NextMoveR[i] + 1, NextMoveR[i] + 2, NextMoveR[i] + 2 };
			int NNMoveC[8] = { NextMoveC[i] - 1, NextMoveC[i] + 1, NextMoveC[i] - 2, NextMoveC[i] + 2, NextMoveC[i] - 2, NextMoveC[i] + 2, NextMoveC[i] - 1, NextMoveC[i] + 1 };
			int count = 0;
			// Count the number of such future steps
			for (int j = 0; j <= 7; j++) {
				if ((NNMoveR[j] >= 0) && (NNMoveC[j] >= 0) && (NNMoveR[j] <= 5) && (NNMoveC[j] <= 5) && (board[NNMoveR[j]][NNMoveC[j]] != 1)) {
					count++;
				}
			}
			// Identify the possible step with fewest future steps and update r and c
			if (count < PossibleStps) {
				PossibleStps = count;
				r = NextMoveR[i];
				c = NextMoveC[i];
			}
			else if (count == PossibleStps) {
				if (r > NextMoveR[i]) {
					r = NextMoveR[i];
					c = NextMoveC[i];
				}
				else if ((r == NextMoveR[i]) && (c > NextMoveC[i])) {
					r = NextMoveR[i];
					c = NextMoveC[i];
				}
			}
		}
	}
}