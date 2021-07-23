#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "pda.h"
#include "passwordComponent.h"

string collectDataMenu(void);
string digitToWord(int);
// string varyDataCollected(string);

int buildDictionary(vector <string> &words);
int manualInputDictionary(vector <string> &words);
int removeFromDictionary(vector <string> &words);

ifstream dictionaryImport;

/**
* https://cybernews.com/best-password-managers/password-cracking-techniques/
* #5 & #6 as refernce for function.
*/
string dictionaryAttack(string passwordToCrack)
{
	vector <string> userData;
	string finalWord;
	int userDataSize, datacombo;

	// import part of the dictionary using a file
	if (buildDictionary(userData) == -1)
		exit(-1);

	// collect user manual input data
	if (manualInputDictionary(userData) == -1)
		exit(-1);
	
	// remove from list
	if (removeFromDictionary(userData) == -1)
		exit(-1);

	// password generation
	userDataSize = userData.size();

	// remove from list again.

	// generate passwords and compare
	finalWord = userData[0];

	if (true) // debugbool later
	{
		cout << "Dictionary before exit:" << endl;
		for (int i = 0; i < userDataSize; i++)
			cout << userData[i] << endl;
	}

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

/**
* Currently only works for some case of 0-12.
* Needs to be upgraded for more cases somehow.
* @param number the number that is to convert to the word version
* @return the word version of the number
*/
string digitToWord(int number)
{
	vector <string> list = { "zero", "one", "two", "three", "four", "five", "six",
							"seven", "eight", "nine", "ten", "eleven", "twelve" };

	return list[number];
}

/**
* @param words the dictionary to be added to
* @return error code
*/
int buildDictionary(vector <string> &words)
{
	string wordToEnter, userInput, trashbin;

	while (true)
	{
		cout << "Would you like to import part of the dictionary? (y/n) ";
		cin >> userInput;
		getline(cin, trashbin);
		if (userInput.compare("y") == 0)
			break;
		if (userInput.compare("n") == 0)
			return 0;
	}

	// import file here;
	dictionaryImport.open("dictionary.txt");
	if (!dictionaryImport.is_open())
	{
		cout << "Dictionary can not be found or opened..." << endl;
		return -1;
	}

	while (true)
	{
		dictionaryImport >> wordToEnter;
		words.push_back(wordToEnter);
		if (dictionaryImport.eof())
			break;
	}
	
	dictionaryImport.close();
	if (dictionaryImport.is_open())
	{
		cout << "Issue closing file..." << endl;
		return -1;
	}
		
	return 0;
}

/**
* @param words the dictionary vector to be added to
* @return error code
*/
int manualInputDictionary(vector <string>& words)
{
	string wordToEnter;
	while (true)
	{
		wordToEnter = collectDataMenu();
		if (wordToEnter.compare("&&&") == 0)
			break;
		if (wordToEnter.compare("%%%") == 0)
		{
			cout << "Current Dictionary:" << endl;
			for (int i = 0; i < words.size(); i++)
				cout << i + 1 << " - " << words[i] << endl;
			continue;
		}
		words.push_back(wordToEnter);
	}
	return 0;
}

/**
* remove from list that does not meet the requirements
* such as exceeding max length or having numbers when
* numbers are not allowed.
* @param words the dictionary vector to be added to
* @return error code
*/
int removeFromDictionary(vector <string>& words)
{
	std::string::size_type sz;
	int type[3] = { pc.alphabet, pc.numbers, pc.symbol };
	int numberAsInt;
	int maxLength = pc.maxLength;
	int iteration = 0;

	bool doNotRemoveWord = true;

	regex cap(".*[a-z]+");
	regex allLeters(".*[A-Za-z]+");
	regex dig(".*[0-9]+");
	// Needs another list of spec chars for specific exclusion
	regex specChar(".*[!\"#$'()*+-./:;<=>?@^_`{|}~]+");
	// Above is missing some other spec chars like [, ], and \

	while (true)
	{
		if (iteration >= words.size())
			break;
		// deals with alphabet
		/*
		* psuedo:
		* if alphabet is not allowed
		* if word contains alphabet remove
		*
		* "might need to do something that varies the
		* cap sensitivity here as well if cap sensitivity
		* is active."
		*/
		// if (userData[i])

		// deals with numbers
		/*
		* if numbers is not allowed
		* if string contains numbers remove
		*/
		// turn number to words (i.e. 1 -> one)
		if (type[0] > 0 && regex_match(words[iteration], dig) &&
			(!regex_match(words[iteration], allLeters) ||
				!regex_match(words[iteration], specChar)))
		{
			numberAsInt = stoi(words[iteration], &sz);
			if (numberAsInt <= 12 && numberAsInt >= 0)
				words.push_back(digitToWord(numberAsInt));
		}

		if (doNotRemoveWord && type[1] == 0 && regex_match(words[iteration], dig))
			doNotRemoveWord = false;

		// deals with symbols
		/*
		* if symbols is not allowed
		* "might need to do two conditional one for all and one for special"
		* if string contains symbols remove
		*/
		if (doNotRemoveWord && type[2] == 0 && regex_match(words[iteration], specChar))
			doNotRemoveWord = false;

		// deals with length
		if (doNotRemoveWord && words[iteration].length() > maxLength)
			doNotRemoveWord = false;

		if (!doNotRemoveWord)
		{
			words.erase(words.begin() + iteration);
			doNotRemoveWord = true;
			continue;
		}

		// iterator or break;
		if (iteration < words.size() - 1)
			iteration++;
		else
			break;
	}
	return 0;
}
