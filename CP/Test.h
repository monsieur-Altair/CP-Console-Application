#pragma once
#include <list>
#include "AdditionalFunctions.h"
#include "SolvedTest.h"



class Test
{
	list<Question*> *ptrQuestionList;
	string shortDescription, subject;
	int uniqueID, maxPointsPerTest, numberOfQuestions, course;
	static int entityCount;
public:
	Test();
	Test(int, string, string, int, list<Question*>*);
	Test(string);
	~Test();
	void PrintTest();
	void PrintTestBriefly();
	void UnloadTest(string);
	void SetMaxPointsPerTest();
	void DownloadFromFile(string);
	int  GetID();
	int  GetCourse();
	int  GetMaxPointsPerTest();
	int  GetNumberOfQuestions();
	SolvedTest* Solving();
	string GetSubject();
	friend void ViewQuestionAndUserAnswer(const SolvedTest*, const Test*);
	friend void EditTest(Teacher*, Test*,bool*);	
	friend bool sort::SortTestBySubject(const Test*, const Test*);
	static int GetEntityCount();
};

