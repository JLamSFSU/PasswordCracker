/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: password_component.h
 * 
 * Description: Define the PasswordComponent class and establish include.
 *****************************************************************************/

#pragma once
using namespace std;

class PasswordComponent
{
public:
	int minimum_length;
	int max_length;
	int numbers;
	int alphabet;
	int symbol;

	PasswordComponent(void);
	PasswordComponent(int, int, int, int, int);
};

extern PasswordComponent password_component;

// to activate or deactivate debug 
extern bool debug_bool;

void SetPasswordComponent(int, int, int, int, int);

string ConvertToString(char*, int);