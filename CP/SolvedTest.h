#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
using namespace std;

class Test;

class SolvedTest
{
	string shortDiscription, uniqueID, subject;
	list<int>* answers;
	int maxPoints, receivedPoints;
public:
	SolvedTest(list<int>*, string, string, string, int, int);
	~SolvedTest();
	void PrintAnswer();
	void PrintBriefly();
	string GetID();
	friend ofstream& operator<<(ofstream&, const SolvedTest&);
	friend ostream& operator<<(ostream&, const SolvedTest&);
	friend void ViewQuestionAndUserAnswer(const SolvedTest*, const Test*);
};

