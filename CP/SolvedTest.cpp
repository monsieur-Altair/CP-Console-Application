#include "SolvedTest.h"

SolvedTest::SolvedTest(list<int>* answers, string shortDiscription, string uniqueID, int receivedPoints, int maxPoints)
{
	this->maxPoints = maxPoints;
	this->receivedPoints = receivedPoints;
	this->answers = answers;
	this->shortDiscription = shortDiscription;
	this->uniqueID = uniqueID;
	//this->size = answers->size();
	cout << "\n����������� ������� " << this;
}

SolvedTest::~SolvedTest()
{
	delete answers;
	cout << "\n���������� ������� " << this;
}

void SolvedTest::PrintAnswer()
{
	//for(auto iter=answers->begin();iter!=answers->end();iter++)
	//	cout<<
}

void SolvedTest::PrintBriefly()
{
	cout << "\n" << this->uniqueID << "\t" << this->receivedPoints << "/" << this->maxPoints << "\t" << this->shortDiscription;
}
