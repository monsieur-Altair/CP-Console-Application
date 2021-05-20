#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
//#define DEBUG
using namespace std;

class Teacher;
class Test;

class Question
{
	int numberOfAnswers;
	string question;
	string* answerOptions;
	int correctAnswerOption, pointsPerQuestion;
public:
	Question();
	Question(string, string*, int, int, int);
	~Question();
	int GetPoints();
	int GetNumberOfAnswers();
	int GetCorrectAnswerOption();
	void PrintQuestion();
	void PrintCorrectAnswer();
	void UnloadQuestion(ofstream&);
	friend void EditTest(Teacher*, Test*,bool*);
};

