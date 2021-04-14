#pragma once
#include <list>
#include "Question.h"
#include "SolvedTest.h"


class Test
{
	list<Question*> questionList;
	string shortDescription, subject, uniqueID;
	int maxPointsPerTest, numberOfQuestions, course;
public:
	Test();
	Test(string);
	~Test();
	void PrintTest();
	void PrintTestBriefly();
	int GetMaxPointsPerTest();
	void SetMaxPointsPerTest();
	void DownloadFromFile(string);
	void UnloadTest(string);
	//friend void DataBase::PrintTestsWithFilter(int, list<string>*);
	string GetSubject();
	int GetCourse();
	string GetID();
	SolvedTest* Solving();
	friend void ViewQuestionAndUserAnswer(const SolvedTest*, const Test*);
};


