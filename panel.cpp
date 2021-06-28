#include "panel.h"
#include "pcrack.h"
#include "passwordComponent.h"

int useNumbers(void);
int useAlphabet(void);
int useSpecialChar(void);

PasswordComponent pc = PasswordComponent();

/**
* Establish a menu to set the paramters to set the passward cracker.
* @param passwardToCrack provided password to find
* @return the found password
*/
void mainMenu(void)
{
	int minLength, maxLength, numbers, alphabet, symbol;
	static int returnVal [5] = {0};

	do {
		cout << "The min Length of password: ";
		cin >> minLength;
		cout << "The max Length of password: ";
		cin >> maxLength;
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
	{
		cout << "Bad Parameters!" << endl;
	}
	else
	{
		setPC(minLength, maxLength, numbers, alphabet, symbol);
		// cout << "OG: " << minLength << ", " << maxLength << ", " << numbers << endl;
		// cout << "PC: " << pc.minLength << ", " << pc.maxLength << ", " << pc.numbers << endl;
	}

	return;
}

/**
* Menu for inclusion of numbers
* @return 0 no Numbers, 1 use Numbers 
*/
int useNumbers(void)
{
	int numbers = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Numbers Used      *\n"
			"* 1 - Use Numbers          *\n"
			"****************************\n"
			"Please Enter 0 or 1: ";
		cin >> numbers;
		if (numbers == 0 || numbers == 1)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return numbers;
}

/**
* Menu for inclusion of alphabet
* @return 0 no alphabet, 1 none cap sensiteve, 2 cap sensitive
*/
int useAlphabet(void)
{
	int alphabet = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Alphabet Used     *\n"
			"* 1 - Use Captilze Alphabet*\n"
			"* 2 - Case Sensitive       *\n"
			"****************************\n"
			"Please Enter 0, 1, or 2: ";
		cin >> alphabet;
		if (alphabet >= 0 && alphabet <= 2)
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
	int symbol = 0;
	do {
		cout <<
			"****************************\n"
			"* 0 - No Symbols Used      *\n"
			"* 1 - Use Spceial Symbol   *\n"
			"* 2 - All Symbols          *\n"
			"* Differnce between 1 and 2*\n"
			"*   is not implemented at  *\n"
			"*   at this time.          *\n"
			"****************************\n"
			"Please Enter 0, 1, or 2: ";
		cin >> symbol;
		if (symbol >= 0 && symbol <= 2)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return symbol;
}