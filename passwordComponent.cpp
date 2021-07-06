#include <iostream>
#include <string>
#include "passwordComponent.h"

bool debugBool = false;

PasswordComponent::PasswordComponent(void) :
	minLength(0), maxLength(0),
	numbers(0), alphabet(0), symbol(0) {}

PasswordComponent::PasswordComponent(int minLength, int maxLength,
	int numbers, int alphabet, int symbol):
	minLength(minLength), maxLength(maxLength), 
	numbers(numbers), alphabet(alphabet), symbol(symbol){}

void setPC(int minLength, int maxLength,
	int numbers, int alphabet, int symbol)
{
	pc.minLength = minLength;
	pc.maxLength = maxLength;
	pc.numbers = numbers;
	pc.alphabet = alphabet;
	pc.symbol = symbol;

	if (debugBool)
	{
		cout << "Setting PC" << endl;
		cout << "MinLength " << pc.minLength << ":" << minLength << endl;
		cout << "MaxLength " << pc.maxLength << ":" << maxLength << endl;
		cout << "numbers " << pc.numbers << ":" << numbers << endl;
		cout << "alphabet " << pc.alphabet << ":" << alphabet << endl;
		cout << "symbol " << pc.symbol << ":" << symbol << endl;
	}
}

string convertToString(char* a, int size)
{
	string s = "";
	for (int i = 0; i < size; i++)
		s = s + a[i];
	return s;
}
