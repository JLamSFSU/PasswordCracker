#include <iostream>
#include <string>
#include <fstream>
#include <thread>
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
	bool regexCase = true;
	string tempWord;
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
		if (regexCase)// pass regex store to list
		{
			listOfP[sizeOfList] = tempWord;
			sizeOfList++;
		}
	}

	// cout << "Printing file:" << endl;
	// for (int i = 0; i < sizeOfList; i += 10)
	// 	cout << listOfP[i] << endl;
	
	return sizeOfList;
}