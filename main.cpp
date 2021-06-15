using namespace std;
#include "panel.h"
#include "pcrack.h"

int main(void)
{
	string passwordToCrack;
	string passwordFound;

	cout << "Enter Password to Crack: ";
	cin >> passwordToCrack;

	passwordFound = cracker(passwordToCrack, mainMenu());
	cout << "Password is: " << passwordFound << endl;
	return 0;
}
