/* CSCI1540
*
* Assignment: 4
* Student ID: 1155028934
* Name      : SHU HAORAN
* E-mail adr: henryshu1994@gmail.com
*
* Please insert your personal particulars in this format in all CSCI1540
* assignment submissions.
*
*/

#include <iostream>
#include<string>
using namespace std;

bool isLeapYear(int y) {
	if (y % 400 == 0)
		return true;
	else if ((y % 4 == 0) && (y % 100 != 0))
		return true;
	else
		return false;
}

int numLeapYear(int y) {
	int n = 0;
	if (y <= 1582)
		return 0;
	else
		for (int i = 1583; i < y; i++)
			if (isLeapYear(i))
				n++;
	return n;
}

int dayOfMonth(int y, int m) {

	if ((m == 2) && isLeapYear(y))
		return 29;
	else if (m == 2)
		return 28;
	else if ((m <= 7) && (m % 2 == 1))
		return 31;
	else if ((m >= 8) && (m % 2 == 0))
		return 31;
	else
		return 30;
}

int startWeekday(int y, int m) {
	int startOfYear, startWeekday;

	startOfYear = ((y - 1583) * 365 + numLeapYear(y) + 6) % 7;
	int dayPass = 0;

	for (int i = 1; i < m; i++)
		dayPass += dayOfMonth(y, i);

	startWeekday = (startOfYear + dayPass) % 7;

	return startWeekday;
}

int main() {
	int year;
	const string month[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	cout << "Enter a year (> 1582): ";
	cin >> year;

	while (year <= 1582) {
		cout << "Year must be > 1582. Try again!" << endl;
		cout << "Enter a year (> 1582): ";
		cin >> year;
	}

	cout << "                             Year " << year << endl;
	cout << endl;

	for (int i = 0; i < 4; i++) {
		int c1 = 1, c2 = 1, c3 = 1;
		int s1 = startWeekday(year, i * 3 + 1), s2 = startWeekday(year, i * 3 + 2), s3 = startWeekday(year, i * 3 + 3);
		cout << "         " << month[i * 3] << "                    " << month[i * 3 + 1] << "                    " << month[i * 3 + 2] << endl;
		cout << "Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa" << endl;
		for (int r = 0; r < 6; r++) {
			int rowcounter = 0;
			while (rowcounter < 21) {
				if (rowcounter < 7) {
					while ((r == 0) && (rowcounter < s1)) {
						cout << "   ";
						rowcounter++;
					}
					if (c1++ <= dayOfMonth(year, i * 3 + 1)) {
						if (c1 <= 10)
							cout << " " << c1 - 1 << " ";
						else
							cout << c1 - 1 << " ";
					}
					else
						cout << "   ";
				}
				else if (rowcounter < 14) {
					while ((r == 0) && (rowcounter < s2 + 7)) {
						cout << "   ";
						rowcounter++;
					}
					if (c2++ <= dayOfMonth(year, i * 3 + 2)) {
						if (c2 <= 10)
							cout << " " << c2 - 1 << " ";
						else
							cout << c2 - 1 << " ";
					}
					else
						cout << "   ";
				}
				else {
					while ((r == 0) && (rowcounter < s3 + 14)) {
						cout << "   ";
						rowcounter++;
					}
					if (c3++ <= dayOfMonth(year, i * 3 + 3)) {
						if (c3 <= 10)
							cout << " " << c3 - 1 << " ";
						else
							cout << c3 - 1 << " ";
					}
					else
						cout << "   ";
				}
				rowcounter++;
				if ((rowcounter == 7) || (rowcounter == 14))
					cout << "  ";
			}
			cout << endl;
		}
	}

	return 0;
}