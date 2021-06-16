#pragma once

class PasswordComponent
{
public:
	int minLength;
	int maxLength;
	int numbers;
	int alphabet;
	int symbol;

	PasswordComponent(void);
	PasswordComponent(int, int, int, int, int);
};

extern PasswordComponent pc;

void setPC(int, int, int, int, int);