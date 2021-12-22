/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 *
 * File: password_compare.c
 *
 * Description: Compares password to pre existing list.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <regex>
#include "../include/password_compare.h"
#include "../../password_component/include/password_component.h"

int GetList(string[]);
bool password_compare_file_condition = false;
ifstream file;

/**
* https://www.passwordrandom.com/most-popular-passwords
* @param password_to_crack password to find
* @return the password found.
*/
string Compare(string password_to_crack)
{
	cout << "Comparing..." << endl;
	string password_array[100];
	int size_of_list;

	if (password_compare_file_condition == false)
	{
		file.open("file.txt");
		if (!file.is_open())
		{
			cout << "File can not be found or opened..." << endl;
			return "";
		}
		password_compare_file_condition = true;
	}


	while (true)
	{
		size_of_list = GetList(password_array);

		for (int i = 0; i < size_of_list; i++)
		{
			if (debug_bool) cout << i <<") Checking: " << password_array[i] << endl;;
			if (password_to_crack.compare(password_array[i]) == 0)
			{
				cout << "Password is found in database..." << endl;
				file.close();
				password_compare_file_condition = false;
				return password_array[i];
			}
		}

		if (size_of_list == -1)
		{
			cout << "Password can not be found in list..." << endl;
			file.close();
			password_compare_file_condition = false;
			return "";
		}
	}

	return "";
}

/**
* Fills the list of prexisiting password to match with,
* the list is populated up to 100 words and only stores
* the words that match the parameters when initialized.
* @param listOfP is a the list that is given back to Compare
* and find the password.
* @return actual size of the list being passed back
*/
int GetList(string listOfP[])
{
	int type[3] = { password_component.alphabet, password_component.numbers, password_component.symbol };

	int size_of_list = 0;
	string temp_word_var;
	regex cap(".*[a-z]+");
	regex all_leters(".*[A-Za-z]+");
	regex digit(".*[0-9]+");
	// Needs another list of spec chars for specific exclusion
	regex special_char(".*[!\"#$'()*+-./:;<=>?@^_`{|}~]+");
	// Above is missing some other spec chars like [, ], and \

	if (file.eof())
		return -1;

	if (!file.good())
	{
		cout << "error with file..." << endl;
		return -1;
	}

	for (int i = 0; i < 100; i++)
	{
		file >> temp_word_var;

		// exclusionary conditions
		if (temp_word_var.length() < password_component.minimum_length || temp_word_var.length() > password_component.max_length)
			continue;

		// need to be upgraded to deal with case sensetive.
		if (type[0] == 0 && regex_match(temp_word_var, all_leters))
			continue;

		if (type[0] == 1 && regex_match(temp_word_var, cap))
			continue;

		if (type[1] == 0 && regex_match(temp_word_var, digit))
			continue;

		// needs to include case for special char inclusion
		if (type[2] && regex_match(temp_word_var, special_char))
			continue;

		if (debug_bool)
		{
			cout << temp_word_var;
			if (regex_match(temp_word_var, cap))
				cout << " Has lower case Letter";
			if (regex_match(temp_word_var, all_leters))
				cout << " Has A letter";
			if (regex_match(temp_word_var, digit))
				cout << " Has A Digit";
			if (regex_match(temp_word_var, special_char))
				cout << " spec Char";
			cout << endl;
		}

		// Regex case goes here which determines if it stores
		// the word to check.

		// pass regex store to list
		listOfP[size_of_list] = temp_word_var;
		size_of_list++;
	}
	return size_of_list;
}