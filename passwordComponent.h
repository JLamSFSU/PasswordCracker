#pragma once

class PasswordComponent
{
private:
	int minLength;
	int maxLength;
	int numbers;
	int alphabet;
	int symbol;
public:
	PasswordComponent(int, int, int, int, int);
};