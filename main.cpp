using namespace std;
#include "panel.h"
#include "pcrack.h"
#include "pcompare.h"

string passwordToBeFound(void);

int main(void)
{
	string passwordToCrack;
	string passwordFound;
	char yn;

	START:switch (mainMenu())
	{
	case 0:
		passwordToCrack = passwordToBeFound();
		passwordFound = compare(passwordToCrack);
		passwordFound = cracker(passwordToCrack);
		break;
	case 1:
		passwordToCrack = passwordToBeFound();
		passwordFound = cracker(passwordToCrack);
		break;
	case 2:
		passwordToCrack = passwordToBeFound();
		passwordFound = compare(passwordToCrack);
		break;
	case 3:
		// method to generate password.
		// passwordFound =
	}
	if (passwordFound != "")
		cout << "Password is: " << passwordFound << endl;
	else
		cout << "Try again..." << endl;

	do {
		cout << "\n\nRestart? (1 for yes 0 for no): ";
		cin >> yn;
		switch (yn)
		{
		case '0':
			return 0;
		case '1':
			cout << endl;
			passwordToCrack.clear();
			passwordFound.clear();
			goto START;
		default:
			cout << "Bad Entry" << endl;
			// Below clears out bad entries
			cin.clear();
			cin.ignore(INT_MAX);
		}
	} while (true);
	return 0;
}


/**
* intermediate function in place of an actual interface for password
* finding. Currently password of interest is supplied, and the program
* works to determine if it can be easily found.
* Future implementation would change it so that it would be able to
* interface with desired platforms to try different passwords till
* success.
*/
string passwordToBeFound()
{
	string passwordToCrack;
	cout << "Enter Password to Crack: ";
	cin >> passwordToCrack;
	return passwordToCrack;
}