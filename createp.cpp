#include <iostream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>
#include "createp.h"
#include "passwordComponent.h"

int generateType(int);
char generateChar(int);
char generateAC(void);
char generateNum(void);
char generateSC(void);

/**
* Generates a password based on defined parameters
* @return created password as a string
*/
string createPassword(void)
{
	string password = "";
	int psize = pc.maxLength;
	char* passwordArray = new char[psize];
	int* arrayForPasswordType = new int[psize];
	srand(time(0));

	int type = 0;
	// build up what type
	if (pc.alphabet > 0)
		type += 1;
	if (pc.numbers > 0)
		type += 2;
	if (pc.symbol > 0)
		type += 4;

	// types allowed as passwords
	// alphabet (1), number (2), and special char (4)
	// if max is greater than the number of availabe types allow
	// minimillay 1 for each type
	
	retry:for (int i = 0; i < psize; i++)
		arrayForPasswordType[i] = generateType(type);
	
	// check there is min of each type
	bool minType[3] = { false };
	switch (type)
	{
	case 3:
		minType[0] = true;
		minType[1] = true;
		break;
	case 5:
		minType[0] = true;
		minType[2] = true;
		break;
	case 6:
		minType[1] = true;
		minType[2] = true;
		break;
	case 7:
		minType[0] = true;
		minType[1] = true;
		minType[2] = true;
		break;
	}

	if (!(type == 1 || type == 2 || type == 4))
	{
		for (int i = 0; i < psize; i++)
		{
			switch (arrayForPasswordType[i])
			{
			case 1:
				minType[0] = false;
				break;
			case 2:
				minType[1] = false;
				break;
			case 4:
				minType[2] = false;
				break;
			}
		}
		if (minType[0] == true || minType[1] == true || minType[2] == true)
			goto retry;
	}

	// in the portion below will fill in the rest.
	for (int i = 0; i < psize; i++)
		passwordArray[i] = generateChar(arrayForPasswordType[i]);
	
	password = convertToString(passwordArray, psize);
		
	delete[] passwordArray;
	delete[] arrayForPasswordType;
	
	return password;
}

/**
* @param type based on type will determin what value to store
* @return type that is to be stored
*/
int generateType(int type)
{
	int storedValue = -1;
	if (type == 1 || type == 2 || type == 4)
		storedValue = type;
	else
	{
		switch (type)
		{
		case 3:
			if (rand() % 2 == 0)
				storedValue = 1;
			else
				storedValue = 2;
			break;
		case 5:
			if (rand() % 2 == 0)
				storedValue = 1;
			else
				storedValue = 4;
			break;
		case 6:

			if (rand() % 2 == 0)
				storedValue = 2;
			else
				storedValue = 4;
			break;
		case 7:
			switch (rand() % 3)
			{
			case 0:
				storedValue = 1;
				break;
			case 1:
				storedValue = 2;
				break;
			case 2:
				storedValue = 4;
				break;
			}
		}
	}
	return storedValue;
}

/**
* based on type return appropriate char value
* types 1, 2, or 4
* @param type
* @return char value
*/
char generateChar(int type)
{
	char pchar = ' ';
	switch (type)
	{
	case 1:
		pchar = generateAC();
		break;
	case 2:
		pchar = generateNum();
		break;
	case 4:
		pchar = generateSC();
		break;
	}
	return pchar;
}

/**
* @return return alphabetical char based on password type
*/
char generateAC(void)
{
	int rValue = rand() % 26;
	switch (pc.alphabet)
	{
	case 1:
		rValue += 'A';
		break;
	case 2:
		rValue += 'a'; 
		break;
	case 3:
		if (rand() % 2 == 0)
			rValue += 'A';
		else
			rValue += 'a';
		break;
	}
	return rValue;
}

/**
* @return return num as a char
*/
char generateNum(void)
{
	return rand() % 10 + '0';
}

/**
* @return return special char based on password type
*/
char generateSC(void)
{
	int rValue = -1;

	// 15 ! - /
	// 7 : - @
	// 6 [ - `
	// 4 { - ~
	switch (pc.symbol)
	{
	case 1:
	case 2:
		switch (rand() % 4)
		{
		case 0:
			rValue = rand() % 15 + '!';
			break;
		case 1:
			rValue = rand() % 7 + ':';
			break;
		case 2:
			rValue = rand() % 6 + '[';
			break;
		case 3:
			rValue = rand() % 4 + '{';
			break;
		}
	}
	return rValue;
}
