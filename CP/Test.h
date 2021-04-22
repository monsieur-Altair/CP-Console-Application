#pragma once
#include <list>
#include "Question.h"
#include "SolvedTest.h"



class Test
{
	list<Question*> *ptrQuestionList;
	string shortDescription, subject, uniqueID;
	int maxPointsPerTest, numberOfQuestions, course;
public:
	Test();
	Test(string, string, string, int, list<Question*>*);
	Test(string);
	~Test();
	void PrintTest();
	void PrintTestBriefly();
	int GetMaxPointsPerTest();
	int GetNumberOfQuestions();
	void SetMaxPointsPerTest();
	void DownloadFromFile(string);
	void UnloadTest(string);
	string GetSubject();
	int GetCourse();
	string GetID();
	SolvedTest* Solving();
	friend void ViewQuestionAndUserAnswer(const SolvedTest*, const Test*);
	friend void EditTest(Teacher*, Test*,bool*);	
	friend bool SortTestBySubject(const Test*, const Test*);
};

bool SortTestBySubject(const Test* ptr1, const Test* ptr2)
{
	return (ptr1->subject.compare(ptr2->subject) < 0);
}
