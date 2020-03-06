#pragma once
#include<vector>
#include<algorithm>

#ifndef _Survey_
#define _Survey_

class Survey {
private:
	int participants;
	float averageHoursPlayed, medianHoursPlayed, modeHoursPlayed;
	std::vector<float> hoursPlayed;
public:
	Survey();
	~Survey();
	void populateSurvey();
	int getParticipants();
	void setParticipants();
	void sortResults();
	float getAverage();
	void calculateAverage();
	float getMedian();
	void calculateMedian();
	float getMode();
	void calculateMode();
	void print();
};

#endif