#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include "pda.h"
#include "passwordComponent.h"

string collectDataMenu(void);
// string varyDataCollected(string);

/**
* https://cybernews.com/best-password-managers/password-cracking-techniques/
* #5 & #6 as refernce for function.
*/
string dictionaryAttack(string passwordToCrack)
{
	vector <string> userData;
	string wordToEnter;
	string finalWord;
	string tempword;
	// collect user data
	while (true)
	{
		cin.clear();
		wordToEnter = collectDataMenu();
		if (wordToEnter.compare("&&&") == 0)
			break;
		stringstream ss(wordToEnter);
		while (getline(ss, tempword, ' '))
			userData.push_back(tempword);
	}

	// password generation

	// generate passwords and compare
	finalWord = wordToEnter;

	cout << "User Data:" << endl;
	for (int i = 0; i < userData.size(); i++)
	{
		cout << userData[i] << endl;
	}

	return finalWord;
}

/**
* Displays a menu that allows the user to continually add to
* the vector.
* @return words to be added to the vector, if return is "" end collection.
*/
string collectDataMenu()
{
	string returnword;
	string trashbin;
	cout << "Please enter a word or number you wish to enter into the dictionary\n"
		"(Enter &&& to stop): ";
	cin >> returnword;
	getline(cin, trashbin);
	return returnword;
}
