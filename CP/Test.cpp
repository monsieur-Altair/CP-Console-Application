#include "Test.h"

Test::Test()
{
	this->shortDescription = "";
	this->maxPointsPerTest = 0;
	this->numberOfQuestions = 0;
	this->course = 0;
	this->subject = "";
	this->uniqueID = "";
	cout << "\n����������� TEST " << this;
}

Test::Test(string uniqueID, string shortDiscription, string subject, int course, list<Question*>* ptrQuestionList)
{
	this->course = course;
	this->ptrQuestionList = ptrQuestionList;
	this->numberOfQuestions = this->ptrQuestionList->size();
	this->shortDescription = shortDiscription;
	this->subject = subject;
	this->uniqueID = uniqueID;
	this->SetMaxPointsPerTest();
}

Test::Test(string DataFilePath)
{
	this->DownloadFromFile(DataFilePath);
	this->SetMaxPointsPerTest();
	this->numberOfQuestions = ptrQuestionList->size();
	cout << "\n����������� TEST " << this;
}

Test::~Test()
{
	for (auto iter = ptrQuestionList->begin(); iter != ptrQuestionList->end(); iter++)
		delete (*iter);
	delete ptrQuestionList;
	cout << "\n���������� TEST " << this;
}

void Test::PrintTest()
{
	//cout << "\n���� " << this->uniqueID << "\n�������: " << this->subject;
	//cout << "\n����: " << this->course << "\n������� ��������: " << shortDescription;
	//for (auto iter = ptrQuestionList->begin(); iter != ptrQuestionList->end(); iter++)
	//	(*iter)->PrintQuestion();
	cout << "\n�������: " << this->subject << "\n����: " << this->course << "\n������� ��������: " << shortDescription << "\n";
	system("pause");
	system("cls");
	for (auto iter = ptrQuestionList->begin(); iter != ptrQuestionList->end(); iter++)
	{
		(*iter)->PrintQuestion();
		cout << "\n���������� �����: " << (*iter)->GetCorrectAnswerOption() << "\n���������� ������: " << (*iter)->GetPoints() << "\n";
		system("pause");
		system("cls");
	}
}

int Test::GetMaxPointsPerTest()
{
	return maxPointsPerTest;
}

void Test::PrintTestBriefly()
{
	cout << "\n" << this->uniqueID << "\t" << this->subject;
	cout << "\t" << this->course << "\t" << shortDescription;
}

void Test::SetMaxPointsPerTest()
{
	for (auto iter = ptrQuestionList->begin(); iter != ptrQuestionList->end(); iter++)
		this->maxPointsPerTest += (*iter)->GetPoints();
}

void Test::UnloadTest(string Path)
{
	ofstream file;
	file.open(Path);
	auto iter1 = ptrQuestionList->begin();
	file << (*iter1)->GetNumberOfAnswers() << " " << this->course << "\n";
	file << this->uniqueID << "\n" << this->subject << "\n" << this->shortDescription;
	for (auto iter = ptrQuestionList->begin(); iter != ptrQuestionList->end(); iter++)
		(*iter)->UnloadQuestion(file);
	file.close();
}

void Test::DownloadFromFile(string dataFilePath)
{
	ifstream dataFile;
	string question, answer;
	int pointPerQuestion, correctAnswer, numberOfAnswers;
	int i, fileSize;
	dataFile.open(dataFilePath);
	if (!dataFile.is_open())
		exit(-1);

	dataFile.seekg(0, ios::end);//���������� ��������� � ����� � ��������� ����� ���� � ����� ������ �����
	fileSize = dataFile.tellg();
	dataFile.seekg(0, ios::beg);

	dataFile >> numberOfAnswers >> this->course;
	dataFile.seekg(2, ios::cur);//��������� �� ����� ������ (2 = ������ "\n")
	getline(dataFile, this->uniqueID);
	getline(dataFile, this->subject);
	getline(dataFile, this->shortDescription);
	this->ptrQuestionList = new list<Question*>;

	while (dataFile.tellg() <= fileSize)
	{
		i = 0;
		string* answ = new string[numberOfAnswers];
		getline(dataFile, question);

		while (i < numberOfAnswers)
			getline(dataFile, answ[i++]);//��������� ������ �� ������

		dataFile >> pointPerQuestion >> correctAnswer;
		ptrQuestionList->push_back(new Question(question, answ, correctAnswer, pointPerQuestion, numberOfAnswers));
		dataFile.seekg(2, ios::cur);
	}
	dataFile.close();
}

string Test::GetSubject()
{
	return this->subject;
}

int Test::GetCourse()
{
	return this->course;
}

string Test::GetID()
{
	return this->uniqueID;
}

SolvedTest* Test::Solving()
{
	system("cls");
	list<int>* answers = new list<int>;
	int answ, receivedPoints = 0;
	cout << "\n��� ������� ������������ ���� " << this->uniqueID << "\n" << this->shortDescription << "\n";
	cout << "���������� ��������: " << this->ptrQuestionList->size() << "\n������ ������������\n\n";
	system("pause");
	for (auto iter = ptrQuestionList->begin(); iter != ptrQuestionList->end(); iter++)
	{
		system("cls");
		(*iter)->PrintQuestion();
		cout << "\n��� �����: ";
		cin >> answ;
		answers->push_back(answ);
		if (answ == (*iter)->GetCorrectAnswerOption())
		{
			int points = (*iter)->GetPoints();
			receivedPoints += points;
			cout << "\n����� ������ - �� ��������� " << points << " ������\n";
		}
		else
			cout << "\n����� �������� - �� ��������� 0 ������\n";
		cout << "\n";
		system("pause");
	}
	system("cls");
	cout << "\n���� �������, ������� �� ����������� �����, ���� ������ ��������\n";
	return new SolvedTest(answers, this->shortDescription, this->uniqueID, receivedPoints, this->maxPointsPerTest);
}

void ViewQuestionAndUserAnswer(const SolvedTest* ptrSolvedTest, const Test* ptrTest)
{
	int correctAnswer, userAnswer, pointsForQuestion;
	auto answerIter = ptrSolvedTest->answers->begin();
	for (auto ptrQuestionIter = ptrTest->ptrQuestionList->begin(); ptrQuestionIter != ptrTest->ptrQuestionList->end(); ptrQuestionIter++)
	{
		correctAnswer = (*ptrQuestionIter)->GetCorrectAnswerOption();
		userAnswer = (*answerIter++);
		(*ptrQuestionIter)->PrintQuestion();
		cout << "\n���������� �����: " << correctAnswer;
		cout << "\n��� �����: " << userAnswer;
		pointsForQuestion = (correctAnswer == userAnswer) ? (*ptrQuestionIter)->GetPoints() : 0;
		cout << "\n�� ��������: " << pointsForQuestion << " ������\n";
		system("pause");
		system("cls");
	}
}
