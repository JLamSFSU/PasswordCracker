/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: main.c
 * 
 * Description: Main Executable program
 *****************************************************************************/

using namespace std;
#include <iostream>
#include <string>
#include "panel/include/panel.h"
#include "create_password/include/create_password.h"
#include "password_finder/include/password_check.h"
#include "password_finder/include/password_compare.h"
#include "password_finder/include/password_crack.h"
#include "password_finder/include/password_dictionary_attack.h"

string passwordToBeFound(void);

int main(void)
{
	string password_to_crack;
	string passwordFound;
	string trash_bin;
	char yn;

	START:switch (MainMenu())
	{
	case 0:
		password_to_crack = passwordToBeFound();
		passwordFound = Compare(password_to_crack);
		if (passwordFound != "")
			break;
		passwordFound = Cracker(password_to_crack);
		break;
	case 1:
		password_to_crack = passwordToBeFound();
		passwordFound = Cracker(password_to_crack);
		break;
	case 2:
		password_to_crack = passwordToBeFound();
		passwordFound = Compare(password_to_crack);
		break;
	case 3:
		// Dictionary attack.
		password_to_crack = passwordToBeFound();
		passwordFound = DictionaryAttack(password_to_crack);
		break;
	case 4:
		// method to generate password.
		passwordFound = CreatePassword();
		break;
	case 5:
		password_to_crack = passwordToBeFound();
		passwordFound = Compare(password_to_crack);
		if (passwordFound != "")
		{
			passwordFound = "Really weak, and is found amongst commonly used password. Please consider a different one.";
			break;
		}
		// method to check security of password
		passwordFound = CheckPassword(password_to_crack);
		break;
	}
	if (passwordFound != "")
		cout << "Password: " << passwordFound << endl;
	else
		cout << "Try again..." << endl;

	do {
		cout << "\n\nRestart? (1 for yes 0 for no): ";
		cin >> yn;
		getline(cin, trash_bin);
		switch (yn)
		{
		case '0':
			return 0;
		case '1':
			cout << endl;
			password_to_crack.clear();
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
	string password_to_crack;
	string trash_bin;
	cout << "Enter Password: ";
	cin >> password_to_crack;
	getline(cin, trash_bin);
	return password_to_crack;
}