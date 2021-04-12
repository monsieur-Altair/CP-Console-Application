#include "Question.h"

Question::Question()
{
	this->question = "вопрос";
	this->answerOptions = nullptr;
	this->numberOfAnswers = 0;
	correctAnswerOption = 0;
	pointsPerQuestion = 0;
	cout << "\nКонструктор QUESTION " << this;
}

Question::Question(string question, string* answ, int correctAnswerOption, int pointsPerQuestion, int numberOfAnswers)
{
	this->numberOfAnswers = numberOfAnswers;
	this->question = question;
	this->answerOptions = answ;
	this->correctAnswerOption = correctAnswerOption;
	this->pointsPerQuestion = pointsPerQuestion;
	cout << "\nКонструктор QUESTION " << this;
}

Question::~Question()
{
	delete[] answerOptions;
	cout << "\nДеструктор QUESTION " << this;
}

int Question::GetPoints()
{
	return this->pointsPerQuestion;
}

int Question::GetCorrectAnswerOption()
{
	return this->correctAnswerOption;
}

void Question::PrintQuestion()
{
	cout << "\n\nВопрос: " << this->question;
	for (int i = 0; i < numberOfAnswers; i++)
		cout << "\n  " << i + 1 << ". " << answerOptions[i];
}

void Question::PrintCorrectAnswer()
{
	cout << "\nПравильный ответ: " << correctAnswerOption;
}

int Question::GetNumberOfAnswers()
{
	return this->numberOfAnswers;
}

void Question::UnloadQuestion(ofstream& file)
{
	file << "\n" << this->question << "\n";
	for (int i = 0; i < this->numberOfAnswers; i++)
		file << this->answerOptions[i] << "\n";
	file << this->pointsPerQuestion << " " << this->correctAnswerOption;
}
