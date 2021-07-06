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
	int minLength, maxLength, numbers, alphabet, symbol;
	static int returnVal [5] = {0};

	cout << "Please complete the passwords parameters:" << endl;

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

// needs to be upgraded to have option for lower case only.
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
			"* 2 - Use Lower Case only  *\n"
			"* 3 - Case Sensitive       *\n"
			"****************************\n"
			"Please Enter 0, 1, 2, or 3: ";
		cin >> alphabet;
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
		cin >> symbol;
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
	int methodUse = 0;
	do {
		cout <<
			"****************************\n"
			"* Find or Create Password  *\n"
			"* 0 - Find Using Both      *\n"
			"* 1 - Find w/ Brute force  *\n"
			"* 2 - Find w/ File         *\n"
			"* 3 - Create Password      *\n"
			"* 4 - Check Password       *\n"
			"****************************\n"
			"Please Enter 0, 1, 2, 3, or 4: ";
		cin >> methodUse;
		if (methodUse >= 0 && methodUse <= 4)
			break;
		cout << "Incorrect Input, Try Again" << endl;
	} while (true);
	return methodUse;
}