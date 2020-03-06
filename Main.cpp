//Andrey Chizhov 101255069
//This program creates a pointer to a survey object, which allows the user to survey any reasonable amount of students for playtimes, calculates average, median, and mode, displays the info to the console, then deletes the survey object
#include "Survey.h"

using namespace std;

int main() {
	Survey* playTimes = new Survey();
	delete playTimes;
	return 0;
}