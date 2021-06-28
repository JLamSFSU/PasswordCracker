using namespace std;
#include "panel.h"
#include "pcrack.h"
#include "pcompare.h"

int main(void)
{
	string passwordToCrack;
	string passwordFound;
	char yn;

	START:cout << "Enter Password to Crack: ";
	cin >> passwordToCrack;

	switch (mainMenu())
	{
	case 0:
		// other method goes here.
		passwordFound = compare(passwordToCrack);
	case 1:
		passwordFound = cracker(passwordToCrack);
		break;
	case 2:
		// other method goes here.
		passwordFound = compare(passwordToCrack);
		break;
	}
	cout << "Password is: " << passwordFound << endl;

	do {
		cout << "\n\nRestart? (1 for yes 0 for no): ";
		cin >> yn;
		cout << "yn:" << yn << endl;
		switch (yn)
		{
		case '0':
			return 0;
		case '1':
			cout << endl;
			goto START;
		default:
			cout << "Bad Entry" << endl;
			cin.clear();
		}
	} while (true);
	return 0;
}
