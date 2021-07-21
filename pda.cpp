#include <iostream>
#include <string>
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
	// collect user data
	while (true)
	{
		wordToEnter = collectDataMenu();
		if (wordToEnter.compare("&&&") == 0)
			break;
		userData.push_back(wordToEnter);
	}

	// password generation

	// generate passwords and compare
	finalWord = wordToEnter;

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
	cout << "Please enter the word you wish to enter into the dictionary\n"
		"(Enter &&& to stop): ";
	cin >> returnword;
	return returnword;
}
