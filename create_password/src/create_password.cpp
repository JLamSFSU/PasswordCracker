/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: create_password.c
 * 
 * Description: Creates passwords for user based on parameter given.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>
#include "../include/create_password.h"
#include "../../password_component/include/password_component.h"

int GenerateType(int);
bool MinimalRequirement(int[], int, int);
char GenerateChar(int);
char GenerateAlphabeticalChar(void);
char GenerateNumber(void);
char GenerateSpecialChar(void);

/**
* Generates a password based on defined parameters
* @return created password as a string
*/
string CreatePassword(void)
{
	string password = "";
	int password_size = password_component.max_length;
	char* password_array = new char[password_size];
	int* array_for_password_type = new int[password_size];
	srand(time(0));

	int type = 0;
	// build up what type
	if (password_component.alphabet > 0)
		type += 1;
	if (password_component.numbers > 0)
		type += 2;
	if (password_component.symbol > 0)
		type += 4;

	// types allowed as passwords
	// alphabet (1), number (2), and special char (4)
	// if max is greater than the number of availabe types allow
	// minimillay 1 for each type
	
	retry:for (int i = 0; i < password_size; i++)
		array_for_password_type[i] = GenerateType(type);
	
	// check to bypass minimal requirments in the password.
	if (((type == 3 || type > 4) && password_size < 2) ||
		(type == 7 && password_size < 3))
		goto create;

	// return to regenerate a new password format if it fails minimal req. 
	if (!(type == 1 || type == 2 || type == 4) &&
		MinimalRequirement(array_for_password_type, type, password_size))
		goto retry;

	// in the portion below will fill in the rest.
	create:for (int i = 0; i < password_size; i++)
		password_array[i] = GenerateChar(array_for_password_type[i]);
	
	password = ConvertToString(password_array, password_size);
		
	delete[] password_array;
	delete[] array_for_password_type;
	
	return password;
}

/**
* @param type based on type will determin what value to store
* @return type that is to be stored
*/
int GenerateType(int type)
{
	int stored_value = -1;
	if (type == 1 || type == 2 || type == 4)
		stored_value = type;
	else
	{
		switch (type)
		{
		case 3:
			if (rand() % 2 == 0)
				stored_value = 1;
			else
				stored_value = 2;
			break;
		case 5:
			if (rand() % 2 == 0)
				stored_value = 1;
			else
				stored_value = 4;
			break;
		case 6:

			if (rand() % 2 == 0)
				stored_value = 2;
			else
				stored_value = 4;
			break;
		case 7:
			switch (rand() % 3)
			{
			case 0:
				stored_value = 1;
				break;
			case 1:
				stored_value = 2;
				break;
			case 2:
				stored_value = 4;
				break;
			}
		}
	}
	return stored_value;
}

/**
* @param array_for_password_type, the array of ints that store the types on char to
* be use in the created password.
* @param type, parameters required in the password.
* @param password_size max sixe of the password.
* return true or false if the array fulfill the requirements.
*/
bool MinimalRequirement(int array_for_password_type[], int type, int password_size)
{
	bool minimal_type[3] = { false };

	// check there is min of each type
	switch (type)
	{
	case 3:
		minimal_type[0] = true;
		minimal_type[1] = true;
		break;
	case 5:
		minimal_type[0] = true;
		minimal_type[2] = true;
		break;
	case 6:
		minimal_type[1] = true;
		minimal_type[2] = true;
		break;
	case 7:
		minimal_type[0] = true;
		minimal_type[1] = true;
		minimal_type[2] = true;
		break;
	}

	for (int i = 0; i < password_size; i++)
	{
		switch (array_for_password_type[i])
		{
		case 1:
			minimal_type[0] = false;
			break;
		case 2:
			minimal_type[1] = false;
			break;
		case 4:
			minimal_type[2] = false;
			break;
		}
	}
	if (minimal_type[0] == true || minimal_type[1] == true || minimal_type[2] == true)
		return true;
	return false;
}

/**
* based on type return appropriate char value
* types 1, 2, or 4
* @param type
* @return char value
*/
char GenerateChar(int type)
{
	char password_char = ' ';
	switch (type)
	{
	case 1:
		password_char = GenerateAlphabeticalChar();
		break;
	case 2:
		password_char = GenerateNumber();
		break;
	case 4:
		password_char = GenerateSpecialChar();
		break;
	}
	return password_char;
}

/**
* @return return alphabetical char based on password type
*/
char GenerateAlphabeticalChar(void)
{
	int random_value = rand() % 26;
	switch (password_component.alphabet)
	{
	case 1:
		random_value += 'A';
		break;
	case 2:
		random_value += 'a'; 
		break;
	case 3:
		if (rand() % 2 == 0)
			random_value += 'A';
		else
			random_value += 'a';
		break;
	}
	return random_value;
}

/**
* @return return num as a char
*/
char GenerateNumber(void)
{
	return rand() % 10 + '0';
}

/**
* @return return special char based on password type
*/
char GenerateSpecialChar(void)
{
	int random_value = -1;

	// 15 ! - /
	// 7 : - @
	// 6 [ - `
	// 4 { - ~
	switch (password_component.symbol)
	{
	case 1:
	case 2:
		switch (rand() % 4)
		{
		case 0:
			random_value = rand() % 15 + '!';
			break;
		case 1:
			random_value = rand() % 7 + ':';
			break;
		case 2:
			random_value = rand() % 6 + '[';
			break;
		case 3:
			random_value = rand() % 4 + '{';
			break;
		}
	}
	return random_value;
}
