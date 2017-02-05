/* CSCI1540
*
* Assignment: 2
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
using namespace std;

int main()
{
// Declaring variables needed
	int year, month, day;
	int a, b, c, d, e, f, g, h, i, k, L, m;

// Prompt the user to enter a 'year' and store the value in variable 'year'
	cout << "Enter year: ";
	cin >> year;

// Follow the assigned algorithm
	a = year % 19;
	b = floor(year / 100);
	c = year % 100;
	d = floor(b / 4);
	e = b % 4;
	f = floor((b + 8) / 25);
	g = floor((b - f + 1) / 3);
	h = (19 * a + b - d - g + 15) % 30;
	i = floor(c / 4);
	k = c % 4;
	L = (32 + 2 * e + 2 * i - h - k) % 7;
	m = floor((a + 11 * h + 22 * L) / 451);

	month = floor((h + L - 7 * m + 114) / 31);
	day = ((h + L - 7 * m + 114) % 31) + 1;

// Print out the result
	cout << "Easter Day in " << year << " is " << day << "/" << month << "/" << year << "." << endl;

	return 0;
}