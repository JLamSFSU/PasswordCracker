#include <iostream>
#include <string>
#include <thread>
#include "pcrack.h"
#include "passwordComponent.h"
#define NUMBERSONLY 10
#define ALPHABETONLY 100

int iteratePasswordPosition(char[], int, int, int, int);
int iterateChar(char[], int, int);
int expand(char[], int, int, int);
int resetPosition(int);

/**
* https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
*/
string cracker(string passwordToCrack)
{
	int type = 0;
	string password;
	char* passwordArray = new char(pc.maxLength);
	int size = 0;

	// cout << "Running Password Cracker" << endl;

	// init parameters
	if (pc.numbers == 0 && pc.alphabet == 0 && pc.symbol == 0)
	{
		return "";
	}
	else
	{
		if (pc.numbers > 0)
		{
			type = NUMBERSONLY;
		}
		switch (pc.alphabet)
		{
		case 3:
			type += ALPHABETONLY;
		case 2:
			type += ALPHABETONLY;
		case 1:
			type += ALPHABETONLY;
			break;
		}
		switch (pc.symbol)
		{
		case 2:
			type += 1;
		case 1:
			type += 1;
			break;
		}
	}

	// cout << "type: " << type << endl;

	// Initilaze string to compare
	size = expand(passwordArray, pc.maxLength, pc.minLength - 1, type);

	// begin cracking...
	cout << "Cracking..." << endl;
	while (true)
	{	
		password = convertToString(passwordArray, size);
		// cout << "Testing: " << password << endl;
		if (passwordToCrack.compare(password) == 0)
		{
			cout << "Password Found." << endl;
			break;
		}

		size = iteratePasswordPosition(passwordArray, pc.maxLength, size, size - 1, type);
		if (size == -1)
		{
			cout << "Not Found" << endl;
			exit(0);
		}
	}
	return password;
}

/**
* @param password the password that is to be changed
* @param size size of the password
* @param position the position that needs to be changed
* @param type passward type
* @return new size
* types:
*   010 numbers only
*   100 alphabet only
*     0 no alphabet, 1 none cap sensiteve, 2 cap sensitive
*   001 special character only
*     0 no symbols, 1 some symbols, 2 all symbols
*/
int iteratePasswordPosition(char password[], int maxsize, int size, int position, int type)
{
	if (type <= 2 && password[position] == 126 && position > 0) // overflow for special char
	{
		// cout << "case 1" << endl;
		// Deal with special character
		if (password[position - 1] == 126)
			size = iteratePasswordPosition(password, maxsize, size, position - 1, type);
		else
			password[position - 1] = iterateChar(password,position - 1, type);
		if (type % 10 == 1 || type % 10 == 2)
			password[position] = resetPosition(type);
	} 
	else if (type <= 12 && password[position] == 57 && position > 0) // when char reaches max for special and number
	{
		// cout << "case 2" << endl;
		// Deals with numbers
		if (password[position - 1] == 57)
			size = iteratePasswordPosition(password, maxsize, size, position - 1, type);
		else
			password[position - 1] = iterateChar(password, position - 1, type);
		if (type == NUMBERSONLY || type == 11 || type == 12)
			password[position] = resetPosition(type);

	}
	else if (((password[position] == 90 && type < 200) || (password[position] == 122 && type >= 200)) && position > 0)
	{
		// cout << "case 3 " << position << ":"<< size <<endl;
		// Deals with Alphabet
		if ((type < 200 && password[position - 1] == 90) || (type >= 200 && password[position - 1] == 122))
			size = iteratePasswordPosition(password, maxsize, size, position - 1, type);
		else
			password[position - 1] = iterateChar(password, position - 1, type);
		if (type >= ALPHABETONLY)
			password[position] = resetPosition(type);
	}
	else
	{
		// cout << "case 4" << endl;
		// Expands the passowrd if at capacity
		if (position == 0 &&
			((type <= 12 && password[position] == 57) ||
				(type == 1 && password[position] == 126) ||
				(type == 2 && password[position] == 126) ||
				(type >= 200 && password[position] == 122) ||
				(type >= 100 && password[position] == 90)))
			return expand(password, maxsize, size, type);
		else
			password[position] = iterateChar(password, position, type);
	}
	return size;
}

/**
* @param password the password
* @param position current position in the password array to iterate
* @param type password type for iterating through all special char
* @return the new loaction in iteration
*/
int iterateChar(char password[], int position, int type)
{
	// cout << "Iterating Special Char" << endl;
	if (type % 10 != 0)
	{
		switch (password[position])
		{
		case 47:
			return 58;
		case 64:
			return 91;
		case 96:
			return 123;
		case 126:
			if (type > 2 && type % 100 >= 10)
				return 48;
			if (type / 100 == 2)
				return 97;
			if (type > 100)
				return 65;
		}
	}
	if (type > 100 && type % 100 > 0)
	{
		if (type / 100 == 2)
			switch (password[position])
			{
			case 57:
				return 97;
			}
		switch (password[position])
		{
		case 57:
			return 65;
		}
	}
	if (type >= 200) // cap sensitive
	{
		switch (password[position])
		{
		case 90:
			return 97;
		}
	}
	return password[position] + 1;
}

/**
* @param password[] the password that is to be changed
* @param size size of current password
* @param type password type
* @return new size of password
*/
int expand(char password[], int maxsize, int size, int type)
{
	// cout << "Expanding...\nSize:Maxsize\n" << size << ":" << maxsize << endl;
	if (size == maxsize)
		return -1;
	for (int i = 0; i <= size; i++)
	{

		if (type % 10 == 1 || type % 10 == 2)
			password[i] = '!';
		else if (type % 100 > 0)
			password[i] = '0';
		else if (type / 100 == 2)
			password[i] = 'a';
		else
			password[i] = 'A';
	}
	// cout << endl;
	return size + 1;
}

/**
* Returns the value for which the password is to be set to pending on the type
* @param type password type
* @return position to set the char
*/
int resetPosition(int type)
{
	if (type % 10 == 1 || type % 10 == 2)
		return 33;
	else if (type % 100 > 0)
		return 48;
	else if (type / 100 == 2)
		return 97;
	else
		return 65;
}
