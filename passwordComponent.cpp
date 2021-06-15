#include "passwordComponent.h"

PasswordComponent::PasswordComponent(int minLength, int maxLength,
	int numbers, int alphabet, int symbol):
	minLength(minLength), maxLength(maxLength), 
	numbers(numbers), alphabet(alphabet), symbol(symbol){}