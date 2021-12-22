/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: password_check.c
 * 
 * Description: Checks if password is valid.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "../include/password_check.h"
#include "../../password_component/include/password_component.h"

#define PASSWORDALPHABET 0
#define PASSWORDNUMBER 1
#define PASSWORDSYMBOL 2

#define UPPER 0
#define LOWER 1
#define NUMBERS 2
#define SPECIALSYMBOL 3
#define ALLSYMBOL 4

bool IsNumber(char);
bool IsUpper(char);
bool IsLower(char);
bool IsAlphabet(char);
bool IsSymbol(char);

/**
* @param password_to_crack the password that is being checked to
* certiify diffculty in cracking.
* @return feedback for the difficulty of the password to be cracked.
*/
string CheckPassword(string password_to_crack)
{
	string final_response;
	string response = ""; 
	int password_grade = 5;
	int password_length;
	int max_length = password_component.max_length;
	int minimum_length = password_component.minimum_length;
	// 0 alphabet, 1 numbers, 2 symbols
	int type[3] = {password_component.alphabet, password_component.numbers, password_component.symbol};
	// 0 upper , 1 lower, 2 number, 3 some symbol, 4 all symbol
	int challenge[5] = { 0,0,0,0,0 };
		
	// Based on length and Regex results will determing difficulty
	password_length = password_to_crack.length();

	for (int i = 0; i < password_length; i++)
	{
		if (IsUpper(password_to_crack[i]))
		{
			challenge[UPPER]++;
			continue;
		}
		if (IsLower(password_to_crack[i]))
		{
			challenge[LOWER]++;
			continue;
		}
		if (IsNumber(password_to_crack[i]))
		{
			challenge[NUMBERS]++;
			continue;
		}
		if (IsSymbol(password_to_crack[i]))
		{
			challenge[ALLSYMBOL]++;
			continue;
		}
		cout << "Character is no listed!" << endl;
	}

	if (minimum_length != max_length)
		if ((password_length - minimum_length) < (max_length - password_length))
		{
			response.append("Should be longer to maxamize security.\n");
			password_grade--;
		}

	switch (type[PASSWORDALPHABET])
	{
	case 1:
		switch (challenge[UPPER])
		{
		case 0:
			response.append("Since Upper is allowed, having at least 1 upper will increase secuirty.\n");
			password_grade -= 2;
			break;
		case 1:
			response.append("Having more than 1 upper will increase secuirty.\n");
			password_grade--;
			break;
		}
		break;
	case 2:
		switch (challenge[LOWER])
		{
		case 0:
			response.append("Since lower is allowed, having at least 1 lower will increase secuirty.\n");
			password_grade -= 2;
			break;
		case 1:
			response.append("Having more than 1 lower will increase secuirty.\n");
			password_grade--;
			break;
		}
		break;
	case 3:
		switch (challenge[UPPER])
		{
		case 0:
			response.append("Since Upper is allowed, having at least 1 upper will increase secuirty.\n");
			password_grade -= 2;
			break;
		case 1:
			response.append("Having more than 1 upper will increase secuirty.\n");
			password_grade--;
			break;
		default:
			break;
		}
		switch (challenge[LOWER])
		{
		case 0:
			response.append("Since lower is allowed, having at least 1 lower will increase secuirty.\n");
			password_grade -= 2;
			break;
		case 1:
			response.append("Having more than 1 lower will increase secuirty.\n");
			password_grade--;
			break;
		}
	}

	switch (type[PASSWORDNUMBER])
	{
	case 1:
		switch (challenge[NUMBERS])
		{
		case 0:
			response.append("Since Numbers is allowed, having at least 1 number will increase secuirty.\n");
			password_grade -= 2;
		case 1:
			response.append("Having more than 1 number will increase secuirty.\n");
			password_grade--;
			break;
		}
	}

	switch (type[PASSWORDSYMBOL])
	{
	case 2:
	case 1:
		switch (challenge[ALLSYMBOL])
		{
		case 0:
			response.append("Since Symbol is allowed, having at lesat 1 symbol will increase secuirty.\n");
			password_grade -= 2;
			break;
		case 1:
			response.append("Having more than 1 symbol will increase secuirty.\n");
			password_grade--;
			break;
		}
		break;
	}

	switch (password_grade)
	{
	case 5:
		final_response = "Amazing Password 5/5:\n";
		break;
	case 4:
		final_response = "Great Password 4/5:\n";
		break;
	case 3:
		final_response = "Okay Password 3/5\n";
		break;
	case 2:
		final_response = "Weak Password 2/5\n";
		break;
	case 1:
		final_response = "Bad Password 1/5\n";
		break;
	default:
		final_response = "Horrible Password 0/5\n";
		break;
	}

	final_response.append(response);

	return final_response;
}

bool IsNumber(char c)
{
	if (c >= 48 && c <= 57)
		return true;
	return false;
}

bool IsUpper(char c)
{
	if (c >= 65 && c <= 90)
		return true;
	return false;
}

bool IsLower(char c)
{
	if (c >= 97 && c <= 122)
		return true;
	return false;
}

bool IsAlphabet(char c)
{
	if (IsUpper(c) || IsLower(c))
		return true;
	return false;
}

bool IsSymbol(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) ||
		(c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return true;
	return false;
}