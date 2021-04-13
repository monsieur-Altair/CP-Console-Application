#include "SolvedTest.h"

SolvedTest::SolvedTest(list<int>* answers, string shortDiscription, string uniqueID, int receivedPoints, int maxPoints)
{
	this->maxPoints = maxPoints;
	this->receivedPoints = receivedPoints;
	this->answers = answers;
	this->shortDiscription = shortDiscription;
	this->uniqueID = uniqueID;
	//this->size = answers->size();
	cout << "\nÊîíñòðóêòîð ÎÒÂÅÒÎÂ " << this;
}

SolvedTest::~SolvedTest()
{
	delete answers;
	cout << "\nÄåñòðóêòîð ÎÒÂÅÒÎÂ " << this;
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

ofstream& operator<<(ofstream& file, const SolvedTest& obj)
{
	file << obj.uniqueID << "\n" << obj.shortDiscription<<"\n";
	file << obj.receivedPoints << " " << obj.maxPoints << "\n";
	file << obj.answers->size();
	for (auto iter = obj.answers->begin(); iter != obj.answers->end(); iter++)
		file << " " << (*iter);
	return file;
}
