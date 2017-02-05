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

int main() {
	int r, c;

	// Ask for input
	cout << "Enter knight's starting position (row col): ";
	cin >> r >> c;

	// Check whether the entered values are valid
	while ((r < 0) || (r > 5) || (c < 0) || (c > 5)) {
		cout << "Invalid. Try again!\n";
		cout << "Enter knight's starting position (row col): ";
		cin >> r >> c;
	}

	// Initiate the configuration
	KnightsTour knightstour(r, c);
	knightstour.print();

	// Ask the player to move when still possible moves left
	while (knightstour.hasMoreMoves()) {
		cout << "Make a move (row col): ";
		cin >> r >> c;
		if (knightstour.move(r, c)) {
			knightstour.print();
			continue;
		}
		else {
			cout << "Invalid move. Try again!\n";
		}
	}

	// When no more moves left, check whether successful
	if (knightstour.isSolved())
		cout << "Finished. Well done!";
	else
		cout << "Sorry. No more moves!";

	return 0;
}