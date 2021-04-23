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
	void PrintBriefly();
	string GetID();
	float GetPercent();
	string GetSubject();
	friend ofstream& operator<<(ofstream&, const SolvedTest&);
	friend ostream& operator<<(ostream&, const SolvedTest&);
	friend void ViewQuestionAndUserAnswer(const SolvedTest*, const Test*);
	friend bool SortByAnswerPercentage(SolvedTest*, SolvedTest*);
	friend bool SortSolvedBySubject(const SolvedTest*,const SolvedTest*);
};

bool SortSolvedBySubject(const SolvedTest*, const SolvedTest*);
bool SortByAnswerPercentage(SolvedTest*, SolvedTest*);