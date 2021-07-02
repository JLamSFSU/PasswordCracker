#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <regex>
#include "pcompare.h"
#include "passwordComponent.h"

int getList(string[]);
bool fileCondition = false;
ifstream file;

/**
* https://www.passwordrandom.com/most-popular-passwords
* @param passwordToCrack password to find
* @return the password found.
*/
string compare(string passwordToCrack)
{
	cout << "Comparing..." << endl;
	string myArray[100];
	int sizeOfList;

	if (fileCondition == false)
	{
		file.open("file.txt");
		if (!file.is_open())
		{
			cout << "File can not be found or opened..." << endl;
			return "";
		}
		fileCondition = true;
	}


	while (true)
	{
		sizeOfList = getList(myArray);

		for (int i = 0; i < sizeOfList; i++)
		{
			// cout << i <<") Checking: " << myArray[i] << endl;;
			if (passwordToCrack.compare(myArray[i]) == 0)
			{
				cout << "Password is found in database..." << endl;
				file.close();
				fileCondition = false;
				return myArray[i];
			}
		}

		if (sizeOfList == -1)
		{
			cout << "Password can not be found in list..." << endl;
			file.close();
			fileCondition = false;
			return "";
		}
	}

	return "";
}

/**
* Fills the list of prexisiting password to match with,
* the list is populated up to 100 words and only stores
* the words that match the parameters when initialized.
* @param listOfP is a the list that is given back to compare
* and find the password.
* @return actual size of the list being passed back
*/
int getList(string listOfP[])
{
	int sizeOfList = 0;
	string tempWord;
	regex cap(".*[a-z]+");
	regex allLeters(".*[A-Za-z]+");
	regex dig(".*[0-9]+");
	// Needs another list of spec chars for specific exclusion
	regex specChar(".*[!\"#$'()*+-./:;<=>?@^_`{|}~]+");
	// Above is missing some other spec chars like [, ], and \

	if (file.eof())
		return -1;

	if (!file.good())
	{
		cout << "error with file..." << endl;
		return -1;
	}

	for (int i = 0; i < 100; i++)
	{
		file >> tempWord;

		// exclusionary conditions
		if (tempWord.length() < pc.minLength || tempWord.length() > pc.maxLength)
			continue;

		// need to be upgraded to deal with case sensetive.
		if (pc.alphabet == 0 && regex_match(tempWord, allLeters))
			continue;

		if (pc.alphabet == 1 && regex_match(tempWord, cap))
			continue;

		if (pc.numbers == 0 && regex_match(tempWord, dig))
			continue;

		// needs to include case for special char inclusion
		if (pc.symbol == 0 && regex_match(tempWord, specChar))
			continue;

		/*
		cout << tempWord;
		if (regex_match(tempWord, cap))
			cout << " Has lower case Letter";
		if (regex_match(tempWord, allLeters))
			cout << " Has A letter";
		if (regex_match(tempWord, dig))
			cout << " Has A Digit";
		if (regex_match(tempWord, mix))
			cout << " mix";
		if (regex_match(tempWord, specChar))
			cout << " spec Char";
		cout << endl;
		*/

		// Regex case goes here which determines if it stores
		// the word to check.

		// pass regex store to list
		listOfP[sizeOfList] = tempWord;
		sizeOfList++;
	}
	
	return sizeOfList;
}