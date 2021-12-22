/******************************************************************************
 * Project: Password Program
 * Author:  Justin Lam
 * 
 * File: password_dictionary_attack.c
 * 
 * Description: Password Dictionary attack.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "../include/password_dictionary_attack.h"
#include "../../password_component/include/password_component.h"

string CollectDataMenu(void);
string DigitToWord(int);
// string varyDataCollected(string);

int BuildDictionary(vector <string> &words);
int ManualInputDictionary(vector <string> &words);
int RemoveFromDictionary(vector <string> &words);

ifstream dictionary_import;

/**
* https://cybernews.com/best-password-managers/password-cracking-techniques/
* #5 & #6 as refernce for function.
*/
string DictionaryAttack(string password_to_crack)
{
	vector <string> user_data;
	string final_word;
	int user_data_size, data_combo;

	// import part of the dictionary using a file
	if (BuildDictionary(user_data) == -1)
		exit(-1);

	// collect user manual input data
	if (ManualInputDictionary(user_data) == -1)
		exit(-1);
	
	// remove from list
	if (RemoveFromDictionary(user_data) == -1)
		exit(-1);

	// password generation
	user_data_size = user_data.size();

	// remove from list again.

	// generate passwords and Compare
	final_word = user_data[0];

	if (true) // debug_bool later
	{
		cout << "Dictionary before exit:" << endl;
		for (int i = 0; i < user_data_size; i++)
			cout << user_data[i] << endl;
	}

	// return match
	return final_word;
}

/**
* Displays a menu that allows the user to continually add to
* the vector.
* @return words to be added to the vector, if return is "" end collection.
*/
string CollectDataMenu()
{
	string return_word;
	string trash_bin;
	cout << "Please enter a word or number you wish to enter into the dictionary\n"
		"(Enter &&& to stop or %%% to view current list): ";
	cin >> return_word;
	getline(cin, trash_bin);
	return return_word;
}

/**
* Currently only works for some case of 0-12.
* Needs to be upgraded for more cases somehow.
* @param number the number that is to convert to the word version
* @return the word version of the number
*/
string DigitToWord(int number)
{
	vector <string> list = { "zero", "one", "two", "three", "four", "five", "six",
							"seven", "eight", "nine", "ten", "eleven", "twelve" };

	return list[number];
}

/**
* @param words the dictionary to be added to
* @return error code
*/
int BuildDictionary(vector <string> &words)
{
	string word_to_enter, user_input, trash_bin;

	while (true)
	{
		cout << "Would you like to import part of the dictionary? (y/n) ";
		cin >> user_input;
		getline(cin, trash_bin);
		if (user_input.compare("y") == 0)
			break;
		if (user_input.compare("n") == 0)
			return 0;
	}

	// import file here;
	dictionary_import.open("dictionary.txt");
	if (!dictionary_import.is_open())
	{
		cout << "Dictionary can not be found or opened..." << endl;
		return -1;
	}

	while (true)
	{
		dictionary_import >> word_to_enter;
		words.push_back(word_to_enter);
		if (dictionary_import.eof())
			break;
	}
	
	dictionary_import.close();
	if (dictionary_import.is_open())
	{
		cout << "Issue closing file..." << endl;
		return -1;
	}
		
	return 0;
}

/**
* @param words the dictionary vector to be added to
* @return error code
*/
int ManualInputDictionary(vector <string>& words)
{
	string word_to_enter;
	while (true)
	{
		word_to_enter = CollectDataMenu();
		if (word_to_enter.compare("&&&") == 0)
			break;
		if (word_to_enter.compare("%%%") == 0)
		{
			cout << "Current Dictionary:" << endl;
			for (int i = 0; i < words.size(); i++)
				cout << i + 1 << " - " << words[i] << endl;
			continue;
		}
		words.push_back(word_to_enter);
	}
	return 0;
}

/**
* remove from list that does not meet the requirements
* such as exceeding max length or having numbers when
* numbers are not allowed.
* @param words the dictionary vector to be added to
* @return error code
*/
int RemoveFromDictionary(vector <string>& words)
{
	std::string::size_type sz;
	int type[3] = { password_component.alphabet, password_component.numbers, password_component.symbol };
	int number_as_int;
	int max_length = password_component.max_length;
	int iteration = 0;

	bool do_not_remove_word = true;

	regex cap(".*[a-z]+");
	regex all_leters(".*[A-Za-z]+");
	regex digit(".*[0-9]+");
	// Needs another list of spec chars for specific exclusion
	regex special_char(".*[!\"#$'()*+-./:;<=>?@^_`{|}~]+");
	// Above is missing some other spec chars like [, ], and \

	while (true)
	{
		if (iteration >= words.size())
			break;
		// deals with alphabet
		/*
		* psuedo:
		* if alphabet is not allowed
		* if word contains alphabet remove
		*
		* "might need to do something that varies the
		* cap sensitivity here as well if cap sensitivity
		* is active."
		*/
		// if (user_data[i])

		// deals with numbers
		/*
		* if numbers is not allowed
		* if string contains numbers remove
		*/
		// turn number to words (i.e. 1 -> one)
		if (type[0] > 0 && regex_match(words[iteration], digit) &&
			(!regex_match(words[iteration], all_leters) ||
				!regex_match(words[iteration], special_char)))
		{
			number_as_int = stoi(words[iteration], &sz);
			if (number_as_int <= 12 && number_as_int >= 0)
				words.push_back(DigitToWord(number_as_int));
		}

		if (do_not_remove_word && type[1] == 0 && regex_match(words[iteration], digit))
			do_not_remove_word = false;

		// deals with symbols
		/*
		* if symbols is not allowed
		* "might need to do two conditional one for all and one for special"
		* if string contains symbols remove
		*/
		if (do_not_remove_word && type[2] == 0 && regex_match(words[iteration], special_char))
			do_not_remove_word = false;

		// deals with length
		if (do_not_remove_word && words[iteration].length() > max_length)
			do_not_remove_word = false;

		if (!do_not_remove_word)
		{
			words.erase(words.begin() + iteration);
			do_not_remove_word = true;
			continue;
		}

		// iterator or break;
		if (iteration < words.size() - 1)
			iteration++;
		else
			break;
	}
	return 0;
}
