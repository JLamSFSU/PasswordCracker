#include "passwordComponent.h"
#include <iostream>
using namespace std;

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
	cout << "Setting PC" << endl;
	pc.minLength = minLength;
	cout << "MinLength " << pc.minLength << ":" << minLength << endl;
	pc.maxLength = maxLength;
	cout << "MaxLength " << pc.maxLength << ":" << maxLength << endl;
	pc.numbers = numbers;
	cout << "numbers " << pc.numbers << ":" << numbers << endl;
	pc.alphabet = alphabet;
	cout << "alphabet " << pc.alphabet << ":" << alphabet << endl;
	pc.symbol = symbol;
	cout << "symbol " << pc.symbol << ":" << symbol << endl;
}