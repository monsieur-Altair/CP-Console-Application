#pragma once
#include <iostream>
#include <list>
using namespace std;

class SolvedTest
{
	string shortDiscription, uniqueID;
	list<int>* answers;
	int maxPoints, receivedPoints;
public:
	SolvedTest(list<int>*, string, string, int, int);
	~SolvedTest();
	void PrintAnswer();
	void PrintBriefly();
};

