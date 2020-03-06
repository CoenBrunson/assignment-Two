#include "Survey.h"
#include<iostream>

using namespace std;

Survey::Survey() // do all work within the constructor, for  p e a k  e f f i c i e n c y
{
	participants = 0;
	averageHoursPlayed = 0;
	medianHoursPlayed = 0;
	modeHoursPlayed = 0;
	setParticipants();
	populateSurvey();
	sortResults();
	calculateAverage();
	calculateMedian();
	calculateMode();
	print();
}

Survey::~Survey()
{
}

void Survey::populateSurvey() //uses input validation to ensure that negative playtime or playtime exceeding hours in a month are not accepted
{
	cout << "Please enter the playtime of each participant in the last month.\n";
	for (int i = 0; i < participants; i++) {
		do {
			float input;
			cout << "Hours played by participant " << i + 1 << ": ";
			cin >> input;
			cin.ignore(INT_MAX, '\n');
			if (std::cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid input, please reenter.\n";
			}
			else if (input < 0) {
				cout << "Negative playtime not accepted, please reenter.\n";
			}
			else if (input > 730) {
				cout << "Invalid, not enough hours in month, please reenter.\n";
			}
			else {
				hoursPlayed.push_back(input);
				break;
			}
		} while (true);
	}
}

int Survey::getParticipants()
{
	return participants;
}

void Survey::setParticipants() // uses input validation to ensure that only a positive number of students will be entered
{
	std::cout << "How many students are being surveyed?\n";
	do {
		cin >> participants;
		cin.ignore(INT_MAX, '\n');
		if (std::cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid input, please reenter.\n";
		}
		else if (participants < 1) {
			cout << "Data can only be obtained from existing people, please reenter.\n";
		}
		else break;
	} while (true);
	hoursPlayed.reserve(participants);
}

void Survey::sortResults() { // uses regular bubble sort
	if (participants != 1) {
		bool swapped = true;
		while (swapped) {
			swapped = false;
			for (int i = 1; i < participants; i++) {
				if (hoursPlayed[i] < hoursPlayed[i - 1]) {
					hoursPlayed[i - 1] += hoursPlayed[i];
					hoursPlayed[i] = hoursPlayed[i - 1] - hoursPlayed[i];
					hoursPlayed[i - 1] -= hoursPlayed[i];
					swapped = true;
				}
			}
		}
	}
}

float Survey::getAverage()
{
	return averageHoursPlayed;
}

void Survey::calculateAverage()
{
	float totalHours = 0;
	for (auto& i : hoursPlayed) {
		totalHours += i;
	}
	averageHoursPlayed = totalHours / participants;
}

float Survey::getMedian()
{
	return medianHoursPlayed;
}

void Survey::calculateMedian() // if an even amount of participants are surveyed, the median is the average of the 2 middle elements
{
	if (participants % 2 == 0) {
		medianHoursPlayed = (hoursPlayed[participants / 2 - 1] + hoursPlayed[participants / 2]) / 2;
	}
	else
		medianHoursPlayed = hoursPlayed[participants / 2];
}

float Survey::getMode()
{
	return modeHoursPlayed;
}

void Survey::calculateMode() // the hoursPlayed vector must be sorted, counts elements with repeating values
{
	float currentNum = hoursPlayed[0];
	int count = 0, highestCount = 0;
	for (int i = 1; i < participants; i++) {
		if (hoursPlayed[i] == currentNum) {
			count++;
		}
		else {
			if (count > highestCount) {
				highestCount = count;
				modeHoursPlayed = currentNum;
			}
			count = 0;
			currentNum = hoursPlayed[i];
		}
	}
}

void Survey::print()
{
	cout << "Survey Results\nPlayers surveyed: " << getParticipants() << "\nAverage playtime: " << getAverage() << "\nMedian playtime: " << getMedian() << "\nMode playtime: " << getMode() << endl;
}
