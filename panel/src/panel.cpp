/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: panel.c
 * 
 * Description: Generate user interface for user
 *****************************************************************************/

#include <string>
#include "../include/panel.h"
#include "../../password_component/include/password_component.h"
#include "../../password_finder/include/password_crack.h"

int UseNumbers(void);
int UseAlphabet(void);
int UseSpecialChar(void);
int MethodToUse(void);

PasswordComponent password_component = PasswordComponent();

/**
* Establish a menu to set the paramters to set the passward Cracker.
* @param passwardToCrack provided password to find
* @return integer value of what to use to find password
*/
int MainMenu(void)
{
	string trash_bin, user_input;
	std::string::size_type sz;
	int minimum_length, max_length, numbers, alphabet, symbol;
	static int return_value [5] = {0};

	cout << "Please complete the passwords parameters:" << endl;

	do {
		cout << "The min Length of password: ";
		cin >> user_input;
		getline(cin, trash_bin);
		try 
		{
			minimum_length = stoi(user_input, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}

		cout << "The max Length of password: ";
		cin >> user_input;
		getline(cin, trash_bin);
		try
		{
			max_length = stoi(user_input, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}

		if (minimum_length <= max_length && minimum_length > 0)
			break;
		cout << "Password Max can not be less than Min length.\nPlease Try Again" << endl;
	} while (true);

	if (true) // testing
	{
		alphabet = UseAlphabet();
		numbers = UseNumbers();
		symbol = UseSpecialChar();
	}
	else
	{
		alphabet = 0;
		numbers = 1;
		symbol = 0;
	}

	if (alphabet == 0 && numbers == 0 && symbol == 0)
		cout << "Bad Parameters!" << endl;
	else
		SetPasswordComponent(minimum_length, max_length, numbers, alphabet, symbol);

	return MethodToUse();
}

/**
* Menu for inclusion of numbers
* @return 0 no Numbers, 1 use Numbers 
*/
int UseNumbers(void)
{
	string trash_bin, user_input;
	std::string::size_type sz;
	int numbers = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Numbers Used      *\n"
			"* 1 - Use Numbers          *\n"
			"****************************\n"
			"Please Enter 0 or 1: ";
		cin >> user_input;
		getline(cin, trash_bin);
		try
		{
			numbers = stoi(user_input, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}
		if (numbers == 0 || numbers == 1)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return numbers;
}

// needs to be upgraded to have option for lower case only.
/**
* Menu for inclusion of alphabet
* @return 0 no alphabet, 1 none cap sensiteve, 2 cap sensitive
*/
int UseAlphabet(void)
{
	string trash_bin, user_input;
	std::string::size_type sz;
	int alphabet = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Alphabet Used     *\n"
			"* 1 - Use Captilze Alphabet*\n"
			"* 2 - Use Lower Case only  *\n"
			"* 3 - Case Sensitive       *\n"
			"****************************\n"
			"Please Enter 0, 1, 2, or 3: ";
		cin >> user_input;
		getline(cin, trash_bin);
		try
		{
			alphabet = stoi(user_input, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}
		if (alphabet >= 0 && alphabet <= 3)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return alphabet;
}

/**
* Menu for inclusion of special characters
* @return 0 no symbols, 1 some symbols, 2 all symbols
*/
int UseSpecialChar(void)
{
	string trash_bin, user_input;
	std::string::size_type sz;
	int symbol = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Symbols Used      *\n"
			"* 1 - Use Spceial Symbol   *\n"
			"* 2 - All Symbols          *\n"
			"* Differnce between 1 and 2*\n"
			"*   is not implemented at  *\n"
			"*   this time.             *\n"
			"****************************\n"
			"Please Enter 0, 1, or 2: ";
		cin >> user_input;
		getline(cin, trash_bin);
		try
		{
			symbol = stoi(user_input, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}
		if (symbol >= 0 && symbol <= 2)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return symbol;
}

/**
* Ask what kind of method to find password
* @return 0 both, 1 brute force, 2 file
*/
int MethodToUse(void)
{
	string trash_bin, user_input;
	std::string::size_type sz;
	int method_use = 0;
	do {
		cout <<
			"****************************\n"
			"* Find or Create Password  *\n"
			"* 0 - Find Using Both      *\n"
			"* 1 - Find w/ Brute force  *\n"
			"* 2 - Find w/ File         *\n"
			"* 3 - Find w/ Dictionary   *\n"
			"* 4 - Create Password      *\n"
			"* 5 - Check Password       *\n"
			"****************************\n"
			"Please Enter a number above: ";
		cin >> user_input;
		getline(cin, trash_bin);
		try
		{
			method_use = stoi(user_input, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}
		if (method_use >= 0 && method_use <= 5)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return method_use;
}