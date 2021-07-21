#include <string>
#include "panel.h"
#include "pcrack.h"
#include "passwordComponent.h"

int useNumbers(void);
int useAlphabet(void);
int useSpecialChar(void);
int methodToUse(void);

PasswordComponent pc = PasswordComponent();

/**
* Establish a menu to set the paramters to set the passward cracker.
* @param passwardToCrack provided password to find
* @return integer value of what to use to find password
*/
int mainMenu(void)
{
	string trashbin, userInput;
	std::string::size_type sz;
	int minLength, maxLength, numbers, alphabet, symbol;
	static int returnVal [5] = {0};

	cout << "Please complete the passwords parameters:" << endl;

	do {
		cout << "The min Length of password: ";
		cin >> userInput;
		getline(cin, trashbin);
		try 
		{
			minLength = stoi(userInput, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}

		cout << "The max Length of password: ";
		cin >> userInput;
		getline(cin, trashbin);
		try
		{
			maxLength = stoi(userInput, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}

		if (minLength <= maxLength && minLength > 0)
			break;
		cout << "Password Max can not be less than Min length.\nPlease Try Again" << endl;
	} while (true);

	if (true) // testing
	{
		alphabet = useAlphabet();
		numbers = useNumbers();
		symbol = useSpecialChar();
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
		setPC(minLength, maxLength, numbers, alphabet, symbol);

	return methodToUse();
}

/**
* Menu for inclusion of numbers
* @return 0 no Numbers, 1 use Numbers 
*/
int useNumbers(void)
{
	string trashbin, userInput;
	std::string::size_type sz;
	int numbers = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Numbers Used      *\n"
			"* 1 - Use Numbers          *\n"
			"****************************\n"
			"Please Enter 0 or 1: ";
		cin >> userInput;
		getline(cin, trashbin);
		try
		{
			numbers = stoi(userInput, &sz);
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
int useAlphabet(void)
{
	string trashbin, userInput;
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
		cin >> userInput;
		getline(cin, trashbin);
		try
		{
			alphabet = stoi(userInput, &sz);
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
int useSpecialChar(void)
{
	string trashbin, userInput;
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
		cin >> userInput;
		getline(cin, trashbin);
		try
		{
			symbol = stoi(userInput, &sz);
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
int methodToUse(void)
{
	string trashbin, userInput;
	std::string::size_type sz;
	int methodUse = 0;
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
		cin >> userInput;
		getline(cin, trashbin);
		try
		{
			methodUse = stoi(userInput, &sz);
		}
		catch (invalid_argument& e)
		{
			continue;
		}
		if (methodUse >= 0 && methodUse <= 5)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return methodUse;
}