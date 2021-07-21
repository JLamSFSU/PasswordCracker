#include <iostream>
#include <string>
// #include <fstream>
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
	string wordToEnter, finalWord;
	// collect user data
	while (true)
	{
		wordToEnter = collectDataMenu();
		if (wordToEnter.compare("&&&") == 0)
			break;
		if (wordToEnter.compare("%%%") == 0)
		{
			cout << "Current Dictionary:" << endl;
			for (int i = 0; i < userData.size(); i++)
				cout << i + 1 << " - " << userData[i] << endl;
			continue;
		}
		userData.push_back(wordToEnter);
	}

	// password generation

	// generate passwords and compare
	finalWord = wordToEnter;

	// return match
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
		"(Enter &&& to stop or %%% to view current list): ";
	cin >> returnword;
	getline(cin, trashbin);
	return returnword;
}
