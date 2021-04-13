#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
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
	friend ofstream& operator<<(ofstream& file, const SolvedTest& solvedTest);
};

