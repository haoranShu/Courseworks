/* CSCI1540
*
* Assignment: 3
* Student ID: 1155028934
* Name      : SHU HAORAN
* E-mail adr: henryshu1994@gmail.com
*
* Please insert your personal particulars in this format in all CSCI1540
* assignment submissions.
*
*/

#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

int main()
{
	int numPlayer, numGame;
	int lose1 = 0, lose2 = 0, lose3 = 0, lose4 = 0, lose5 = 0;

	cout << "How many players (3-5)? ";
	cin >> numPlayer;

	while ((numPlayer < 3) || (numPlayer > 5)) {
		cout << "Number of players must be 3-5! Try again." << endl;
		cout << "How many players (3-5)? ";
		cin >> numPlayer;
	}

	cout << "How many games? ";
	cin >> numGame;

	while (numGame < numPlayer) {
		cout << "At least " << numPlayer << " games! Try again." << endl;
		cout << "How many games? ";
		cin >> numGame;
	}

	srand(numPlayer * numGame);

	for (int i = 0; i < numGame; i++) {
		int upperBd = 100, lowerBd = 1, secret = rand() % 100 + 1;
		cout << "Game #" << i + 1 << ":" << endl;

		while (upperBd != lowerBd) {
			for (int j = i; j >= 0; j++) {
				int guess;

				cout << "Player " << j%numPlayer + 1 << ", make a guess (" << lowerBd << "-" << upperBd << "): ";
				cin >> guess;

				while ((guess < lowerBd) || (guess > upperBd)) {
					cout << "Guess must be " << lowerBd << "-" << upperBd << "! Trt again." << endl;
					cout << "Player " << j%numPlayer + 1 << ", make a guess (" << lowerBd << "-" << upperBd << "): ";
					cin >> guess;
				}

				if (guess == secret) {
					lowerBd = guess;
					upperBd = guess;
					cout << "Boom! Player " << j%numPlayer + 1 << " loses." << endl;
					if ((j%numPlayer + 1) == 1)
						lose1++;
					else if ((j%numPlayer + 1) == 2)
						lose2++;
					else if ((j%numPlayer + 1) == 3)
						lose3++;
					else if ((j%numPlayer + 1) == 4)
						lose4++;
					else if ((j%numPlayer + 1) == 5)
						lose5++;
					j = -1;
					break;
				}
				else if ((guess >= lowerBd) && (guess < secret)) {
					cout << "Your guess is LO." << endl;
					lowerBd = guess + 1;
				}
				else {
					cout << "Your guess is HI." << endl;
					upperBd = guess - 1;
				}
			}
		}
	}

	int k = 0;
	if (k < numPlayer) {
		cout << "Player " << k + 1 << " loses " << lose1 << " time(s)." << endl;
		k++;
	}
	if (k < numPlayer) {
		cout << "Player " << k + 1 << " loses " << lose2 << " time(s)." << endl;
		k++;
	}
	if (k < numPlayer) {
		cout << "Player " << k + 1 << " loses " << lose3 << " time(s)." << endl;
		k++;
	}
	if (k < numPlayer) {
		cout << "Player " << k + 1 << " loses " << lose4 << " time(s)." << endl;
		k++;
	}
	if (k < numPlayer) {
		cout << "Player " << k + 1 << " loses " << lose5 << " time(s)." << endl;
		k++;
	}

	return 0;
}