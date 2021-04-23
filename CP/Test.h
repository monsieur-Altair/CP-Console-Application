#pragma once
#include <list>
#include "Question.h"
#include "SolvedTest.h"
#include <conio.h>


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

template<class T>
void Check(T* value, double min = -10000000, double max = 1000000)
{
	if (cin.good())
		return;
	cin.clear();
	cin.ignore(500, '\n');
	do
	{
		cout << "\nНеверный ввод!\nВведите новое значение: ";
		char x = 0;
		*value = 0;
		bool isMinus = false, isAppear = false;
		do
		{
			x = _getch();
			if (x == '-' && !isAppear)
			{
				cout << x;
				isMinus = true;
				isAppear = true;
			}
			if (x >= '0' && x <= '9')
			{
				isAppear = true;
				cout << x;
				*value *= 10;
				if (!isMinus) *value += (x - 48);
				else *value -= (x - 48);
			}
			if (x == 8)
			{
				cout << "\b \b";
				*value /= 10;
			}
		} while (x != 13);
	} while (*value < min || *value > max);
}
bool SortTestBySubject(const Test*, const Test*);