#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "pcompare.h"
#include "passwordComponent.h"

string compare(string passwordToCrack)
{
	cout << "Comparing..." << endl;
	string myArray[6];

	ifstream file("file.txt");
	if (file.good())
	{
		cout << "file is open..." << endl;
		for (int i = 0; i < 6; i++)
		{
			file >> myArray[i];
		}
	}

	if (file.good())
	{
		for (int i = 0; i < 6; i++)
		{
			cout << myArray[i] << endl;
		}
	}
	file.close();

	return "";
}