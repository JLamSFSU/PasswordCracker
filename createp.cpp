#include <iostream>
#include <string>
#include <regex>
#include "createp.h"
#include "passwordComponent.h"

/**
* Generates a password based on defined parameters
* @return created password as a string
*/
string createPassword(void)
{
	string password = "";
	int psize = pc.maxLength;
	int positionInArray = 0;
	bool paramNotMet;
	char pchar;
	char* passwordArray = new char(psize);

	// char variable here
	randomize:for (int i = 0; i < psize; i++)
	{
		paramNotMet = true;
		while (paramNotMet)
		{
			// randomizer till char meets one of the param
			pchar = '1';
			paramNotMet = false;
		}
		passwordArray[i] = pchar;
	}

	password = convertToString(passwordArray, psize);

	// regex the array, if does not pass goto above loop to retry.
	if (pc.numbers > 0 && !regex_match(password, regex(".*[0-9]+")))
	{
		cout << "fail criteria" << endl;
		goto randomize;
	}

	return password;
}