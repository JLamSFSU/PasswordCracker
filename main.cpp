using namespace std;
#include <iostream>
#include <string>
#include "panel.h"
#include "pcrack.h"
#include "pcompare.h"
#include "createp.h"
#include "pcheck.h"
#include "pda.h"

string passwordToBeFound(void);

int main(void)
{
	string passwordToCrack;
	string passwordFound;
	string trashbin;
	char yn;

	START:switch (mainMenu())
	{
	case 0:
		passwordToCrack = passwordToBeFound();
		passwordFound = compare(passwordToCrack);
		if (passwordFound != "")
			break;
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
		// Dictionary attack.
		passwordToCrack = passwordToBeFound();
		passwordFound = dictionaryAttack(passwordToCrack);
		break;
	case 4:
		// method to generate password.
		passwordFound = createPassword();
		break;
	case 5:
		passwordToCrack = passwordToBeFound();
		passwordFound = compare(passwordToCrack);
		if (passwordFound != "")
		{
			passwordFound = "Really weak, and is found amongst commonly used password. Please consider a different one.";
			break;
		}
		// method to check security of password
		passwordFound = checkPassword(passwordToCrack);
		break;
	}
	if (passwordFound != "")
		cout << "Password: " << passwordFound << endl;
	else
		cout << "Try again..." << endl;

	do {
		cout << "\n\nRestart? (1 for yes 0 for no): ";
		cin >> yn;
		getline(cin, trashbin);
		switch (yn)
		{
		case '0':
			return 0;
		case '1':
			cout << endl;
			passwordToCrack.clear();
			passwordFound.clear();
			passwordFound = "";
			goto START;
		default:
			cout << "Bad Entry" << endl;
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
	string trashbin;
	cout << "Enter Password: ";
	cin >> passwordToCrack;
	getline(cin, trashbin);
	return passwordToCrack;
}