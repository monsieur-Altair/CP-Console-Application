#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
	int GetCorrectAnswerOption();
	void PrintQuestion();
	void PrintCorrectAnswer();
	int GetNumberOfAnswers();
	void UnloadQuestion(ofstream&);
};

