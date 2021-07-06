#pragma once
using namespace std;

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

// to activate or deactivate debug 
extern bool debugBool = false;

void setPC(int, int, int, int, int);

string convertToString(char*, int);