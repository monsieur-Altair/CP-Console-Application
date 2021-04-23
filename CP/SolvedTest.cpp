#include "SolvedTest.h"

SolvedTest::SolvedTest(list<int>* answers, string shortDiscription, string uniqueID, string subject, int receivedPoints, int maxPoints)
{
	this->maxPoints = maxPoints;
	this->receivedPoints = receivedPoints;
	this->answers = answers;
	this->shortDiscription = shortDiscription;
	this->uniqueID = uniqueID;
	this->subject = subject;
	cout << "\nÊîíñòðóêòîð ÎÒÂÅÒÎÂ " << this;
}

SolvedTest::~SolvedTest()
{
	delete answers;
	cout << "\nÄåñòðóêòîð ÎÒÂÅÒÎÂ " << this;
}


void SolvedTest::PrintBriefly()
{
	cout << "\n" << this->uniqueID << "\t" << this->subject << "\t" << this->receivedPoints << "/" << this->maxPoints << "\t" << this->shortDiscription;
}

string SolvedTest::GetID()
{
	return this->uniqueID;
}

float SolvedTest::GetPercent()
{
	return (float)receivedPoints / maxPoints;
}

string SolvedTest::GetSubject()
{
	return this->subject;
}

ofstream& operator<<(ofstream& file, const SolvedTest& obj)
{
	file << obj.uniqueID << "\n" << obj.subject << "\n" << obj.shortDiscription << "\n";
	file << obj.receivedPoints << " " << obj.maxPoints << "\n";
	file << obj.answers->size();
	for (auto iter = obj.answers->begin(); iter != obj.answers->end(); iter++)
		file << " " << (*iter);
	return file;
}

ostream& operator<<(ostream& out, const SolvedTest& obj)
{
	out << obj.uniqueID << "\n" << obj.subject << "\n" << obj.shortDiscription << "\n";
	out << obj.receivedPoints << " " << obj.maxPoints << "\n";
	out << obj.answers->size();
	for (auto iter = obj.answers->begin(); iter != obj.answers->end(); iter++)
		out << " " << (*iter);
	return out;
}

bool SortByAnswerPercentage(SolvedTest* ptr1, SolvedTest* ptr2)
{
	return (ptr1->GetPercent() > ptr2->GetPercent());
}

bool SortSolvedBySubject(const SolvedTest* ptr1, const SolvedTest* ptr2)
{
	return (ptr1->subject.compare(ptr2->subject) < 0);
}


