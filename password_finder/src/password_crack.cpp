/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: password_crack.c
 * 
 * Description: Password Cracker brute forces the pasword combination.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <thread>
#include "password_crack.h"
#include "password_component.h"
#define NUMBERSONLY 10
#define ALPHABETONLY 100

int IteratePasswordPosition(char[], int, int, int, int);
int IterateChar(char[], int, int);
int ExpandPassword(char[], int, int, int);
int ResetPosition(int);

/**
* https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
*/
string Cracker(string password_to_crack)
{
	int type = 0;
	string password;
	char* password_array = new char[password_component.max_length];
	int size = 0;

	// cout << "Running Password Cracker" << endl;

	// init parameters
	if (password_component.numbers == 0 && password_component.alphabet == 0 && password_component.symbol == 0)
	{
		return "";
	}
	else
	{
		if (password_component.numbers > 0)
		{
			type = NUMBERSONLY;
		}
		switch (password_component.alphabet)
		{
		case 3:
			type += ALPHABETONLY;
		case 2:
			type += ALPHABETONLY;
		case 1:
			type += ALPHABETONLY;
			break;
		}
		switch (password_component.symbol)
		{
		case 2:
			type += 1;
		case 1:
			type += 1;
			break;
		}
	}

	if (debug_bool) cout << "type: " << type << endl;

	// Initilaze string to Compare
	size = ExpandPassword(password_array, password_component.max_length, password_component.minimum_length - 1, type);

	// begin cracking...
	cout << "Cracking..." << endl;
	while (true)
	{	
		password = ConvertToString(password_array, size);
		if (debug_bool) cout << "Testing: " << password << endl;
		if (password_to_crack.Compare(password) == 0)
		{
			cout << "Password Found." << endl;
			break;
		}

		size = IteratePasswordPosition(password_array, password_component.max_length, size, size - 1, type);
		if (size == -1)
		{
			cout << "Not Found" << endl;
			exit(0);
		}
	}
	delete[] password_array;
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
int IteratePasswordPosition(char password[], int max_size, int size, int position, int type)
{
	if (type <= 2 && password[position] == 126 && position > 0) // overflow for special char
	{
		if (debug_bool) cout << "case 1" << endl;
		// Deal with special character
		if (password[position - 1] == 126)
			size = IteratePasswordPosition(password, max_size, size, position - 1, type);
		else
			password[position - 1] = IterateChar(password,position - 1, type);
		if (type % 10 == 1 || type % 10 == 2)
			password[position] = ResetPosition(type);
	} 
	else if (type <= 12 && password[position] == 57 && position > 0) // when char reaches max for special and number
	{
		if (debug_bool) cout << "case 2" << endl;
		// Deals with numbers
		if (password[position - 1] == 57)
			size = IteratePasswordPosition(password, max_size, size, position - 1, type);
		else
			password[position - 1] = IterateChar(password, position - 1, type);
		if (type == NUMBERSONLY || type == 11 || type == 12)
			password[position] = ResetPosition(type);

	}
	else if (((password[position] == 90 && type < 200) || (password[position] == 122 && type >= 200)) && position > 0)
	{
		if (debug_bool) cout << "case 3 " << position << ":"<< size <<endl;
		// Deals with Alphabet
		if ((type < 200 && password[position - 1] == 90) || (type >= 200 && password[position - 1] == 122))
			size = IteratePasswordPosition(password, max_size, size, position - 1, type);
		else
			password[position - 1] = IterateChar(password, position - 1, type);
		if (type >= ALPHABETONLY)
			password[position] = ResetPosition(type);
	}
	else
	{
		if (debug_bool) cout << "case 4" << endl;
		// Expands the passowrd if at capacity
		if (position == 0 &&
			((type <= 12 && password[position] == 57) ||
				(type == 1 && password[position] == 126) ||
				(type == 2 && password[position] == 126) ||
				(type >= 200 && password[position] == 122) ||
				(type >= 100 && password[position] == 90)))
			return ExpandPassword(password, max_size, size, type);
		else
			password[position] = IterateChar(password, position, type);
	}
	return size;
}

/**
* @param password the password
* @param position current position in the password array to iterate
* @param type password type for iterating through all special char
* @return the new loaction in iteration
*/
int IterateChar(char password[], int position, int type)
{
	if (debug_bool) cout << "Iterating Special Char" << endl;
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
int ExpandPassword(char password[], int max_size, int size, int type)
{
	if (debug_bool) cout << "Expanding...\nSize:Maxsize\n" << size << ":" << max_size << endl;
	if (size == max_size)
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
	if (debug_bool) cout << endl;
	return size + 1;
}

/**
* Returns the value for which the password is to be set to pending on the type
* @param type password type
* @return position to set the char
*/
int ResetPosition(int type)
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
