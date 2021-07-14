#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "pcheck.h"
#include "passwordComponent.h"

#define PALPHABET 0
#define PNUMBERS 1
#define PSYMBOLS 2

#define UPPER 0
#define LOWER 1
#define NUMBERS 2
#define SSYMBOL 3
#define ASYMBOL 4

bool isNumber(char);
bool isUpper(char);
bool isLower(char);
bool isAlphabet(char);
bool isSymbol(char);

/**
* @param passwordToCrack the password that is being checked to
* certiify diffculty in cracking.
* @return feedback for the difficulty of the password to be cracked.
*/
string checkPassword(string passwordToCrack)
{
	string response = ""; 
	int passwordLength;
	int maxLength = pc.maxLength;
	int minLength = pc.minLength;
	// 0 alphabet, 1 numbers, 2 symbols
	int type[3] = {pc.alphabet, pc.numbers, pc.symbol};
	// 0 upper , 1 lower, 2 number, 3 some symbol, 4 all symbol
	int challenge[5] = { 0,0,0,0,0 };
		
	// Based on length and Regex results will determing difficulty
	passwordLength = passwordToCrack.length();

	for (int i = 0; i < passwordLength; i++)
	{
		if (isUpper(passwordToCrack[i]))
		{
			challenge[UPPER]++;
			continue;
		}
		if (isLower(passwordToCrack[i]))
		{
			challenge[LOWER]++;
			continue;
		}
		if (isNumber(passwordToCrack[i]))
		{
			challenge[NUMBERS]++;
			continue;
		}
		if (isSymbol(passwordToCrack[i]))
		{
			challenge[ASYMBOL]++;
			continue;
		}
		cout << "Character is no listed!" << endl;
	}

	if (minLength != maxLength)
	{
		if ((passwordLength - minLength) < (maxLength - passwordLength))
			response.append("Should be longer to maxamize security.\n");
	}

	switch (type[PALPHABET])
	{
	case 1:
		switch (challenge[UPPER])
		{
		case 0:
			response.append("Since Upper is allowed, having at least 1 upper will increase secuirty.\n");
			break;
		case 1:
			response.append("Having more than 1 upper will increase secuirty.\n");
			break;
		}
		break;
	case 2:
		switch (challenge[LOWER])
		{
		case 0:
			response.append("Since lower is allowed, having at least 1 lower will increase secuirty.\n");
			break;
		case 1:
			response.append("Having more than 1 lower will increase secuirty.\n");
			break;
		}
		break;
	case 3:
		switch (challenge[UPPER])
		{
		case 0:
			response.append("Since Upper is allowed, having 1 at least upper will increase secuirty.\n");
			break;
		case 1:
			response.append("Having more than 1 upper will increase secuirty.\n");
			break;
		default:
			break;
		}
		switch (challenge[LOWER])
		{
		case 0:
			response.append("Since lower is allowed, having 1 at least lower will increase secuirty.\n");
			break;
		case 1:
			response.append("Having more than 1 lower will increase secuirty.\n");
			break;
		}
	}

	switch (type[PNUMBERS])
	{
	case 1:
		switch (challenge[NUMBERS])
		{
		case 0:
			response.append("Since Numbers is allowed, having at least 1 number will increase secuirty.\n");
		case 1:
			response.append("Having more than 1 number will increase secuirty.\n");
			break;
		}
	}

	switch (type[PSYMBOLS])
	{
		switch (challenge[ASYMBOL])
		{
		case 0:
			response.append("Since Symbol is allowed, having at lesat 1 symbol will increase secuirty.\n");
			break;
		case 1:
			response.append("Having more than 1 symbol will increase secuirty.\n");
			break;
		}
		break;
	}

	return response;
}

bool isNumber(char c)
{
	if (c >= 48 && c <= 57)
		return true;
	return false;
}

bool isUpper(char c)
{
	if (c >= 65 && c <= 90)
		return true;
	return false;
}

bool isLower(char c)
{
	if (c >= 97 && c <= 122)
		return true;
	return false;
}

bool isAlphabet(char c)
{
	if (isUpper(c) || isLower(c))
		return true;
	return false;
}

bool isSymbol(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) ||
		(c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return true;
	return false;
}