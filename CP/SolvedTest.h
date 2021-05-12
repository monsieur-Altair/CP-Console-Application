#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
//#define DEBUG_1
using namespace std;

class Test;
class Student;
class SolvedTest;

namespace sort
{
	bool SortSolvedBySubject(const SolvedTest*, const SolvedTest*);
	bool SortByAnswerPercentage(SolvedTest*, SolvedTest*);
	bool SortStudentByGroups(const Student*, const Student*);
	bool SortStudentAlphabetic(Student*, Student*);
	bool SortTestBySubject(const Test*, const Test*);
}

class SolvedTest
{
	string shortDiscription, subject;
	shared_ptr<list<int>> answers;
	int uniqueID, maxPoints, receivedPoints;
public:
	SolvedTest
	(
		shared_ptr<list<int>>, //answers
		string, //short decription
		int,	//unique ID
		string, //subject
		int,	//received points
		int		//max points
	);
	~SolvedTest();
	void PrintBriefly();
	int GetID();
	float GetPercent();
	string GetSubject();
	friend ofstream& operator<<(ofstream&, const SolvedTest&);
	friend ostream&  operator<<(ostream&,  const SolvedTest&);
	friend void ViewQuestionAndUserAnswer(const SolvedTest*, const Test*);
	friend bool sort::SortByAnswerPercentage(SolvedTest*, SolvedTest*);
	friend bool sort::SortSolvedBySubject(const SolvedTest*,const SolvedTest*);
};

