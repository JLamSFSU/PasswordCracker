#include <iostream>
#include <string>
#include <thread>
#include "pcrack.h"
#define NUMBERSONLY 10
#define ALPHABETONLY 100

string convertToString(char*, int);

int iteratePasswordPosition(char[], int, int, int, int);
int expand(char[], int, int, int);
int resetPosition(int);

/**
* https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
*/
string cracker(string passwordToCrack, int* parameters)
{
	int minLength, maxLength, numbers, alphabet, symbol;
	int type = 0;
	string password;
	char* passwordArray = new char(*(parameters + 1));
	int size = 0;

	cout << "Running Password Cracker" << endl;

	// init parameters
	if (*(parameters + 2) == 0 && *(parameters + 3) == 0 && *(parameters + 4) == 0)
	{
		return "";
	}
	else
	{
		minLength = *(parameters);
		maxLength = *(parameters + 1);
		numbers = *(parameters + 2);
		if (numbers > 0)
		{
			type = NUMBERSONLY;
		}
		alphabet = *(parameters + 3);
		switch (alphabet)
		{
		case 2:
			type += ALPHABETONLY;
		case 1:
			type += ALPHABETONLY;
			break;
		default:
			break;
		}
		symbol = *(parameters + 4);
		switch (symbol)
		{
		case 2:
			type += 1;
		case 1:
			type += 1;
			break;
		default:
			break;
		}
	}

	cout << "type: " << type << endl;

	// Initilaze string to compare
	size = expand(passwordArray, maxLength, minLength - 1, type);

	// begin cracking...
	cout << "Cracking..." << endl;
	while (true)
	{
		password = convertToString(passwordArray, size);
		if (passwordToCrack.compare(password) == 0)
		{
			cout << "Password Found." << endl;
			break;
		}

		size = iteratePasswordPosition(passwordArray, maxLength, size, size - 1, type);
		if (size == -1)
		{
			cout << "Not Found" << endl;
			return "";
		}
	}
	return password;
}

string convertToString(char* a, int size)
{
	string s = "";
	for (int i = 0; i < size; i++)
		s = s + a[i];
	return s;
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
	if ((resetPosition(type) == 33 || resetPosition(type) == 48) && password[position] == 57 && position > 0)
	{
		if (password[position - 1] == 57)
			size = iteratePasswordPosition(password, maxsize, size, position - 1, type);
		else
			password[position - 1] += 1;
		if (type == NUMBERSONLY)
			password[position] = resetPosition(type);
	}
	else
	{
		if (position == 0 && password[position] == 57)
			return expand(password, maxsize, size, type);
		else
			password[position] += 1;
	}
	return size;
}

/**
* @param password[] the password that is to be changed
* @param size size of current password
* @param type password type
* @return new size of password
*/
int expand(char password[], int maxsize, int size, int type)
{
	cout << "Expanding...\nSize:Maxsize\n" << size << ":" << maxsize << endl;
	if (size == maxsize)
		return -1;
	for (int i = 0; i <= size; i++)
	{
		switch (type)
		{
		default:
			password[i] = '!';
			break;
		case NUMBERSONLY:
			password[i] = '0';
			break;
		case ALPHABETONLY:
		case 200: // cap sensitive
			password[i] = 'A';
			break;
		}
		cout << password[i];
	}
	cout << endl;
	return size + 1;
}


int resetPosition(int type)
{
	int rPos = 0;
	switch (type)
	{
		default:
			rPos = 33;
			break;
		case NUMBERSONLY:
			rPos = 48;
			break;
		case ALPHABETONLY:
		case 200: // cap sensitive
			rPos = 65;
			break;
	}
	return rPos;
}