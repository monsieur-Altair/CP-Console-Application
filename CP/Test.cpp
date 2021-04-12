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

Test::Test(string DataFilePath)
{
	this->DownloadFromFile(DataFilePath);
	this->SetMaxPointsPerTest();
	this->numberOfQuestions = questionList.size();
	cout << "\n����������� TEST " << this;
}

Test::~Test()
{
	for (auto iter = questionList.begin(); iter != questionList.end(); iter++)
		delete (*iter);
	cout << "\n���������� TEST " << this;
}

void Test::PrintTest()
{
	cout << "\n���� " << this->uniqueID << "\n�������: " << this->subject;
	cout << "\n����: " << this->course << "\n������� ��������: " << shortDescription;
	for (auto iter = questionList.begin(); iter != questionList.end(); iter++)
		(*iter)->PrintQuestion();
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
	for (auto iter = questionList.begin(); iter != questionList.end(); iter++)
		this->maxPointsPerTest += (*iter)->GetPoints();
}


void Test::UnloadTest(string Path)
{
	ofstream file;
	file.open(Path);
	auto iter1 = questionList.begin();
	file << (*iter1)->GetNumberOfAnswers() << " " << this->course << "\n";
	file << this->uniqueID << "\n" << this->subject << "\n" << this->shortDescription;
	for (auto iter = questionList.begin(); iter != questionList.end(); iter++)
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

	while (dataFile.tellg() <= fileSize)
	{
		i = 0;
		string* answ = new string[numberOfAnswers];
		getline(dataFile, question);

		while (i < numberOfAnswers)
			getline(dataFile, answ[i++]);//��������� ������ �� ������

		dataFile >> pointPerQuestion >> correctAnswer;
		questionList.push_back(new Question(question, answ, correctAnswer, pointPerQuestion, numberOfAnswers));
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
	list<int>* answers = new list<int>;
	int answ, receivedPoints = 0;
	for (auto iter = questionList.begin(); iter != questionList.end(); iter++)
	{
		(*iter)->PrintQuestion();
		cout << "\n��� �����: ";
		cin >> answ;
		answers->push_back(answ);
		if (answ == (*iter)->GetCorrectAnswerOption())
		{
			int points = (*iter)->GetPoints();
			receivedPoints += points;
			cout << "\n����� ������ - �� ��������� " << points << " ������";
		}
		else
			cout << "\n����� �������� - �� ��������� 0 ������";
	}
	cout << "\n���� �������, ������� �� ����������� �����, ���� ������ ��������";
	return new SolvedTest(answers, this->shortDescription, this->uniqueID, receivedPoints, this->maxPointsPerTest);
}
