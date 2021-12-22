/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: password_component.c
 * 
 * Description: components of the passwords.
 *****************************************************************************/

#include <iostream>
#include <string>
#include "password_component.h"

bool debug_bool = false;

PasswordComponent::PasswordComponent(void) :
	minimum_length(0), max_length(0),
	numbers(0), alphabet(0), symbol(0) {}

PasswordComponent::PasswordComponent(int minimum_length, int max_length,
	int numbers, int alphabet, int symbol):
	minimum_length(minimum_length), max_length(max_length), 
	numbers(numbers), alphabet(alphabet), symbol(symbol){}

void SetPasswordComponent(int minimum_length, int max_length,
	int numbers, int alphabet, int symbol)
{
	password_component.minimum_length = minimum_length;
	password_component.max_length = max_length;
	password_component.numbers = numbers;
	password_component.alphabet = alphabet;
	password_component.symbol = symbol;

	if (debug_bool)
	{
		cout << "Setting password_component" << endl;
		cout << "minimum_length " << password_component.minimum_length << ":" << minimum_length << endl;
		cout << "max_length " << password_component.max_length << ":" << max_length << endl;
		cout << "numbers " << password_component.numbers << ":" << numbers << endl;
		cout << "alphabet " << password_component.alphabet << ":" << alphabet << endl;
		cout << "symbol " << password_component.symbol << ":" << symbol << endl;
	}
}

string ConvertToString(char* a, int size)
{
	string s = "";
	for (int i = 0; i < size; i++)
		s = s + a[i];
	return s;
}
